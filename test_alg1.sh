#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:50:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


./omp_sort 1000000000 1 80000000
./omp_sort 1000000000 2 40000000
./omp_sort 1000000000 3 26666600
./omp_sort 1000000000 4 20000000
./omp_sort 1000000000 5 16000000
./omp_sort 1000000000 6 13333300
./omp_sort 1000000000 7 11428500
./omp_sort 1000000000 8 10000000





