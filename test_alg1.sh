#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:20:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


./omp_sort 100000000 1 8000000
./omp_sort 100000000 2 4000000
./omp_sort 100000000 3 2666660
./omp_sort 100000000 4 2000000
./omp_sort 100000000 5 1600000
./omp_sort 100000000 6 1333330
./omp_sort 100000000 7 1142850
./omp_sort 100000000 8 1000000





