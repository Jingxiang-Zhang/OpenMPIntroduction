#include "2_forloop.h"
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <random>
#include <chrono>


void forloop_demo1()
{
#pragma omp parallel
	{
		int i, j, N = 10, M = 3;
		int nthreads = omp_get_num_threads(); // get num of threads
		int tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d\n", tid,
			nthreads);

#pragma omp for
		for (i = 1; i <= N; i++) {
			int tid2 = omp_get_thread_num(); // get my thread id
			printf("    For loop from thread %d, for loop variable id = %d\n", tid2, i);
			if (tid != tid2) {
				printf("    tid not equal to tid2 !\n");
			}
		}

		for (j = 1; j <= M; j++) {
			int tid3 = omp_get_thread_num(); // get my thread id
			printf("This function run multiple time in each thread\n");
		}
	}
}

void forloop_demo2()
{
	int i;
#pragma omp parallel for
	for (i = 0; i <= 20; i++) {
		int nthreads = omp_get_num_threads(); // get num of threads
		int tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d\n", tid,
			nthreads);
	}
}

void forloop_private_value()
{
	int i, k;
	printf("Test:\n");
	k = 100;
	printf(" first k = %d\n", k);
#pragma omp parallel for lastprivate(k)
	for (i = 0; i < 10; i++) {
		k = i;
		printf("private k = % d\n", k);
	}
	printf(" last k = %d\n", k);
}

#define PI25DT 3.141592653589793238462643

void forloop_calculate_PI()
{
	int nthreads = 8, n, i;
	double pi, h, x, t0, t1;
	t0 = omp_get_wtime();
	n = 11111111;
	h = 1.0 / (double)n;
	pi = 0.0;
#pragma omp parallel for default(shared) \
		private(x) reduction(+:pi)
	for (i = 1; i <= n; i++) {
		x = h * ((double)i - 0.5);
		pi += 4.0 * h * sqrt(1. - x * x);
	}
	t1 = omp_get_wtime();
	printf("Number of threads = %d\n", nthreads);
	printf("pi is approximately %.16f\n", pi);
	printf("Error is %.16f\n", fabs(pi - PI25DT));
	printf("Wall clock time = %f\n", t1 - t0);
}

void forloop_ordered()
{
	int i, n = 10;
#pragma omp parallel for ordered
	for (i = 0; i < n; i++) {
		std::mt19937_64 rng;
		rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
		int time = (int)std::uniform_real_distribution<double>(0, 10000)(rng);
		Sleep(time);
#pragma omp ordered
		{
			// even if each thread have different sleep time, but they must
			// do the following code segement inorder
			printf("%d\n", i);
		}
	}
}