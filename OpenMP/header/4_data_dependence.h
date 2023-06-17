#pragma once


 /*****************************************************************************
 There are 4 types of data relationship:
 1. No relationship:
	A = x + y;
	B = x + z;
	A and B have no relationship, and the order can be changed
 2. Flow dependence (Read After Write):
	A = x + y;
	B = x + A;
	B need to read A's value after A is done
 3. Anti-dependence (Write After Read):
	A = x + B;
	B = x + z;
	A need B's previous value, and B change the value after A is done
 4. Output dependence (Write After Write)
	A = x + y;
	A = x + z;
	A's value depend on the order of the code.
 Write After Read and Write After Write data dependency can be eliminated by some ways.
 A good compiler can help to reduce the data dependency, while a good programmer can also
 avoid data these two types of data dependency. 
 However, Read After Write data dependency can not be eliminated.

 *****************************************************************************/

void data_dependency_and_eliminate();
