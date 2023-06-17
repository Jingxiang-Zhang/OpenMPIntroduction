#pragma once

/*****************************************************************************
There are 6 types of synchronization sentence:
1. barrier: wait until all the thread run on the same point
2. single: already used in the former example, can use nowait to cancel the synchronization
3. master: similar to single keyword, but the code in the master section will only
	be executed by main thread, and no implicit barrier (nowait)
4. ordered: already used in the former example
5. critical: execute the code by mutual exclusion (mutex). For the code that not thread
	safety, use critical keyword to keey thread safety, which only allow one thread
	at a time to manipulate the following code segment. see the following example.
 *****************************************************************************/

void barrier_demo();

void master_demo();

/*****************************************************************************
In the following example for critical keyword, you may find that this will lower
down the speed of the program. Using critical keyword by reasonable code segment
can increase the efficiency of the program.
 *****************************************************************************/

void critical_demo();
