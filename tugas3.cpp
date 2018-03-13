#include "printName3.h"
#include "printPlane3.cpp"
#include "shootPlane3.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

// struct termios initial_settings, new_settings;
// struct termios initial_settings,
//                new_settings;

int tugas3() {
	int length, i, j, k;
	char * Name;
	char * Name2;
    char * Name3;
	char * Name4;
    char * Name5;
	char * Name6;
    char * Name7;
	char * Name8;
    int n;
    int bulletCounter = 0;
    int bullets[10];
    unsigned char key;

    clearScreen3();
    // char inputCharacter;
    // printf("masukkan input karakter : ");
    // scanf("%c", &inputCharacter);

    printChar3('c', 200, 200, 255, 255, 255);
    printChar3('f', 300, 200, 255, 255, 255);
    printChar3('j', 400, 200, 255, 255, 255);
    printChar3('q', 500, 200, 255, 255, 255);
    printChar3('s', 600, 200, 255, 255, 255);
    printChar3('r', 700, 200, 255, 255, 255);
    printChar3('S', 800, 200, 255, 255, 255);
    printChar3('V', 900, 200, 255, 255, 255);

    sleep(2);
    clearScreen3();

	return 0;
}
