#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct VSumArgs {
	size_t start;
	size_t stop;
	size_t step;
	double *v;
	pthread_mutex_t *sum_mutex;
	double *sum;
};

void *threaded_vsum(void *args)
{
	size_t start = ((struct VSumArgs *)args)->start;
	size_t stop = ((struct VSumArgs *)args)->stop;
	size_t step = ((struct VSumArgs *)args)->step;
	double *v = ((struct VSumArgs *)args)->v;
	pthread_mutex_t *sum_mutex = ((struct VSumArgs *)args)->sum_mutex;
	double *sum = ((struct VSumArgs *)args)->sum;
	double psum = 0.0;
	for (size_t i = start; i < stop; i += step) {
		psum += v[i];
	}
	pthread_mutex_lock(sum_mutex);
	*sum += psum;
	pthread_mutex_unlock(sum_mutex);
	return NULL;
}

#define NUM_THREADS 8
double vsum(double *v, size_t N)
{
	pthread_mutex_t sum_mutex;
	pthread_mutex_init(&sum_mutex, NULL);
	struct VSumArgs args[NUM_THREADS];
	double sum = 0.0;
	for (int i = 0; i < NUM_THREADS; i++) {
		args[i].start = i;
		args[i].stop = N;
		args[i].step = NUM_THREADS;
		args[i].v = v;
		args[i].sum_mutex = &sum_mutex;
		args[i].sum = &sum;
	}
	pthread_t threads[NUM_THREADS];
	for (int k = 0; k < NUM_THREADS; k++) {
		pthread_create(&threads[k], NULL, threaded_vsum, &args[k]);
	}
	for (int k = 0; k < NUM_THREADS; k++) {
		pthread_join(threads[k], NULL);
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
