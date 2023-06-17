#include "3_other_structure.h"
#include <omp.h>
#include <stdio.h>
#include "sleep.h"


void section_demo()
{
	int nthreads, tid;
#pragma omp parallel sections
	{
#pragma omp section
		{
			nthreads = omp_get_num_threads(); // get num of threads
			tid = omp_get_thread_num(); // get my thread id
			printf("From thread %d out of %d\n", tid, nthreads);
		}

#pragma omp section
		{
			nthreads = omp_get_num_threads(); // get num of threads
			tid = omp_get_thread_num(); // get my thread id
			printf("From thread %d out of %d\n", tid, nthreads);
		}
	}
}

void single_keyword()
{
	int nthreads, tid;
#pragma omp parallel
	{
		random_sleep();
		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d\n", tid, nthreads);

#pragma omp single
		{
			printf("This section will only run once\n");
		}

		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d - part2\n", tid, nthreads);
	}
}


void single_keyword_nowait()
{
	int nthreads, tid;
#pragma omp parallel
	{
		random_sleep();
		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d\n", tid, nthreads);

#pragma omp single nowait
		{
			printf("This section will only run once\n");
		}

		nthreads = omp_get_num_threads(); // get num of threads
		tid = omp_get_thread_num(); // get my thread id
		printf("From thread %d out of %d - part2\n", tid, nthreads);
	}

}

int a = 0, b = 0;
#pragma omp threadprivate(a)
void threadprivate_keyword()
{
	int tid;
	omp_set_dynamic(0);

	printf("1st Parallel Region:\n");
#pragma omp parallel num_threads(4) private(tid, b)
	{
		tid = omp_get_thread_num();
		a = tid + 10;
		b = tid + 2;
		printf("Thread %d: a = %d, b = %d\n", tid, a, b);
	}
	printf("In main thread: a = %d, b = %d\n", a, b);

	printf("2nd Parallel Region:\n");
#pragma omp parallel num_threads(4) private(tid)
	{
		tid = omp_get_thread_num();
		printf("Thread %d: a = %d, b = %d\n", tid, a, b);
	}

}

int counter = 0;
#pragma omp threadprivate(counter)

void copyin_keyword()
{
	int tid;
	omp_set_dynamic(0);
	omp_set_num_threads(4);
	counter = 10;
	printf("1st Parallel Region, without copyin:\n");
#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		printf("ThreadId: %d, count = %d\n", tid, counter);
	}

	printf("2nd Parallel Region, with copyin:\n");
#pragma omp parallel private(tid) copyin(counter)
	{
		tid = omp_get_thread_num();
		printf("ThreadId: %d, count = %d\n", tid, counter);
	}
}

void copyprivate_keyword()
{
	int tid;
	omp_set_dynamic(0);
	omp_set_num_threads(4);

	printf("1st Parallel Region, without copyprivate:\n");
#pragma omp parallel private(tid)
	{
#pragma omp single
		{
			counter = 10;
		}
		tid = omp_get_thread_num();
		printf("In the single section, ThreadId: %d, count = %d\n", tid, counter);
	}

	printf("2nd Parallel Region, with copyprivate:\n");
#pragma omp parallel private(tid)
	{
#pragma omp single copyprivate(counter)
		{
			counter = 20;
		}
		tid = omp_get_thread_num();
		printf("In the single section, ThreadId: %d, count = %d\n", tid, counter);
	}
}