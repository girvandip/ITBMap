#include "printName1.h"

void printName1(char* Name, int Length, int Red, int Green, int Blue, int Y) {
    int i;

    // print the characters
    for(i = 0; i < Length; i++){
        //printf("%d\n",90*i);
        printChar1(Name[i], Red, Green, Blue, 90*(i+1), Y);
        
    }

    //delay
    //for(i = 0; i < 2500000; i++);

    //clearScreen();
}
