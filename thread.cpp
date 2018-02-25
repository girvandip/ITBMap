/* compile: g++ -o thread.exe thread.cpp -lncurses --std=c++11 -pthread */

#include <iostream>
#include <thread>
#include <ncurses.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "line/line.cpp"
#include "utils/util.cpp"
#include "utils/UserInput.h"

bool flag = false;
bool moveLeft = false;
bool moveUp = false;
bool moveRight = false;
bool moveDown = false;
bool zoomIn = false;
bool zoomOut = false;

int *** framebuffer;

using namespace std;


int main() {

    // std::thread t1(call_from_thread1);
    UserInput input;

    Line line(100,100,200,200);
    // unsigned char input = '\0';

    while(!flag){
        // usleep(1000);
        framebuffer = Util::initFrameBuffer();
        line.print(0,0,255,255,255,framebuffer);
        if(input.getKeyPress('q')){
            break;
        } else if(input.getKeyPress('a')) {
            line.update(-10,0);
        } else if(input.getKeyPress('s')) {
            line.update(0,10);
        } else if(input.getKeyPress('d')){
            line.update(10,0);
        } else if(input.getKeyPress('w')) {
            line.update(0,-10);
        }

        // //cout << "hello" << endl;
        // if(moveRight){
        //     //printw("yo");
        //     //line.update(10,0);
        //     moveRight = false;
        // } else 
        // if(moveLeft){
        //     //line.update(-10,0);
        //     moveLeft = false;
        // } else 
        // if(moveDown){
        //     //line.update(0,10);
        //     moveDown = false;
        // } else 
        // if(moveUp){
        //     //line.update(0,-10);
        //     moveUp = false;
        // }

        // initscr();
        // refresh();
        // input = getch();
        // //cin >> input;
        // //usleep(10000);
        // if(input == 27) { // Escape for break
        //     //printw("this is escape");
        //     flag = true;
        //     break;
        // } else
        // if(input == 119) { // move up
        //     //printw("w");
        //     moveUp = true;
        // } else
        // if(input == 97) { // move left
        //     //printw("a");
        //     moveLeft = true;
        // } else 
        // if(input == 115) { // move down
        //     //printw("s");
        //     moveDown = true;
        // } else
        // if(input == 100) { // move right
        //     //printw("d");
        //     moveRight = true;
        // }
        // endwin();

        Util::printScreen(framebuffer);
        //free(framebuffer);
    }

    // t1.join();

    return 0;

}