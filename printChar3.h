#ifndef PRINTCHAR3_H
#define PRINTCHAR3_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void line3(int x0, int y0, int x1, int y1, int divx, int divy, int r, int g, int b);
void printChar3(char character, int dx, int dy, int r, int g, int b);
void floodFill3(int x, int y, int r, int g, int b, int newcolor);
void clearScreen3();

#endif