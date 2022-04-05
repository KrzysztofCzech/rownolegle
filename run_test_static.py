from subprocess import call 

for i in range(0,10):
    call(["./omp_static", "1500000000", "1", "1000"])
    call(["./omp_static", "1500000000", "2", "1000"])
    call(["./omp_static", "1500000000", "3", "1000"])
    call(["./omp_static", "1500000000", "4", "1000"])
    call(["./omp_static", "1500000000", "1", "1"])
    call(["./omp_static", "1500000000", "2", "1"])
    call(["./omp_static", "1500000000", "3", "1"])
    call(["./omp_static", "1500000000", "4", "1"])
    call(["./omp_static", "1500000000", "1", "1000000"])
    call(["./omp_static", "1500000000", "2", "1000000"])
    call(["./omp_static", "1500000000", "3", "1000000"])
    call(["./omp_static", "1500000000", "4", "1000000"])