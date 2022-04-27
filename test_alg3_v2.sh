#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:30:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


 for i in {0..5}
    do
./omp_sort3 100000000 1 5000000
./omp_sort3 100000000 2 5000000
./omp_sort3 100000000 3 5000000
./omp_sort3 100000000 4 5000000
./omp_sort3 100000000 5 5000000
./omp_sort3 100000000 6 5000000
./omp_sort3 100000000 7 5000000
./omp_sort3 100000000 8 5000000
done






