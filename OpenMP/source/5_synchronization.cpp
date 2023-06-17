#include "5_synchronization.h"
#include <omp.h>
#include <stdio.h> 
#include "sleep.h"



void barrier_demo()
{
	int nthreads, tid;
#pragma omp parallel
	{
		random_sleep();
#pragma omp barrier
		nthreads = omp_get_num_threads();
		tid = omp_get_thread_num();
		printf("From thread %d out of %d\n", tid, nthreads);
	}

}


void master_demo()
{
	int nthreads, tid;
#pragma omp parallel
	{
		random_sleep();
#pragma omp master
		{
			nthreads = omp_get_num_threads();
			tid = omp_get_thread_num();
			printf("From thread %d out of %d\n", tid, nthreads);
		}
	}

}

void critical_demo()
{
	int count = 0;
	int num = 1000000;
	int nthread = 10;
#pragma omp parallel num_threads(nthread)
	{
		for (int i = 0; i < num; i++) {
			count++;
		}
	}
	printf("In the first case, count = %d, which should be %d\n", count, num * nthread);

	count = 0;
#pragma omp parallel num_threads(nthread)
	{
#pragma omp critical
		for (int i = 0; i < num; i++) {
			count++;
		}
	}
	printf("In the second case, count = %d, which should be %d\n", count, num * nthread);

	count = 0;
#pragma omp parallel num_threads(nthread)
	{
		for (int i = 0; i < num; i++) {
#pragma omp critical
			count++;
		}
	}
	printf("In the third case, count = %d, which should be %d\n", count, num * nthread);
}
