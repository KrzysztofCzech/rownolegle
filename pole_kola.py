#!/usr/bin/python
import random
from mpi4py import MPI
import sys
import array

comm = MPI.COMM_WORLD
def check_in_circle(x,y):
    return (x**2 + y**2) < 1

def set_seed(rank):
    base = 34
    random.seed = base * rank + 11

buff = array.array("I", [0])
npoints = int(sys.argv[1])
print("size" + str(comm.size))

npoints_per_node = npoints // comm.size

circle_count = 0
set_seed(comm.rank)
comm.barrier()
time1 = MPI.Wtime()
for i in range(0,npoints_per_node):
    xcoordinate = random.uniform(0,1)
    ycoordinate = random.uniform(0,1)
    if check_in_circle(xcoordinate, ycoordinate):
        circle_count = circle_count + 1
send_buf = array.array("I",[circle_count])

# if comm.rank != 0:
#     comm.Reduce(send_buf,None, op = MPI.SUM, root = 0)
# else:
comm.Reduce(send_buf,[buff,MPI.INT], op = MPI.SUM, root = 0)
time2 = MPI.Wtime()

if (comm.rank == 0):
    pi = 4.0*buff[0]/npoints
    print("Pi wynosi " + str(pi))
    print("czas = " + str(time2 - time1))