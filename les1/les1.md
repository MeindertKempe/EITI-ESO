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

# Opdracht 1.2

## Stap 1

De enige warning is identiek aan [Opdracht 1.1](#opdracht-1.1)

## Stap 2

De volgende errors en warnings verschijnen:

```
/home/mk/projects/ESO/les1/les1_2.c: In function ‘main’:
/home/mk/projects/ESO/les1/les1_2.c:13:26: warning: implicit declaration of function ‘difference’ [-Wimplicit-function-declaration]
   13 |         unsigned int d = difference(b, a);
      |                          ^~~~~~~~~~
/home/mk/projects/ESO/les1/les1_2.c: At top level:
/home/mk/projects/ESO/les1/les1_2.c:25:14: error: conflicting types for ‘difference’; have ‘unsigned int(int,  int)’
   25 | unsigned int difference(int x, int y) { return x - y; }
      |              ^~~~~~~~~~
/home/mk/projects/ESO/les1/les1_2.c:13:26: note: previous implicit declaration of ‘difference’ with type ‘int()’
   13 |         unsigned int d = difference(b, a);
      |                          ^~~~~~~~~~
```

Deze zijn het resultaat van het gebruiken van de difference functie voordat
deze gedefinieerd is, de twee waarschuwingen geven dit ook aan. De error komt
doordat als er geen functie declaratie is de compiler er standaard van uit
gaat dat deze een integer heeft als return type, terwijl de functie hier een
unsigned integer als return type heeft.

Om dit op te lossen zijn er twee mogelijkheden, de difference functie kan voor
de main functie geplaatst worden of het functie prototype kan in voor de main
functie gedefinieerd worden (bijvoorbeeld in de header file).

Als we de compilatie error oplossen is de uitvoer als volgt:

```
The sum of 3 and 5 is 8
Printing the sum: 3 + 5 = 8

The difference is 2
The difference is 4294967294
```

De laatste regel is hier wellicht wat onverwacht, maar het is eenvoudig te
verklaren. De functie difference berekent hier namelijk `3 - 5` en geeft het
resultaat als een unsigned integer terug. Omdat het resultaat van de
berekening `-2` is en mijn platform 32-bit, 2's complement integers gebruikt
is de waarde `1111 1111 1111 1111 1111 1111 1111 1110` in binary wat
vervolgens als unsigned integer geïnterpreteerd wordt en dus een waarde geeft
van `4294967294`.

## Stap 3

Als de `%u` in een `%d` veranderd wordt is de uitvoer:

```
The difference is 2
The difference is -2
```

Dit komt omdat de waarde nu als een signed integer geïnterpreteerd wordt, zie
[Stap 2](#stap-2).

Als de `%d` nu in een `%x` veranderd wordt is de uitvoer:

```
The difference is 2
The difference is fffffffe
```

Het getal is nu geïnterpreteerd als unsigned en genoteerd in hexadecimaal
zoals wordt beschreven in `printf(3)`

## Stap 4

De code zal compileren met waarschuwingen over de functie declaratie (zoals
besproken in [Stap 2](#stap-2)) en het feit dat er een return type mist bij de
square functie. De rede dat deze code in tegenstelling tot [Stap 2](#stap-2)
geen error produceert is dat het standaard return type bij implicit function
declaration een integer is wat overeen komt met het verwachte return type in
onze code. Het resultaat van onze code komt dus ook overeen met onze
verwachtingen.

Om de waarschuwingen te verhelpen kunnen we een functie prototype declareren
en een return type noteren.
