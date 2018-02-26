#include <iostream>

#include "polygon/polygon.cpp"
#include "utils/util.cpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

struct termios initial_settings, new_settings;

using namespace std;

// Frame array
int *** frameBufferArray = Util::initFrameBuffer();

// Global Clip border
Line mtop(600,100,900,100);
Line mright(900,100,900,500);
Line mbottom(900,500,600,500);
Line mleft(600,500,600,100);
Line mtopSmall(100,300,250,300);
Line mrightSmall(250,300,250,500);
Line mbottomSmall(250,500,100,500);
Line mleftSmall(100,500,100,300);


Line mtop1(100,200,480,200);
Line mright1(480,200,480,650);
Line mbottom1(480,650,100,650);
Line mleft1(100,650,100,200);
Clip clip1(mtop1, mright1, mbottom1, mleft1);


Clip clip(mtop, mright, mbottom, mleft);
Clip smallClip(mtopSmall, mrightSmall, mbottomSmall, mleftSmall);
Point middleClip(650, 350);

int main() {
    frameBufferArray = Util::initFrameBuffer();
    clip1.drawClipBorder(0,0,255,255,255,frameBufferArray);
    Polygon obj2 ((char*)"objects/2.txt");
    Polygon obj3 ((char*)"objects/3.txt");
    Polygon obj4 ((char*)"objects/4.txt");
    Polygon obj5 ((char*)"objects/5.txt");
    Polygon obj6 ((char*)"objects/6.txt");
    Polygon obj7 ((char*)"objects/7.txt");
    Polygon obj8 ((char*)"objects/8.txt");
    Polygon obj9 ((char*)"objects/9.txt");
    Polygon obj10 ((char*)"objects/10.txt");
    Polygon obj11 ((char*)"objects/11.txt");
    Polygon obj12 ((char*)"objects/12.txt");
    vector<Polygon> objects;
    string result;
    result = std::to_string(2) + ".txt";
    for(int i = 1;i < 82;i++) {
        result = "objects/" + std::to_string(i) + ".txt";
        Polygon obj (result);
        objects.push_back(obj);    
    }
    for(int i = 1;i < 82;i++) {
        objects[i].update(100,220);
        objects[i].print(0, 0, 255, 191, 255, clip1, frameBufferArray);
        objects[i].scanLine(0, 191, 255, clip1, frameBufferArray);
    }
    Util::printScreen(frameBufferArray);

    return 0;
}

