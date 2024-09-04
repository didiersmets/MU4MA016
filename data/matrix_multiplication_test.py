import numpy
import time

for N in (10, 20, 50, 100, 200):

    A = numpy.random.random((N, N)).astype(numpy.float32)
    B = numpy.random.random((N, N)).astype(numpy.float32)
    C = numpy.zeros((N,N)).astype(numpy.float32)

    if (N <= 200):
        start = time.time()
        for i in range(N):
            for k in range(N):
                for j in range(N):
                    C[i,j] += A[i,k] * B[k,j]
        end = time.time()
        print("Pure Python for N = %4d : %.5fs" % (N, end - start))

for N in (1000, 2000, 4000):

    A = numpy.random.random((N, N)).astype(numpy.float32)
    B = numpy.random.random((N, N)).astype(numpy.float32)
    C = numpy.zeros((N,N)).astype(numpy.float32)

    start = time.time()
    tests = int(10000 / N) + 1
    for i in range(tests):
        C = A.dot(B)
    end = time.time()
    print("Using Numpy for N = %4d : %.5fs" % (N, (end - start) / tests))
