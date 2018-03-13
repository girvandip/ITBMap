#ifndef PRINTCHAR1_H
#define PRINTCHAR1_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

void printChar1(char Character, int Red, int Green, int Blue, int axis, int ordinat);
void clearScreen1();

#endif
