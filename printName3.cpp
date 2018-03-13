#include "printName3.h"

void printName3(char* Name, int Length, int Y, int r, int g, int b) {
    int j;

	for (j = 0; j< Length; j++) {
		printChar3(Name[j], j*120, Y, r, g, b);
	}

}
