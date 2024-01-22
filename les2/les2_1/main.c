#include "main.h"
#include "math.h"
#include <stdio.h>

int main(void) {
	int a = 3;
	int b = 5;

	int c = sum(a, b);
	printf("The sum of %d and %d is %d\n", a, b, c);
	print_sum(a, b);
}

void print_sum(int x, int y) {
	printf("Printing the sum: %d + %d = %d\n\n", x, y, sum(x, y));
}
