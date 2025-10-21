#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double vsum(double *v, size_t N)
{
	double sum = 0;
#pragma omp parallel
	{
		size_t id = omp_get_thread_num();
		size_t num = omp_get_num_threads();
		double psum = 0.0;
		for (size_t i = id; i < N; i += num) {
			psum += v[i];
		}
#pragma omp critical
		{
			sum += psum;
		}
	}
	return sum;
}

int main(int argc, char **argv)
{
	size_t N;
	assert(sscanf(argv[1], "%zu", &N) == 1);
	printf("Summing over %zu indices\n", N);
	double *v = (double *)malloc(N * sizeof(double));
	for (size_t i = 0; i < N; ++i) {
		v[i] = 1.0;
	}
	double sum = vsum(v, N);
	printf("Sum is : %lf\n", sum);
	return EXIT_SUCCESS;
}
