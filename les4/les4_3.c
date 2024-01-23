#include <stdio.h>

void fun(int a) { printf("Value of a is %d\n", a); }

int main(void) {
	int a = 16;
	void (*fn)(int) = fun;
	fn(a);
}
