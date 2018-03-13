#ifndef PRINTPLANE2
#define PRINTPLANE2

#include "printChar2.h"

void printPlane2(int x, int y, int r, int g, int b){
	// 1
	line(350,350, 375,333, x, y, r, g, b);
	line(350,350, 375,363, x, y, r, g, b);
	// 2
	line(375,333, 425,333, x, y, r, g, b);
	line(375,363, 425,363, x, y, r, g, b);
	// 3
	line(425, 333, 450, 233, x, y, r, g, b);
	line(425, 363, 450, 463, x, y, r, g, b);
	// 4
	line(450, 233, 463, 233, x, y, r, g, b);
	line(450, 463, 463, 463, x, y, r, g, b);
	// 5
	line(463, 233, 463, 333, x, y, r, g, b);
	line(463, 463, 463, 363, x, y, r, g, b);
	// 6
	line(463, 333, 475, 333, x, y, r, g, b);
	line(463, 363, 475, 363, x, y, r, g, b);
	// 7
	line(475, 333, 488, 308, x, y, r, g, b);
	line(475, 363, 488, 388, x, y, r, g, b);
	// 8
	line(488, 308, 500, 308, x, y, r, g, b);
	line(488, 388, 500, 388, x, y, r, g, b);
	// 9
	line(500, 308, 500, 388, x, y, r, g, b);
}

#endif