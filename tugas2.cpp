#include "printName2.h"
#include "shootPlane.h"
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

struct termios initial_settings, new_settings;

int tugas2(bool *running) {
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
    
    // use input from user
    tcgetattr(0,&initial_settings);
    
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 0;
    new_settings.c_cc[VTIME] = 0;
    
    tcsetattr(0, TCSANOW, &new_settings);
  
    Name = (char*) malloc(4);
    Name[0] = 'a';
    Name[1] = 'm';
    Name[2] = 'u';
    Name[3] = 'z';

    Name2 = (char*) malloc(4);
	Name2[0] = 'i';
    Name2[1] = 'c';
    Name2[2] = 'h';
    Name2[3] = 'a';

    length = 6;
    Name3 = (char*) malloc(6);
    Name3[0] = 'r';
    Name3[1] = 'o';
    Name3[2] = 'y';
    Name3[3] = 'y';
    Name3[4] = 'a';
    Name3[5] = 'n';

    Name4 = (char*) malloc(7);
	Name4[0] = 'a';
    Name4[1] = 'l';
    Name4[2] = 'd';
    Name4[3] = 'r';
    Name4[4] = 'i';
    Name4[5] = 'c';
    Name4[6] = 'h';

    Name5 = (char*) malloc(4);
    Name5[0] = 'a';
    Name5[1] = 'g';
    Name5[2] = 'g';
    Name5[3] = 'i';

    Name6 = (char*) malloc(4);
	Name6[0] = 'm';
    Name6[1] = 'i';
    Name6[2] = 'c';
    Name6[3] = 'o';

    Name7 = (char*) malloc(5);
    Name7[0] = 'b';
    Name7[1] = 'o';
    Name7[2] = 'b';
    Name7[3] = 'b';
    Name7[4] = 'y';

    Name8 = (char*) malloc(5);
	Name8[0] = 'f';
    Name8[1] = 'a';
    Name8[2] = 'j';
    Name8[3] = 'a';
    Name8[4] = 'r';

   

    for (i = 200; i > -1300; i--) {
        if(!(*running)) break;

        n = getchar();
    
        if(n != EOF)
        {
            key = n;
        
            if(key == 27)  /* Escape key pressed */
            {
                bullets[bulletCounter] = 0;
                bulletCounter += 1;
            } else {
                break;
            }
        
            /* do something useful here with key */
            //break;
        }

    	printName2(Name, 4, i, 7, 198, 40);
    	printName2(Name2, 4, i+160, 6, 255, 87);	
        printName2(Name3, 6, i+320, 4, 255, 255);	
        printName2(Name4, 7, i+480, 4, 50, 203);	
        printName2(Name5, 4, i+640, 4, 41, 121);	
        printName2(Name6, 4, i+800, 5, 98, 0);	
        printName2(Name7, 5, i+960, 5, 123, 31);	
        printName2(Name8, 5, i+1120, 4, 183, 110);	
    	
        printPlane(i,-100, 255, 255, 255);

        for(k = 0; k < bulletCounter; k++){
            shootPlane(bullets[k], bullets[k], -1);
            shootPlane(-1*bullets[k], bullets[k], 1);
            shootPlane(0, bullets[k], 0);
            bullets[k]--;
        }
        
    	for(j = 0; j < 5000000; j++);
		clearScreen2();
        //printf("%d\n",i);

    }  	

    tcsetattr(0, TCSANOW, &initial_settings);

    clearScreen2();
    *running = true;
	
	return 0;
}
