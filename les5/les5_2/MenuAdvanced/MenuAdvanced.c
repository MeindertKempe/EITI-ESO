#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#	include <windows.h> /* For console input on Windows */
#else
#	include <termios.h> /* For console input on Linux */
#	include <unistd.h>
#endif
#include "MenuAdvanced.h"

#define MAX_MENU_KEY  6
#define LCD_MAX_LINES 4

/* Define indices for the keys in the array of new IDs */
#define MENU_KEY_ESC   0
#define MENU_KEY_OK    1
#define MENU_KEY_UP    2
#define MENU_KEY_DOWN  3
#define MENU_KEY_LEFT  4
#define MENU_KEY_RIGHT 5

/* Define the IDs for all menu items */
#define MENU_MAIN_0_ID  0
#define MENU_MAIN_1_ID  3
#define MENU_MAIN_2_ID  7
#define MENU_SUB_1_0_ID 20
#define MENU_SUB_1_4_ID 24

void handleMenu(int key);
void printMenuItem(char *lines[]);
int keyScan(void);

/* Define struct to hold data for a single menu item */
typedef struct {
	unsigned int id;                  /* ID for this item */
	unsigned int newId[MAX_MENU_KEY]; /* IDs to jump to on keypress */
	char *text[LCD_MAX_LINES];        /* Text for this item */
} MENU_ITEM_STRUCT;

/* Define the menu items */
/* Note: the menu ID is NOT the same as its position in the array */
MENU_ITEM_STRUCT menu[] = {
	{ /* Menu item 0 */
	  MENU_MAIN_0_ID,
	  { /* New item id (Esc, Ok, Up, Down, Left, Right) */
	    MENU_MAIN_0_ID, MENU_MAIN_0_ID, MENU_MAIN_2_ID, MENU_MAIN_1_ID,
	    MENU_MAIN_0_ID, MENU_MAIN_0_ID },
	  { /* Menu item text */
	    "HOOFDMENU", "Alarmen", " ", " " } },
	{ /* Menu item 1 */
	  MENU_MAIN_1_ID,
	  { /* New item id (Esc, Ok, Up, Down, Left, Right) */
	    MENU_MAIN_0_ID, MENU_SUB_1_0_ID, MENU_MAIN_0_ID, MENU_MAIN_2_ID,
	    MENU_MAIN_1_ID, MENU_MAIN_1_ID },
	  { /* Menu item text
	     01234567890123456789 */
	    "HOOFDMENU ", "Instellingen", "Ok om te selecteren", " " } },
	{ /* Menu item 2 */
	  MENU_MAIN_2_ID,
	  { /* New item id (Esc, Ok, Up, Down, Left, Right) */
	    MENU_MAIN_0_ID, MENU_MAIN_2_ID, MENU_MAIN_1_ID, MENU_MAIN_0_ID,
	    MENU_MAIN_2_ID, MENU_MAIN_2_ID },
	  { /* Menu item text
	     01234567890123456789 */
	    "HOOFDMENU", "Radio", "< Aan  > Uit" } },
	{ /* Sub menu item 0 */
	  MENU_SUB_1_0_ID,
	  { /* New item id (Esc, Ok, Up, Down, Left, Right) */
	    MENU_MAIN_1_ID, MENU_SUB_1_0_ID, MENU_SUB_1_0_ID, MENU_SUB_1_4_ID,
	    MENU_SUB_1_0_ID, MENU_SUB_1_0_ID },
	  { "SUBMENU", "Tijdzone instellen", " ", " " } },
	{ /* Sub menu item 4 */
	  MENU_SUB_1_4_ID,
	  { /* New item id (Esc, Ok, Up, Down, Left, Right) */
	    MENU_MAIN_1_ID, MENU_SUB_1_4_ID, MENU_SUB_1_0_ID, MENU_SUB_1_4_ID,
	    MENU_SUB_1_4_ID, MENU_SUB_1_4_ID },
	  { "SUBMENU", "Instellingen wissen", " ", " " } }
};

static unsigned int currentMenuIndex = 0; /* Start at first menu item */
static unsigned int currentMenuId;

/* Main entry point */
int main() {
	int key;

	printf("To exit press 'q'\n\n");
	/* Print first menu */
	currentMenuId = menu[currentMenuIndex].id;
	printMenuItem(menu[currentMenuIndex].text);
	// key = keyScanNonBlocking();
	key = keyScan();
	while (key != 'Q' && key != 'q' && key != -1) {
		handleMenu(key);
		/* Sleep a short while to give other threads a chance */
		// usleep(100000L);
		// key = keyScanNonBlocking();
		key = keyScan();
	}
}

void handleMenu(int key) {
	switch (key) {
			/* Esc */
		case 'E':
		case 'e':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_ESC];
			break;
			/* Ok */
		case 'O':
		case 'o':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_OK];
			break;
			/* Up */
		case 'U':
		case 'u':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_UP];
			break;
			/* Down */
		case 'D':
		case 'd':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_DOWN];
			break;
			/* Left */
		case 'L':
		case 'l':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_LEFT];
			break;
			/* Right */
		case 'R':
		case 'r':
			currentMenuId = menu[currentMenuIndex].newId[MENU_KEY_RIGHT];
			break;
		default: break;
	}
	/* Lookup new current menu id in the array of menu items */
	/* Note: each menu has an ID and a position in the menu array and these are
	 * NOT the same! */
	currentMenuIndex = 0;
	while (menu[currentMenuIndex].id != currentMenuId) {
		currentMenuIndex += 1;
	}
	/* Display the menu item text */
	printMenuItem(menu[currentMenuIndex].text);
}

void printMenuItem(char *lines[]) {
	unsigned int lineNr = 0;
	/* Display the item text */
	printf("=DISPLAY============\n");
	for (lineNr = 0; lineNr < LCD_MAX_LINES; lineNr += 1) {
		if (lines[lineNr] != NULL) { printf("%s\n", lines[lineNr]); }
	}
	printf("====================\n\n");
}

#ifdef _WIN32
int keyScanWin(void) {
	/* Scan the keyboard until a key is pressed, then return its value */
	INPUT_RECORD inputBuffer[2];
	int charsRead;
	int key     = 0;
	int keyDown = 0;

	do {
		if (ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &(inputBuffer[0]),
		                     1, &charsRead)) {
			keyDown = inputBuffer[0].EventType == KEY_EVENT &&
			          inputBuffer[0].Event.KeyEvent.bKeyDown;
		}
	} while (!keyDown);
	key = inputBuffer[0].Event.KeyEvent.uChar.AsciiChar;
	printf("Key entered: %c [%d]\n", key, key);
	return key;
}
#else
int keyScanNonBlocking(void) {
	int key;
	struct termios savedState, newState;

	/* Set stdin to non-blocking single character */
	if (-1 == tcgetattr(STDIN_FILENO, &savedState)) { return EOF; }
	memcpy(&newState, &savedState, sizeof(struct termios));
	newState.c_lflag   &= ~(ICANON | ECHO);
	newState.c_cc[VMIN] = 1;
	if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &newState)) { return EOF; }
	key = fgetc(stdin);
	/* Set stdin back to old status */
	if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &savedState)) { return EOF; }
	return key;
}
#endif

int keyScan(void) {
#ifdef _WIN32
	return keyScanWin();
#else
	return keyScanNonBlocking();
#endif
	/* Wait for a key to be pressed (+ enter) */
	// int key = getchar();
	// return key;
}
