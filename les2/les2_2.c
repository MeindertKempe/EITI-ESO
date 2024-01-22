/* Opdracht 1.2 - Functie aanroepen in C */

#include <stdio.h>
#include <string.h>

struct Person {
	char name[50];
	int bsn;
	float budget;
};

int main(void) {
	int bsn      = 3;
	float budget = 5;
	struct Person rvr = { 0 };
	strcpy(rvr.name, "Meindert Kempe");
	rvr.bsn = bsn;
	rvr.budget = budget;
	printf("The bsn of %s is %d and their budget is %.2f\n", rvr.name, rvr.bsn, rvr.budget);
}
