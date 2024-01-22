#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char a[80];
	char *s;
	/* Lees tekst in vanaf het keyboard.
	 * note: Deze functie is gevaarlijk aangezien deze geen rekening houdt met
	 * de grote van de buffer, gebruik een andere functie zoals fgets(3). */
	gets(a);
	/* Alloceer genoeg geheugen voor de ingelezen tekst. */
	s = (char *)malloc(strlen(a) + 1); /* cast onnodig in c! */
	/* Kopieer de tekst naar het het gealloceerde geheugen. */
	strcpy(s, a);
	/* Opnieuw tekst inlezen om achter de vorige tekst te plakken */
	gets(a);
	/* Heralloceer het geheugen zodat de vorige string die zig al in s bevind en
	 * de nieuwe ingelezen string in a beide in het geheugen van s passen */
	s = (char *)realloc(s, strlen(s) + strlen(a) + 1);
	/* Concatenate de string in a met de string in s. */
	strcat(s, a);
	/* Bekijk het resultaat. */
	printf("%s\n", s);
	/* Bevrijd het gealloceerde geheugen. (In dit geval is dit niet per se nodig
	 * aangezien het geheugen automatisch bevrijd wordt door het
	 * besturingssysteem wanneer het programma stopt.) */
	free(s);
}
