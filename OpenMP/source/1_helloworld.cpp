#include "1_helloworld.h"
#include <omp.h>
#include <stdio.h>
#include <math.h>


void hello_world()
{
	int nthreads, tid = 10;
	double t0, t1;
	omp_set_num_threads(4);
	t0 = omp_get_wtime();
#pragma omp parallel private(tid)
	{
		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d, Hello World!\n", tid,
			nthreads);
	}
	t1 = omp_get_wtime();
	printf("Time elapsed is %f.\nThat's all, folks!\n", t1 - t0);

	printf("\n\n");
	omp_set_num_threads(2);
#pragma omp parallel private(tid)
	{
		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d, Hello World!\n", tid,
			nthreads);
	}
	t1 = omp_get_wtime();
	printf("Time elapsed is %f.\nThat's all, folks!\n", t1 - t0);

	printf("\n\n");
	printf("Maximum thread use: %d\n", omp_get_max_threads());
}


#define PI25DT 3.141592653589793238462643

void calculate_PI() 
{
	int nthreads, tid, n, i;
	double pi, h, x, t0, t1;
	t0 = omp_get_wtime();
	n = 10000000;
	h = 1.0 / (double)n;
	pi = 0.0;
#pragma omp parallel default(shared) \
		private(tid, i, x) reduction(+:pi)
	{
		nthreads = omp_get_num_threads();
		tid = omp_get_thread_num();
		for (i = tid + 1; i <= n; i += nthreads) {
			x = h * ((double)i - 0.5);
			pi += 4.0 * h * sqrt(1. - x * x);
		}
	}
	t1 = omp_get_wtime();
	printf("Number of threads = %d\n", nthreads);
	printf("pi is approximately %.16f\n", pi);
	printf("Error is %.16f\n", fabs(pi - PI25DT));
	printf("Wall clock time = %f\n", t1 - t0);
}