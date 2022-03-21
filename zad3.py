#!/usr/bin/python
from mpi4py import MPI
import sys

from numpy import equal

cycles_num = int(sys.argv[1])

data = [0] *30 
data_to_send = []
res = []
size_list = []
comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

for i in range(0,cycles_num):
    size = sys.getsizeof(data_to_send)
    buff = bytearray(size)
    comm.barrier()
    time1 = MPI.Wtime()
    if (comm.rank == 0):
        MPI.Attach_buffer(buff)
        comm.bsend(data_to_send, dest = 1, tag = 11)
        MPI.Detach_buffer()
    if (comm.rank == 1):
        data_to_send = comm.recv( source = 0, tag = 11)
    comm.barrier()
    time2 = MPI.Wtime()
    res.append(int(size/(time2 - time1)))
    size_list.append(size)
    data_to_send.extend(data)

#get average speed rate for duplicated size
prev_size = size_list[0]
acc= 0
num = 0
speed_rates =[]
sizes_final = []
for i in range(0,len(size_list)):
    if prev_size  != size_list[i]:
        speed_rates.append( acc/num)
        sizes_final.append(prev_size)
        acc = 0
        num = 0
    prev_size = size_list[i]
    acc += res[i]
    num +=1

speed_rates.append( acc/num)
sizes_final.append(prev_size)


if(comm.rank == 0):
    with open('results_bsend.txt', 'w') as f:
        f.write('Speed rates in b/s\n')
        f.write(",".join(map(str,speed_rates)))
        f.write('\n')
        f.write('Sizes in b\n')
        f.write(','.join(map(str,sizes_final)))
        f.write('\n')

data = [0] *30 
data_to_send = []
res = []
size_list = []

for i in range(0,cycles_num):
    size = sys.getsizeof(data_to_send)
    comm.barrier()
    time1 = MPI.Wtime()
    if (comm.rank == 0):
        req = comm.isend(data_to_send, dest = 1, tag = 11)
        req.wait()
    if (comm.rank == 1):
        req = comm.irecv(tag = 11)
        data_to_send = req.wait()
    comm.barrier()
    time2 = MPI.Wtime()
    res.append(int(size/(time2 - time1)))
    size_list.append(size)
    data_to_send.extend(data)

#get average speed rate for duplicated size
prev_size = size_list[0]
acc= 0
num = 0
speed_rates =[]
sizes_final = []
for i in range(0,len(size_list)):
    if prev_size  != size_list[i]:
        speed_rates.append( acc/num)
        sizes_final.append(prev_size)
        acc = 0
        num = 0
    prev_size = size_list[i]
    acc += res[i]
    num +=1

speed_rates.append( acc/num)
sizes_final.append(prev_size)


if(comm.rank == 0):
    with open('results_isend.txt', 'w') as f:
        f.write('Speed rates in b/s\n')
        f.write(",".join(map(str,speed_rates)))
        f.write('\n')
        f.write('Sizes in b\n')
        f.write(','.join(map(str,sizes_final)))
        f.write('\n')




