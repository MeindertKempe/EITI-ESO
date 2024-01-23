#include "teststack.h"
#include "stack.h"
#include <stdio.h>

// TODO add header for assert statements
//
void test_stack(void) {
	int error           = STACK_OK;
	int ival1           = -1;
	int ival2           = 0;
	double dval1           = -1;
	int nrValuesWritten = 0;
	int nrValuesRead    = 0;

	error = stack_push_int(17);
	// TODO convert to an assert( ) statement
	if (error) { printf("ERROR in stackPushInt(): %i\n", error); }

	error = stack_pop_int(&ival1);
	// TODO convert to an assert( ) statement
	if (error) { printf("ERROR in stackPopInt():%i\n", error); }

	error = stack_push_double(17.4);
	// TODO convert to an assert( ) statement
	if (error) { printf("ERROR in stackPushInt(): %i\n", error); }

	error = stack_pop_double(&dval1);
	// TODO convert to an assert( ) statement
	if (error) { printf("ERROR in stackPopInt():%i\n", error); }

	error = STACK_OK;
	ival1 = 9;
	while (STACK_OK == error) {
		ival1 += 3;
		error  = stack_push_int(ival1);
		if (error) {
			printf("Error received after %d writes\n", nrValuesWritten);
		} else {
			nrValuesWritten += 1;
		}
	}
	printf("Number of values written: %d\n", nrValuesWritten);

	error = STACK_OK;
	while (STACK_OK == error) {
		ival1 -= 3;
		error  = stack_pop_int(&ival2);
		if (error) {
			printf("Error received after %d values read\n", nrValuesRead);
		} else {
			nrValuesRead += 1;
			// TODO convert to an assert( ) statement
			if (ival2 != ival1) {
				printf("ERROR reading value back from stack: values inequal\n");
			}
		}
	}
	printf("Number of values read: %d\n", nrValuesRead);

	// TODO convert to an assert( ) statement
	if (nrValuesWritten != nrValuesRead) {
		printf("ERROR wrong number of values read back from stack\n");
	}
	// TODO add test code to test pushing and popping double values from the
	// stack
}
