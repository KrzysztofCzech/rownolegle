#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 1
#SBATCH --time=00:59:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22


 for i in {0..4}
    do
    ./omp_sort3 100000000 1 1
    ./omp_sort3 100000000 1 10
    ./omp_sort3 100000000 1 100
    ./omp_sort3 100000000 1 1000
    ./omp_sort3 100000000 1 10000
    ./omp_sort3 100000000 1 100000
    ./omp_sort3 100000000 1 1000000
    ./omp_sort3 100000000 1 10000000
    ./omp_sort3 100000000 1 20000000
    ./omp_sort3 100000000 1 50000000
    ./omp_sort3 100000000 1 80000000
    ./omp_sort3 100000000 1 10000000
done



