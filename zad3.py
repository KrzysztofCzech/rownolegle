#!/usr/bin/python
from mpi4py import MPI
import sys

from numpy import equal

cycles_num = int(sys.argv[1])

data_to_send = [0] * 20 
buff = []
res = []
size_list = []
comm = MPI.COMM_WORLD

if comm.size < 2:
    print("err world to small")

for i in range(0,cycles_num):
    comm.barrier()
    time1 = MPI.Wtime()
    if (comm.rank == 0):
        comm.send(buff, dest = 1, tag = 11)
    if (comm.rank == 1):
        data = comm.recv( source = 0, tag = 11)
    comm.barrier()
    time2 = MPI.Wtime()
    size = sys.getsizeof(buff)
    res.append(int(size/(time2 - time1)))
    size_list.append(size)
    buff.extend(data_to_send)

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
    with open('results.txt', 'w') as f:
        f.write('Speed rates in b/s\n')
        f.write(",".join(map(str,speed_rates)))
        f.write('\n')
        f.write('Sizes in b\n')
        f.write(','.join(map(str,sizes_final)))
        f.write('\n')



