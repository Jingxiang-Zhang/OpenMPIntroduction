#include "4_data_dependence.h"
#include <omp.h>
#include <stdio.h>

void data_dependency_and_eliminate()
{
	int x;
	int a[100] = { 0 };
	int b[100] = { 0 };
	int c[100] = { 0 };

	// code that have data dependency
#pragma omp parallel for
	for (int i = 0; i < 99; i++) {
		x = b[i] + c[i];
		a[i] = a[i + 1] + x;
	}

	// remove x dependency
#pragma omp parallel for
	for (int i = 0; i < 99; i++) {
		a[i] = a[i + 1] + b[i] + c[i];
	}

	// use private x
		// remove x
#pragma omp parallel for lastprivate(x)
	for (int i = 0; i < 99; i++) {
		x = b[i] + c[i];
		a[i] = a[i + 1] + x;
	}
}
