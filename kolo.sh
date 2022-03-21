#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 4
#SBATCH --time=00:10:00
#SBATCH --partition=plgrid-short
#SBATCH --account=plgmpr22

module add plgrid/tools/openmpi
module load plgrid/libs/python-mpi4py/3.0.1-python-3.6
module add plgrid/libs/python-mpi4py/3.0.0-python-2.7
mpiexec -np 1 ./pole_kola.py 100000
mpiexec -np 2 ./pole_kola.py 100000
mpiexec -np 3 ./pole_kola.py 100000
mpiexec -np 4 ./pole_kola.py 100000
mpiexec -np 5 ./pole_kola.py 100000
mpiexec -np 6 ./pole_kola.py 100000
mpiexec -np 7 ./pole_kola.py 100000
mpiexec -np 8 ./pole_kola.py 100000
mpiexec -np 9 ./pole_kola.py 100000
mpiexec -np 10 ./pole_kola.py 100000
mpiexec -np 11 ./pole_kola.py 100000
mpiexec -np 12 ./pole_kola.py 100000