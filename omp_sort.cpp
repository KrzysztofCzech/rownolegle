#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>


struct thread_data{
    std::vector<std::vector<double>> buckets = std::vector<std::vector<double>>();
    std::vector<double> buckets_thresholds = std::vector<double>();
    long long total_buckets_size = 0;
    long long emplace_buckets_offset = 0;
};

int main(int argc, char *argv[]){
    char* pEnd;
    unsigned long long int TAB_SIZE = strtoull(argv[1],&pEnd, 10);
    unsigned long int N_THREADS = strtoul(argv[2], &pEnd, 10);
    unsigned long int N_BUCKETS_IN_THREAD = strtoul(argv[3], &pEnd, 10);
    double BUCKET_RANGE_STEP = (1.0)/((double)(N_BUCKETS_IN_THREAD*N_THREADS));

    std::vector<double> tab = std::vector<double>(TAB_SIZE);
    std::vector<thread_data> threads_data = std::vector<thread_data>(N_THREADS);

    printf("TAB_SIZE : \r\n %llu \r\n",TAB_SIZE);
    printf("N_THREADS : \r\n %lu \r\n",N_THREADS);
    printf("N_BUCKETS_IN_THREAD : \r\n %lu \r\n",N_BUCKETS_IN_THREAD);
    printf("BUCKET_RANGE_STEP : \r\n %f\r\n",BUCKET_RANGE_STEP);

    //init random array
    long TSEED = time(NULL);
    #pragma omp parallel for num_threads(N_THREADS) schedule(guided)
    for(int i = 0; i< TAB_SIZE; i++){
        uint seed = 25233 + TAB_SIZE * omp_get_thread_num() + TSEED*(i+1)*301;
        tab[i] = (double)rand_r(&seed)/(double)RAND_MAX;
    }

    //init threads data
    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< N_THREADS; i++){
        thread_data* this_data = &threads_data[i];

        //init buckets thresholds
        this_data->buckets_thresholds.resize(N_BUCKETS_IN_THREAD+1);
        for(int j=0; j < N_BUCKETS_IN_THREAD+1; j++){
            this_data->buckets_thresholds[j] = (double)i*(BUCKET_RANGE_STEP*(double)N_BUCKETS_IN_THREAD) + j*BUCKET_RANGE_STEP;
        }

        //init buckets
        this_data->buckets.resize(N_BUCKETS_IN_THREAD);
        for(int j=0; j < N_BUCKETS_IN_THREAD; j++){
            this_data->buckets.emplace_back(std::vector<double>());
            this_data->buckets[j].reserve((int)1.5*TAB_SIZE*BUCKET_RANGE_STEP);
        }
    }
    double t_start = omp_get_wtime();
    
    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< N_THREADS; i++){
        thread_data* this_data = &threads_data[i];
        //put into buckets
        for(int j=0; j < TAB_SIZE; j++){
            int SEARCH_OFFSET = (TAB_SIZE/N_THREADS)*i;
            double val = tab[(j+SEARCH_OFFSET)%TAB_SIZE];
            //bucket search
            if( val >= this_data->buckets_thresholds[0] && val < this_data->buckets_thresholds[N_BUCKETS_IN_THREAD+1]){
                for(int k = 0; k< N_BUCKETS_IN_THREAD; k++){
                    if(val >= this_data->buckets_thresholds[k] && val < this_data->buckets_thresholds[k+1]){
                        this_data->buckets[k].emplace_back(val);
                    }
                }
            }
        }
        //sort in buckets
        for(int k = 0; k< N_BUCKETS_IN_THREAD; k++){
            std::sort(this_data->buckets[k].begin(), this_data->buckets[k].end());
            this_data->total_buckets_size += this_data->buckets[k].size(); 
        }
    }

    //calculate where each thread should start writing it's buckets
    for(int i = 1; i< N_THREADS; i++){
        threads_data[i].emplace_buckets_offset = threads_data[i-1].emplace_buckets_offset + threads_data[i-1].total_buckets_size;
    }

    //write buckets back
    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< N_THREADS; i++){
        thread_data* this_data = &threads_data[i];
        for(unsigned int k = 0; k< N_BUCKETS_IN_THREAD; k++){
            for(int j=0; j < this_data->buckets[k].size(); j++){
                tab[this_data->emplace_buckets_offset + j] =  this_data->buckets[k][j];
            } 
            this_data->emplace_buckets_offset += this_data->buckets[k].size();
        }
    }
        
    double t = omp_get_wtime() - t_start;
    printf("Time [s] \r\n %f \r\n",t);

    // for(int i=0; i<TAB_SIZE; i++){
    //     printf("%lf \n", tab[i]);
    // }

    printf("DONE\r\n");

    return 0;
}