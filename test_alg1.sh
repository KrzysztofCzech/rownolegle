#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:50:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

./omp_sort3 1000000000 1 50000000
./omp_sort3 1000000000 2 50000000
./omp_sort3 1000000000 3 50000000
./omp_sort3 1000000000 4 50000000
./omp_sort3 1000000000 5 50000000
./omp_sort3 1000000000 6 50000000
./omp_sort3 1000000000 7 50000000
./omp_sort3 1000000000 8 50000000






