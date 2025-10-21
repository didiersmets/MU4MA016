#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

double vsum(double *v, size_t N)
{
	double sum = 0;
#pragma omp parallel
#pragma omp for reduction(+ : sum)
	for (size_t i = 0; i < N; i++) {
		sum += v[i];
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
