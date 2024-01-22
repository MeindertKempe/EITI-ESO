/* Opdracht 1.2 - Functie aanroepen in C */

#include "les1_2.h"
#include <stdio.h>

int main(void) {
	int a = 3;
	int b = 5;
	int c = sum(a, b);
	printf("The sum of %d and %d is %d\n", a, b, c);
	print_sum(a, b);

	unsigned int d = difference(b, a);
	printf("%%u:\n");
	printf("The difference is %u\n", d);
	d = difference(a, b);
	printf("The difference is %u\n", d);

	printf("\n%%d:\n");
	d = difference(b, a);
	printf("The difference is %d\n", d);
	d = difference(a, b);
	printf("The difference is %d\n", d);

	printf("\n%%x:\n");
	d = difference(b, a);
	printf("The difference is %x\n", d);
	d = difference(a, b);
	printf("The difference is %x\n", d);

	printf("\n");

	printf("The square of %d is %d\n", 8, square(8));
}

int sum(int x, int y) { return x + y; }

void print_sum(int x, int y) {
	printf("Printing the sum: %d + %d = %d\n\n", x, y, sum(x, y));
}

unsigned int difference(int x, int y) { return x - y; }

int square(int n) { return n * n; }
