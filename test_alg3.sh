#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:30:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

 for i in {0..5}
    do
./omp_sort3 100000000 1 8000000
./omp_sort3 100000000 2 8000000
./omp_sort3 100000000 3 8000000
./omp_sort3 100000000 4 8000000
./omp_sort3 100000000 5 8000000
./omp_sort3 100000000 6 8000000
./omp_sort3 100000000 7 8000000
./omp_sort3 100000000 8 8000000
done





