#ifndef PRINTCHAR2_H
#define PRINTCHAR2_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void line(int x0, int y0, int x1, int y1, int divx, int divy, int r, int g, int b);
void printChar2(char character, int dx, int dy, int r, int g, int b);
void clearScreen2();

#endif
