# Opdracht 1.1

De code compileert zonder problemen met GCC en Clang. De enige waarschuwing
resulteert als er met Clang en `-Wpedantic` gecompileerd wordt.

```
b.c:3:9: warning: a function declaration without a prototype is deprecated in all versions of C [-Wstrict-prototypes]
int main() {
        ^
         void
1 warning generated
```

Dit komt doordat volgens de standaard enkel de volgende prototypen juist zijn
voor de main functie:

```c
int main(void);
int main(int argc, char **argv);
```

Lege parameters zijn in c namelijk niet het zelfde als `void` (tenzij je al
c23 gebruikt). Dit komt doordat er in c twee manieren om functies te
declareren. Ten eerste:

```c
int foo(int a);
int foo(int a) {
	return a;
}
```

En ten tweede:

```c
int foo();
int foo(a)
int a;
{
	return a;
}
```

De tweede manier is deprecated in elke versie van c en verwijdert uit c23,
maar compiler support voor c23 is nog beperkt en bij het compileren van deze
code heb ik de optie `-std=c99` gebruikt.
