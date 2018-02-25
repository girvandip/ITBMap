/* compile: g++ -o thread.exe thread.cpp -lncurses --std=c++11 -pthread */

#include <iostream>
#include <thread>
#include <ncurses.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "polygon/polygon.cpp"
#include "utils/util.cpp"
#include "utils/UserInput.h"

Line mtop(100,100,1200,100);
Line mright(1200,100,1200,600);
Line mbottom(1200,600,100,600);
Line mleft(100,600,100,100);
Clip clip(mtop, mright, mbottom, mleft);

int *** framebuffer;

using namespace std;


int main() {

    // std::thread t1(call_from_thread1);
    UserInput input;

    Polygon test((char*)"objects/0.txt");
    test.update(800,800);
    test.scaleNew(0.2);
    // Line line(100,100,200,200);
    // unsigned char input = '\0';

    while(1){
        // usleep(1000);
        framebuffer = Util::initFrameBuffer();
        test.print(0,0,255,255,255,clip,framebuffer);
        if(input.getKeyPress('q')){
            break;
        } else if(input.getKeyPress('a')) {
            test.update(-10,0);
        } else if(input.getKeyPress('s')) {
            test.update(0,10);
        } else if(input.getKeyPress('d')){
            test.update(10,0);
        } else if(input.getKeyPress('w')) {
            test.update(0,-10);
        } else if(input.getKeyPress('o')) {
            test.scale(1.2);
        } else if(input.getKeyPress('p')) {
            test.scale(0.8);
        }

        Util::printScreen(framebuffer);
        
    }
    free(framebuffer);
    // t1.join();

    return 0;

}
