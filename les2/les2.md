# Opdracht 2.3

## Stap 1

Er staan 'smart quotes' in de source code dus ik verwacht dat het niet
compileert...

```
les2_3.c: In function ‘main’:
les2_3.c:6:8: error: stray ‘\342’ in program
    6 | printf(<U+201C>%d <U+201D>, changeMe());
      |        ^~~~~~~~
```

Wanneer we dit probleem opgelost hebben zal de uitvoer als volgt zijn:

```
1 2 
```

Dit komt omdat dankzij het `static` keyword de waarde van het variable `value`
over meerde oproepen van de `changMe` functie bewaard wordt en in de functie
wordt er steeds één bij deze waarde opgeteld.

## Stap 2

Ik verwacht hier een error van de linker, de compiler gaat er hier gewoon van
uit dat het variable `var` in externe code te vinden is en het is de taak van
de linker om dit symbool te vinden. Echter is het variable in geen van de code
waar de linker tegen linkt te vinden en krijgt men een linker error.

```
/usr/bin/ld: CMakeFiles/les2_3.dir/les2/les2_3.c.o: warning: relocation against `var' in read-only section `.text'
/usr/bin/ld: CMakeFiles/les2_3.dir/les2/les2_3.c.o: in function `main':
les2_3.c:(.text+0x6): undefined reference to `var'
/usr/bin/ld: warning: creating DT_TEXTREL in a PIE
collect2: error: ld returned 1 exit status
```

## Stap 3

Door `int var;` toe te voegen aan de header verhelpen we de linker error, het
variable is nu ergens gedefinieerd en de linker kan dit nu gebruiken tijdens
het linken. Echter is het niet handig om op deze manier te doen want als we
uiteindelijk een programma schrijven met meerdere translation units die de
header gebruiken zal `int var;` meerdere keren gedefinieerd worden. Het is dus
beter om in de header `extern int var;` te gebruiken en dan in één source file
het variable te definiëren met `int var;`.

```
/usr/bin/ld: CMakeFiles/les2_3.dir/les2/les2_3_1.c.o:(.bss+0x0): multiple definition of `var'; CMakeFiles/les2_3.dir/les2/les2_3.c.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status
```

Zie boven voor de linker error als meerdere translation units de header
gebruiken.
