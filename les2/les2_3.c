/* Opdracht 1.3 - memory classes */

#include "les2_3.h"
#include <stdio.h>

extern int var;

int changeMe(void);

int main(void) {
	var = 10;
	printf("%d ", changeMe());
	printf("%d ", changeMe());
	return 0;
}

int changeMe(void) {
	static int value = 0;
	value++;
	return value;
}
