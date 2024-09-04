#include <stdio.h>     // For printing to the console
#include <stdlib.h>    // For memory allocation (malloc), string to integer
		       // converion (atoi), and generating random numbers (rand)
#include <sys/time.h>  // For implementing a chrono (struct timeval and
#include <time.h>      // For time() function used in random seed generation
		       // gettimeofday). Requires a POSIX OS.

void matrix_product_v1(float *__restrict C, const float *A, const float *B,
		       int N) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
			for (int k = 0; k < N; k++) {
				/* Update C_ {i , j } */
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
}

void matrix_product_v2(float *__restrict C, const float *A, const float *B,
		       int N) {
	for (int i = 0; i < N; ++i) {
		/* Zero initialize C */
		for (int j = 0; j < N; j++) {
			C[i * N + j] = 0;
		}
		for (int k = 0; k < N; k++) {
			for (int j = 0; j < N; j++) {
				/* Update C_ {i , j } */
				C[i * N + j] += A[i * N + k] * B[k * N + j];
			}
		}
	}
}

void timer_start(struct timeval *tv) { gettimeofday(tv, NULL); }

unsigned int timer_stop(const struct timeval *tv, const char *str) {
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned int mus = 1000000 * (now.tv_sec - tv->tv_sec);
	mus += (now.tv_usec - tv->tv_usec);
	if (str[0]) {
		printf("Timer %s: ", str);
		if (mus >= 1000000) {
			printf("%.3f s\n", (float)mus / 1000000);
		} else {
			printf("%.3f ms\n", (float)mus / 1000);
		}
	}
	return (mus);
}

/* When profiling with compiler optimization, it is important to ''do''
 * something with the result, all of it, in order to prevent the smart
 * compiler from just no computing what is not latter used.
 */
float check_and_avoid_lazy_optimizers(const float *C, int N) {
	float dummy = 0;
	for (int i = 0; i < N * N; ++i) {
		dummy += C[i];
	}
	return dummy;
}

/* We initialize A and B with random numbers in the interval [0,1] */
void initialize_matrices(float *A, float *B, int N) {
	srand(time(NULL));
	for (int i = 0; i < N * N; ++i) {
		A[i] = (double)rand() / RAND_MAX;
		B[i] = (double)rand() / RAND_MAX;
	}
}

int main(int argc, char **argv) {
	/* Read 1st program argument string and convert into a number*/
	int N = atoi(argv[1]);
	if (N <= 0) {
		printf("First argument N must be positive.\n");
		return (EXIT_FAILURE);
	}

	/* Allocate memory for storing A, B, and the resulting C = A * B */
	float *A = (float *)aligned_alloc(32, N * N * sizeof(float));
	float *B = (float *)aligned_alloc(32, N * N * sizeof(float));
	float *C = (float *)aligned_alloc(32, N * N * sizeof(float));
	if (A == NULL || B == NULL || C == NULL) {
		printf("Memory allocation failed ($N$ too large ?)\n");
		return (EXIT_FAILURE);
	}

	/* For measuring timings of both algorithm */
	struct timeval chrono;

	/* Test 1 */
	initialize_matrices(A, B, N);
	timer_start(&chrono);
	matrix_product_v1(C, A, B, N);
	timer_stop(&chrono, "Algo 1");
	printf("Sum of C : %f\n", check_and_avoid_lazy_optimizers(C, N));

	/* Test 2 */
	// initialize_matrices(A, B, N);
	timer_start(&chrono);
	matrix_product_v2(C, A, B, N);
	timer_stop(&chrono, "Algo 2");
	printf("Sum of C : %f\n", check_and_avoid_lazy_optimizers(C, N));

	/* Release memory to OS */
	free(C);
	free(B);
	free(A);

	return (EXIT_SUCCESS);
}
