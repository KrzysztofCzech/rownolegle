#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 1
#SBATCH --time=00:05:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


./omp_sort 100 1 1
./omp_sort 100 1 10


