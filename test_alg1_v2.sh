#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:50:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

./omp_sort 1000000000 1 50000000
./omp_sort 1000000000 2 25000000
./omp_sort 1000000000 3 16666600
./omp_sort 1000000000 4 12500000
./omp_sort 1000000000 5 10000000
./omp_sort 1000000000 6 8333300
./omp_sort 1000000000 7 7142800
./omp_sort 1000000000 8 6250000






