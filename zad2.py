#!/usr/bin/python
from mpi4py import MPI
import sys

number_of_sends = int(sys.argv[1])



comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

data = 0
comm.barrier()
time1 = MPI.Wtime()
for i in range(0,1000):
    if (comm.rank == 0):
        comm.send(data, dest = 1, tag = 11)
        comm.recv( source = 0, tag = 12)
    if (comm.rank == 1):
        comm.recv( source = 0, tag = 11)
        comm.send(data, dest = 1, tag = 12)
time2 = MPI.Wtime()

with open('results.txt', 'w') as f:
    f.write(str(time2-time1) + "time passed")
    f.write('\n')
    f.write(str(time2-time1)/(number_of_sends *2) + "delay time in sec")
    f.write('\n')

