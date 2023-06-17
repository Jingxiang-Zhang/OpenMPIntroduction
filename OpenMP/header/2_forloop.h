#pragma once

/*****************************************************************************
for loop in OpenMP must have
1. start statement with assignment: int i = 0
2. end statement with explicit boundary: i < 10
3. count statement with equal step: i += 3
4. no break, goto, return statement
5. variable i must be integer, can't change i value inside forloop
*****************************************************************************/

void forloop_demo1();

// if only one forloop in the parallel code segment, then you can use:

void forloop_demo2();

/*****************************************************************************
clause type for for statement:
1. private (list)
  private variable list, all of the provided variable is independent of each thread
2. shared (list)
  shared variable list. need to make sure thread safety
3. firstprivate (list)
  similar to private (list), but initialize the variable by the main thread variable
4. reduction (operator: list)
  similar to private (list), but provide a thread safe operator, see the next example
5. lastprivate (list):
  similar to private (list), but take out the private variable after the forloop
6. schedule (type [,chunk]):
  control CPU scheduling, , type include:
     static: chunk size is a constant, default = n / t. Use for equal workload for each thread
     dynamic: chunk size is a constant, default = 1. For a double forloop, the inner layer
             forloop start from i, which means the outer layer forloop block is not equal
             workload, then you can use dynamic scheduling.
     guided: chunk size dynamicly change. To reduce the overhead of job allocation,
             the chunk size = remaining_iteration / number_of_thread
     runtime: chunk size controlled by OMP_SCHEDULE, i.e., one of the previous three
     auto: choose by system
  chunk must be integer, is round-robin. If chunck equal to m, then thread n will execute
  [nm, n(m+1)-1], where n start from 0. And after the first round, if it not end, then
  use the same strategy for the second round
7. ordered: code inside forloop have potential order
   must use with #pragma omp ordered. code inside the ordered segment only executed
   by one thread. And to increase the parallelism, you need to adjust the schedule.
   see the following example void forloop_ordered();
8. collapse (n): loop unrolling to the n layer.
9. nowait:
*****************************************************************************/

void forloop_private_value();

void forloop_calculate_PI();

void forloop_ordered();