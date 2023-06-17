#pragma once

/*****************************************************************************
in the follow sentence
#pragma omp parallel private(tid)
#pragma omp is unchanged, parallel is the directive name, all the following is the clause
It allows multiple clause, and all of the clauses are unordered, can use \ for multiple lines

clause type:
1. if (scalar_expression)
   if(true), i.e., not zero, then execute in parallel. else execute in series.
2. private (list)
   private variable list, all of the provided variable is independent of each thread
3. shared (list)
   shared variable list. need to make sure thread safety
4. default (shared | none)
   set default variable type
5. firstprivate (list)
   similar to private (list), but initialize the variable by the main thread variable
6. reduction (operator: list)
   similar to private (list), but provide a thread safe operator, see the next example
7. copyin (list)
8. num_threads (integer_expression)
   one way to set the thread. thread can be set by (from low priority to high priority):
	   system default
	   OMP_NUM_THREADS variable
	   omp_set_num_threads() function
	   num_threads clause
	   if clause

*****************************************************************************/

void hello_world();

void calculate_PI();