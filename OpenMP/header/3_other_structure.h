#pragma once

/*****************************************************************************
sections allow user to define multiple code segment, and each segment will be
allocated to one thread and execute. The following example have two code segment,
and these two segments will be executed by different thread. The relationship between
the number of thread and the number of section:
1. number of thread > number of section: some thread have no work to do
2. number of thread = number of section: each thread allocate one section
3. number of thread < number of section: some thread have multiple section to do
note that the allocation is random.

*****************************************************************************/

void section_demo();

/*****************************************************************************
single keyword: single section can be inside the parallel section, and require the following
single section run only once. For the following example, there are 3 parts:
1. random sleep part: before single section
2. single thread part
3. after single thread part
In this example, N thread will be created, and all of the thread will start to run the first part,
the first finish thread will go to execute the single thread part, and all of the other thread
will skip the second part. And all of the thread will wait until all of thread go into the third
part, and start to execute at the same time. Run the following example to check out.

clause type:
1. private (list)
   private variable list, all of the provided variable is independent of each thread
2. firstprivate (list)
   similar to private (list), but initialize the variable by the main thread variable
3. nowait:
   thread will not wait until all the thread finish the single thread part
*****************************************************************************/

void single_keyword();

void single_keyword_nowait();

/*****************************************************************************
 threadprivate (list): declare the variable that is always a private variable
 in any section, and the value of the variable can pass through code section.
 Can only be used by:
 1. global variable.
 2. static variable.
 The threadprivate keyword have many restriction:
 1. The declaration must be after the variable declaration, and before variable in use.
 2. Disable omp to dynamically allocate thread by omp_set_dynamic(0)
 3. In each section, the thread number must be the same
 *****************************************************************************/

void threadprivate_keyword();

/*****************************************************************************
When using threadprivate keyword, you can use copyin in the parallel section,
which can copy the value of threadprivate variable in the main thread to all other
thread. In the following example, the counter variable initialize to 0, so counter
equal to 0 in all of the 4 threads. However, when I set counter = 10 at the beginning
of the function, it actually set the variable value in the main thread, and all the
thread remain 0. But by using copyin, counter in all of the thread equal to 10.
*****************************************************************************/

void copyin_keyword();

/*****************************************************************************
 When using threadprivate keyword, you can also use copyprivate in the single section
 inside the parallel section, which aim to broadcast the threadprivate variable value to
 all the other thread. In the following example, when change the variable value in the
 single section, the threadprivate value only be changed in one thread. However, when
 using copyprivate, all of the thread will have the same threadprivate value.
 *****************************************************************************/

void copyprivate_keyword();