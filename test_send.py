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
buff = bytearray(64)
MPI.Attach_buffer(buff)
if mode == 1:
    if (comm.rank == 0):
        comm.bsend(data, dest = 0, tag = 11)
    if (comm.rank == 1):
        data = comm.recv( source = 0, tag = 11)
        print("Data received mode 1")
time2 = MPI.Wtime()

if mode == 0:
    if (comm.rank == 0):
        comm.Ssend(data, dest = 0, tag = 11)
    if (comm.rank == 1):
        data = comm.recv( source = 0, tag = 11)
        print("Data received mode 0")


