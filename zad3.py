#!/usr/bin/python
from mpi4py import MPI
import sys

cycles_num = int(sys.argv[1])

data_to_send = [0,0,0,0] 
buff = []
res = []
size_list = []
comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

for i in range(0,cycles_num):
    buff.append(data_to_send)
    comm.barrier()
    time1 = MPI.Wtime()
    if (comm.rank == 0):
        comm.send(buff, dest = 1, tag = 11)
    if (comm.rank == 1):
        data = comm.recv( source = 0, tag = 11)
    comm.barrier()
    time2 = MPI.Wtime()
    size = sys.getsizeof(buff)
    res.append(size/(time2 - time1))
    size_list.append(size)


if(comm.rank == 0):
    with open('results.txt', 'w') as f:
        f.write(",".join(map(str,size_list)))
        f.write('\n')
        f.write(','.join(map(str,res)))
        f.write('\n')

