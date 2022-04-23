#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 1
#SBATCH --time=00:50:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


./omp_sort 100000000 1 1
./omp_sort 100000000 1 10
./omp_sort 100000000 1 100
./omp_sort 100000000 1 1000
./omp_sort 100000000 1 10000
./omp_sort 100000000 1 100000
./omp_sort 100000000 1 1000000
./omp_sort 100000000 1 2000000
./omp_sort 100000000 1 10000000
./omp_sort 100000000 1 20000000
./omp_sort 100000000 1 40000000
./omp_sort 100000000 1 80000000
./omp_sort 100000000 1 90000000
./omp_sort 100000000 1 100000000

