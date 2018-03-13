#include "printName.h"
#include "printPlane.c"
#include "shootPlane.h"

int main() {
	int length, i, j;
	char * Name;
	char * Name2;
    char * Name3;
	char * Name4;
    char * Name5;
	char * Name6;
    char * Name7;
	char * Name8;

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
    
    int n;
 
  unsigned char key;
 
 
 
  tcgetattr(0,&initial_settings);
 
  new_settings = initial_settings;
  new_settings.c_lflag &= ~ICANON;
  new_settings.c_lflag &= ~ECHO;
  new_settings.c_lflag &= ~ISIG;
  new_settings.c_cc[VMIN] = 0;
  new_settings.c_cc[VTIME] = 0;
 
  tcsetattr(0, TCSANOW, &new_settings);
 
  while(1)
  {
    n = getchar();
 
    if(n != EOF)
    {
      key = n;
 
      if(key == 27)  /* Escape key pressed */
      {
       int y;
    for (y = 200; y > -1300; y--) {
        printPlane();

        
        shootPlane(y, y, -1);
        shootPlane(-1*y, y, 1);
        shootPlane(0, y, 0);

    	for(j = 0; j < 5000000; j++);
		clearScreen();
    }

      }
 
    /* do something useful here with key */
    }
  }
 
  tcsetattr(0, TCSANOW, &initial_settings);




    

    for (i = 200; i > -1300; i--) {
    	printName(Name, 4, i);
    	printName(Name2, 4, i+160);	
        printName(Name3, 6, i+320);	
        printName(Name4, 7, i+480);	
        printName(Name5, 4, i+640);	
        printName(Name6, 4, i+800);	
        printName(Name7, 5, i+960);	
        printName(Name8, 5, i+1120);	
    	
        printPlane();

        
        shootPlane(i, i, -1);
        shootPlane(-1*i, i, 1);
        shootPlane(0, i, 0);

    	for(j = 0; j < 5000000; j++);
		clearScreen();
        //printf("%d\n",i);

    }  	
	
	return 0;
}
