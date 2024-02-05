#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#	include <windows.h> /* For console input on Windows */
#else
#	include <termios.h> /* For console input on Linux */
#	include <unistd.h>
#endif
#include "MenuSimple.h"

/* Define the IDs for all menu items */
#define MENU_MAIN_0_ID  0
#define MENU_MAIN_1_ID  3
#define MENU_MAIN_2_ID  7
#define MENU_SUB_1_0_ID 20
#define MENU_SUB_1_4_ID 24

void handleMenuSimple(int key);
int keyScan(void);

static unsigned int currentMenuId;

/* Main entry point */
int main(void) {
	int key;

	printf("To exit press 'q'\n\n");
	/* Print first menu */
	currentMenuId = MENU_MAIN_0_ID;
	handleMenuSimple(0);
	key = keyScan();
	while (key != 'Q' && key != 'q' && key != -1) {
		handleMenuSimple(key);
		/* Sleep a short while to give other threads a chance */
		// usleep(100000L);
		key = keyScan();
	}
}

void handleMenuSimple(int key) {
	if (currentMenuId == MENU_MAIN_0_ID) {
		if (key == 'U' || key == 'u') {
			currentMenuId = MENU_MAIN_2_ID;
		} else if (key == 'D' || key == 'd') {
			currentMenuId = MENU_MAIN_1_ID;
		}
	} else if (currentMenuId == MENU_MAIN_1_ID) {
		if (key == 'U' || key == 'u') {
			currentMenuId = MENU_MAIN_0_ID;
		} else if (key == 'D' || key == 'd') {
			currentMenuId = MENU_MAIN_2_ID;
		} else if (key == 'E' || key == 'e') {
			currentMenuId = MENU_MAIN_0_ID;
		} else if (key == 'O' || key == 'o') {
			currentMenuId = MENU_SUB_1_0_ID;
		}
	} else if (currentMenuId == MENU_MAIN_2_ID) {
		if (key == 'U' || key == 'u') {
			currentMenuId = MENU_MAIN_1_ID;
		} else if (key == 'D' || key == 'd') {
			currentMenuId = MENU_MAIN_0_ID;
		} else if (key == 'E' || key == 'e') {
			currentMenuId = MENU_MAIN_0_ID;
		}
	} else if (currentMenuId == MENU_SUB_1_0_ID) {
		if (key == 'E' || key == 'e') {
			currentMenuId = MENU_MAIN_1_ID;
		} else if (key == 'D' || key == 'd') {
			currentMenuId = MENU_SUB_1_4_ID;
		}
	} else if (currentMenuId == MENU_SUB_1_4_ID) {
		if (key == 'E' || key == 'e') {
			currentMenuId = MENU_MAIN_1_ID;
		} else if (key == 'U' || key == 'u') {
			currentMenuId = MENU_SUB_1_0_ID;
		}
	}
	/* Display the menu item text */
	if (currentMenuId == MENU_MAIN_0_ID) {
		printf("=DISPLAY============\n");
		printf("HOOFDMENU\n");
		printf("Alarmen\n");
		printf("====================\n\n");
	} else if (currentMenuId == MENU_MAIN_1_ID) {
		printf("=DISPLAY============\n");
		printf("HOOFDMENU\n");
		printf("Instellingen\n");
		printf("Ok om te selecteren\n");
		printf("====================\n\n");
	} else if (currentMenuId == MENU_MAIN_2_ID) {
		printf("=DISPLAY============\n");
		printf("HOOFDMENU\n");
		printf("Radio\n");
		printf("< Aan  > Uit\n");
		printf("====================\n\n");
	} else if (currentMenuId == MENU_SUB_1_0_ID) {
		printf("=DISPLAY============\n");
		printf("SUBMENU\n");
		printf("Tijdzone instellen\n");
		printf("====================\n\n");
	} else if (currentMenuId == MENU_SUB_1_4_ID) {
		printf("=DISPLAY============\n");
		printf("SUBMENU\n");
		printf("Instellingen wissen\n");
		printf("====================\n\n");
	}
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
