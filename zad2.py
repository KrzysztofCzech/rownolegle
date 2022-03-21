#!/usr/bin/python
from mpi4py import MPI
import sys

number_of_sends = int(sys.argv[1])
comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

data = 0
buff = bytearray(256)
comm.barrier()
time1 = MPI.Wtime()
for i in range(0,number_of_sends):
    if (comm.rank == 0):
        MPI.Attach_buffer(buff)
        comm.bsend(data, dest = 1, tag = 11)
        MPI.Detach_buffer()
    if (comm.rank == 1):
        data = comm.recv( source = 0, tag = 11)
time2 = MPI.Wtime()

if(comm.rank == 0):
    with open('results_bsend.txt', 'w') as f:
        f.write(str(time2-time1) + "time passed")
        f.write('\n')
        f.write(str((time2-time1)/(number_of_sends *2)) + "delay time in sec")
        f.write('\n')

comm.barrier()
time1 = MPI.Wtime()
for i in range(0,number_of_sends):
    if (comm.rank == 0):
        req = comm.isend(data, dest = 1, tag = 11)
        req.wait()
    if (comm.rank == 1):
        req = comm.irecv(tag = 11)
        data = req.wait()
time2 = MPI.Wtime()

if(comm.rank == 0):
    with open('results_isend.txt', 'w') as f:
        f.write(str(time2-time1) + "time passed")
        f.write('\n')
        f.write(str((time2-time1)/(number_of_sends *2)) + "delay time in sec")
        f.write('\n')



