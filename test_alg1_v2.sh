#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 8
#SBATCH --time=00:30:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

 for i in {0..5}
    do

./omp_sort 100000000 1 5000000
./omp_sort 100000000 2 2500000
./omp_sort 100000000 3 1666660
./omp_sort 100000000 4 1250000
./omp_sort 100000000 5 1000000
./omp_sort 100000000 6 833330
./omp_sort 100000000 7 714280
./omp_sort 100000000 8 625000
done






