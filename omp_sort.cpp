#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

struct timer{
    double time_start;
    double time_fill_tab;
    double time_bucketing;
    double time_sort;
    double time_rewriting;
    double time_all;
};

struct thread_data{
    std::vector<std::vector<double>> buckets = std::vector<std::vector<double>>();
    std::vector<double> buckets_thresholds = std::vector<double>();
    long long total_buckets_size = 0;
    long long emplace_buckets_offset = 0;
};

void print_time(timer timer, unsigned long long int TAB_SIZE, unsigned long int N_THREADS , unsigned long int N_BUCKETS_IN_THREAD )
{
    timer.time_all =timer.time_all - timer.time_start;
    timer.time_rewriting = timer.time_rewriting - timer.time_sort;
    timer.time_sort = timer.time_sort  - timer.time_bucketing;
    timer.time_bucketing = timer.time_bucketing - timer.time_fill_tab;
    timer.time_fill_tab = timer.time_fill_tab - timer.time_start;


    std::cout << "\r\nRESULTS \r\n";
    
    std::cout << "TAB_SIZE,N_THREADS,N_BUCKETS_IN_THREAD,time_fill_tab,time_bucketing,time_sort,time_rewriting,time_all\r\n";
    
    std::cout << TAB_SIZE << ",";
    std::cout << N_THREADS << ",";
    std::cout << N_BUCKETS_IN_THREAD << ",";
    std::cout << timer.time_fill_tab << ",";
    std::cout << timer.time_bucketing << ",";
    std::cout << timer.time_sort << ",";
    std::cout << timer.time_rewriting << ",";
    std::cout << timer.time_all << "\r\n";

}

int main(int argc, char *argv[]){
    struct timer timer;
    char* pEnd;
    unsigned long long int TAB_SIZE = strtoull(argv[1],&pEnd, 10);
    unsigned long int N_THREADS = strtoul(argv[2], &pEnd, 10);
    unsigned long int N_BUCKETS_IN_THREAD = strtoul(argv[3], &pEnd, 10);
    double BUCKET_RANGE_STEP = (1.0)/((double)(N_BUCKETS_IN_THREAD*N_THREADS));

    std::vector<double> tab = std::vector<double>(TAB_SIZE);
    std::vector<thread_data> threads_data = std::vector<thread_data>(N_THREADS);

    // printf("TAB_SIZE : \r\n %llu \r\n",TAB_SIZE);
    // printf("N_THREADS : \r\n %lu \r\n",N_THREADS);
    // printf("N_BUCKETS_IN_THREAD : \r\n %lu \r\n",N_BUCKETS_IN_THREAD);
    // printf("BUCKET_RANGE_STEP : \r\n %f\r\n",BUCKET_RANGE_STEP);

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
    timer.time_start = omp_get_wtime();
    
    //init random array
    long TSEED = time(NULL);
    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< TAB_SIZE; i++){
        uint seed = 25233 + TAB_SIZE * omp_get_thread_num() + TSEED*(i+1)*301;
        tab[i] = (double)rand_r(&seed)/(double)RAND_MAX;
    }
    timer.time_fill_tab =  omp_get_wtime();

    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< N_THREADS; i++){
        thread_data* this_data = &threads_data[i];
        double val;
        int SEARCH_OFFSET;
        unsigned long int index;
        //put into buckets
        for(int j=0; j < TAB_SIZE; j++){
            SEARCH_OFFSET = (TAB_SIZE/N_THREADS)*i;
            val = tab[(j+SEARCH_OFFSET)%TAB_SIZE];
            //bucket search
            if( val >= this_data->buckets_thresholds[0] && val < this_data->buckets_thresholds[N_BUCKETS_IN_THREAD]){
                index = (unsigned long int)((val - this_data->buckets_thresholds[0])/BUCKET_RANGE_STEP);
                this_data->buckets[index].emplace_back(val);
            }
        }
    }

    timer.time_bucketing =  omp_get_wtime();

    #pragma omp parallel for num_threads(N_THREADS)
    for(int i = 0; i< N_THREADS; i++){
        unsigned long int max_size = 0;
        thread_data* this_data = &threads_data[i];
        //sort in buckets
        for(int k = 0; k< N_BUCKETS_IN_THREAD; k++){
            std::sort(this_data->buckets[k].begin(), this_data->buckets[k].end());
            this_data->total_buckets_size += this_data->buckets[k].size(); 
            if(max_size < this_data->buckets[k].size()) { max_size = this_data->buckets[k].size();}
        }
        std::cout <<  "max bucket size " << max_size << "\n";
    }


    timer.time_sort =  omp_get_wtime();

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
    timer.time_rewriting =  omp_get_wtime();
    timer.time_all =  omp_get_wtime();

    for(int i=0; i<TAB_SIZE -1; i++){
        if(tab[i] > tab[i+1]){
            std::cout <<" NOT SORTED \n";
        }
    }

    printf("DONE\r\n");

    print_time(timer, TAB_SIZE, N_THREADS, N_BUCKETS_IN_THREAD );

    return 0;
}