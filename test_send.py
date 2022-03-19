#!/usr/bin/python
from mpi4py import MPI
import sys

mode = int(sys.argv[1])

comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

data = 0
comm.barrier()
time1 = MPI.Wtime()
if mode == 1:
    if (comm.rank == 0):
        comm.bsend(data, dest = 0, tag = 11)
        print("works")
        # data = comm.recv( source = 1, tag = 12)
#     if (comm.rank == 1):
#         data = comm.recv( source = 0, tag = 11)
#         comm.send(data, dest = 0, tag = 12)
# time2 = MPI.Wtime()

