#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

unsigned seed;


int main(int argc, char *argv[]){
    // if(argc < 3){
    //     print("invalid arg count");
    //     return -1;
    // }
    char* pEnd;
    unsigned long long int TAB_SIZE = strtoull(argv[1],&pEnd, 10);
    unsigned long int N_THREADS = strtoul(argv[2], &pEnd, 10);
    unsigned long long int CHUNK_SIZE = 1000;//strtoull(argv[3], &pEnd, 10);


    printf("TAB_SIZE : \r\n %llu \r\n",TAB_SIZE/10);
    printf("N_THREADS : \r\n %lu \r\n",N_THREADS);
    printf("CHUNK_SIZE : \r\n %llu \r\n",CHUNK_SIZE);
    
    double* tab = (double*) malloc(TAB_SIZE * sizeof(double));
    if(tab == NULL){
        printf("Couldn't malloc tab");
        return -1;
    }
    double t_start = omp_get_wtime();


    #pragma omp threadprivate(seed)
    //#pragma omp parallel for num_threads(N_THREADS) schedule(static, CHUNK_SIZE)
    #pragma omp parallel for num_threads(N_THREADS) schedule(guided, CHUNK_SIZE)    
    for(int i = 0; i< TAB_SIZE; i++){
        seed = 25234 + 17 * omp_get_thread_num();

        tab[i] = rand_r(&seed);
        // unsigned long thread_num = omp_get_thread_num();
        // unsigned long block_size = (TAB_SIZE/N_THREADS);
        // unsigned long block_start = block_size*thread_num;
        // unsigned long block_end = block_size*(thread_num+1);
        // if(thread_num == N_THREADS -1){
        //     block_end = TAB_SIZE;
        // }
        // printf("Thread %d starting\r\n",thread_num);

        
        // int i = 0;
        // for(i = block_start; i< block_end; i++){
        //     tab[i] = 1;
        // }
        // printf("Thread %d done\r\n",thread_num);
        
    }

    double t = omp_get_wtime() - t_start;
    printf("Time \r\n %f \r\n",t);

    free(tab);

    printf("DONE\r\n");
    return 0;
}