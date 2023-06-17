#ifdef _OPENMP
#include <omp.h> // omp header file
#else
	#define omp_set_num_threads(x) 0
	#define omp_get_num_threads() 1
	#define omp_get_thread_num() 0
#endif

#include "1_helloworld.h"
#include "2_forloop.h"
#include "3_other_structure.h"
#include "4_data_dependence.h"
#include "5_synchronization.h"


/*****************************************************************************
 to run the code in visual studio, you need to:
 1. Go into the project properties window,
 2. navigate to the "Configuration Properties" -> "C/C++" -> "Language" section.
 3. Set the "Open MP Support" property to "Yes" (/openmp).

 The following part are not covered in this introduction: atomic keyword,
 orphaning situation, task parallelism, dynamic thread, nested parallelism,
 flush keyword, stack size, thread affinity and binding, vectorization and SIMD,
 false sharing, mutex lock, custom reduction, OpenMP4.0, OpenMP 5.0, and so forth
*****************************************************************************/

int main()
{
	// 1. first example of OpenMP
	hello_world();
	// calculate_PI();

	// 2. for loop
	// forloop_demo1();
	// forloop_demo2();
	// forloop_private_value();
	// forloop_calculate_PI();
	// forloop_ordered();

	// 3. work sharing construct
	// section_demo();
	// single_keyword();
	// single_keyword_nowait();
	// threadprivate_keyword();
	// copyin_keyword();
	// copyprivate_keyword();

	// 4. data dependency and eliminate
	// data_dependency_and_eliminate();

	// 5. synchronization construct
	// barrier_demo();
	// master_demo();
	// critical_demo();
}
