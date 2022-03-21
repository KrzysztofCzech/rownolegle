#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 4
#SBATCH --time=00:10:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

module add plgrid/tools/openmpi

mpiexec -np 4 ./pole_kola.py 10000