/* Opdracht 1.3 - if statements */
#include <stdio.h>

void do_if_tests(void);

int main(void) { do_if_tests(); }

void do_if_tests(void) {
	int value = 0;
	if (value == 0) { printf("value == 0\n"); }
	if (value == 1) { printf("value = 1\n"); }
	value = 0; // Add this line in step 3
	value = 17; // Add this line in step 4
	value = -1; // Add this line in step 5

	if (value) {
		printf("value appears to be true\n");
	} else {
		printf("value appears to be false\n");
	}
}
