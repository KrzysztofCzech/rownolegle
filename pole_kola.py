import random
from mpi4py import MPI
import sys

comm = MPI.COMM_WORLD
def check_in_circle(x,y):
    return (x**2 + y**2) < 1

def set_seed(rank):
    base = 34
    random.seed = base * rank + 11

buff = list()
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


comm.Reduce(circle_count, buff, MPI.SUM, 0)
time2 = MPI.Wtime()

if (comm.rank == 0):
    pi = 4.0*buff/npoints
    print("Pi wynosi " + str(pi))
    print("czas = " + str(time1 - time2))