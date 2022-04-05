from subprocess import call 

for i in range(0,10):
    call(["./omp_dynamic", "1500000000", "1", "1000"])
    call(["./omp_dynamic", "1500000000", "2", "1000"])
    call(["./omp_dynamic", "1500000000", "3", "1000"])
    call(["./omp_dynamic", "1500000000", "4", "1000"])