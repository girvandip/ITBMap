#include <iostream>
#include "MClip.cpp"
#include "SClip.cpp"
#include "polygon/polygon.cpp"
#include "utils/util.cpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include "utils/UserInput.cpp"


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
    //frameBufferArray = Util::initFrameBuffer();
    UserInput input;
    clip1.drawClipBorder(0,0,255,255,255,frameBufferArray);
    vector<Polygon> objects;
    string result;

    Point A(10,20);
    Point B(310,320);

    Point X(100,200);
    Point Y(800,1500);

    Point C(80,60);
    Point D(155,130);

    Point E(320,20);
    Point F(920,620);

    Clip Lclip(E,F);
    SClip sClip(C,D,Lclip);
    for(int i = 1;i < 82;i++) {
        result = "objects/" + std::to_string(i) + ".txt";
        Polygon obj (result);
        objects.push_back(obj);    
    }
    for(int i = 1;i < 82;i++) {
        objects[i].update(100,220);
    }

    MClip mClip(X,Y,objects);

    while(1){
        if(input.getKeyPress('q')){
            break;
        } else if(input.getKeyPress('d')){
            C.update(10,0);
            D.update(10,0);
            sClip.setTopLeft(C);
            sClip.setBottomRight(D);
        }  else if(input.getKeyPress('a')){
            C.update(-10,0);
            D.update(-10,0);
            sClip.setTopLeft(C);
            sClip.setBottomRight(D);
        } else if(input.getKeyPress('s')){
            C.update(0,10);
            D.update(0,10);
            sClip.setTopLeft(C);
            sClip.setBottomRight(D);
        } else if(input.getKeyPress('w')){
            C.update(0,-10);
            D.update(0,-10);
            sClip.setTopLeft(C);
            sClip.setBottomRight(D);
        }

        int *** frameBufferArray = Util::initFrameBuffer();

        // Lclip.drawClipBorder(0,0,255,255,255,frameBufferArray);

        
        
        sClip.render(mClip,frameBufferArray, 255,255,255);

        Util::printScreen(frameBufferArray);
        usleep(16); // sleep = 1000/fps
    }


    // obj3.update(600,100);
    // obj4.update(600,100);
    // obj5.update(600,100);
    // obj6.update(600,100);
    // obj7.update(600,100);
    // obj8.update(600,100);
    // obj9.update(600,100);
    // obj10.update(600,100);
    // obj11.update(600,100);
    // obj12.update(600,100);
    // obj3.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj3.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj4.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj4.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj5.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj5.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj6.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj6.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj7.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj7.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj8.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj8.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj9.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj9.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj10.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj10.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj11.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj11.scanLine(0, 191, 255, clip1, frameBufferArray);
    // obj12.print(0, 0, 255, 191, 255, clip1, frameBufferArray);
    // obj12.scanLine(0, 191, 255, clip1, frameBufferArray);


    // unsigned char key;
    // // use input from user
    // tcgetattr(0,&initial_settings);
    
    // new_settings = initial_settings;
    // new_settings.c_lflag &= ~ICANON;
    // new_settings.c_lflag &= ~ECHO;
    // new_settings.c_lflag &= ~ISIG;
    // new_settings.c_cc[VMIN] = 0;
    // new_settings.c_cc[VTIME] = 0;
    
    // tcsetattr(0, TCSANOW, &new_settings);

    // Polygon plane ((char*)"objects/plane.txt");
    // Polygon tire ((char*)"objects/tire.txt");
    // Polygon tire2 ((char*)"objects/tire.txt");
    // Polygon propeller ((char*)"objects/propeller.txt");
    // Polygon propeller2 ((char*)"objects/propeller.txt");
    // Polygon bullet((char*)"objects/bullet.txt");
    // Polygon parachute((char*)"objects/parachuteperson.txt");
    // int dx = 500;
    // int dy = 150;
    // parachute.update(dx, dy);

    // float middlePlaneX = (plane.getTopLeft().getAxis() + plane.getBottomRight().getAxis()) / 2;
    // float middlePlaneY = (plane.getTopLeft().getOrdinat() + plane.getBottomRight().getOrdinat()) / 2;
    // Point middlePointPlane = Point(middlePlaneX, middlePlaneY + 400);

    // plane.update(300,400);
    // bullet.update(100, 1000);
    // tire.scale(0.2);
    // tire2.scale(0.2);
    // propeller.scale(0.65);
    // propeller2.scale(0.65);
    // tire.update(310,314);
    // tire2.update(397,314);
    // propeller.update(380, 335);
    // propeller2.update(220, 335);
    // float i = 1;
    // int j = 0;
    // int u = 0;
    // int n;

    // Point p1(100, 900);
    // Point p2(1500, 900);
    // Line surface(p1,p2);
    // bool hit =  false;
    // while(i < 1.12) {
    //     Util::printScreen(frameBufferArray);
    //     frameBufferArray = Util::initFrameBuffer();

    //     if(i >= 1.04 && i <= 1.05) {
    //         tire.scaleByPoint(1.5, middleClip);
    //         tire2.scaleByPoint(1.5, middleClip);
    //         plane.scaleByPoint(1.5, middleClip);
    //         propeller.scaleByPoint(1.5, middleClip);
    //         propeller2.scaleByPoint(1.5, middleClip);    
    //     } else if(i >= 1.08 && i <= 1.09){
    //         tire.scaleByPoint(0.5, middleClip);
    //         tire2.scaleByPoint(0.6, middleClip);
    //         plane.scaleByPoint(0.5, middleClip);
    //         propeller.scaleByPoint(0.5, middleClip);
    //         propeller2.scaleByPoint(0.5, middleClip);    
    //     }

    //     i += 0.005;
    //     tire.scaleByPoint(i, middlePointPlane);
    //     plane.scaleByPoint(i, middlePointPlane);
    //     propeller.scaleByPoint(i, middlePointPlane);
    //     propeller2.scaleByPoint(i, middlePointPlane);
    //     propeller.rotate(20);
    //     propeller2.rotate(20);
    //     plane.print(0, 0, 0, 191, 255,clip, frameBufferArray);
    //     plane.scanLine(0, 191, 255, clip, frameBufferArray);
    //     tire.print(0, 0, 70, 70, 70,clip, frameBufferArray);
    //     tire.scanLine(130, 130, 130, clip, frameBufferArray);
    //     propeller.print(0, 0, 0, 128, 0, clip, frameBufferArray);
    //     propeller.scanLine(0, 128, 0, clip, frameBufferArray);
    //     propeller2.print(0, 0, 0, 128, 0, clip, frameBufferArray);
    //     propeller2.scanLine(0, 128, 0, clip, frameBufferArray);
    //     if(!plane.isHitBy(bullet)) {
    //         if (!hit){
    //             bullet.print(0,0,255,0,0, clip, frameBufferArray);
    //             bullet.scanLine(255, 0, 0, clip, frameBufferArray);
    //             bullet.update(30,-58);
    //             bullet.rotate(2.5);
    //         }    //     frameBufferArray = Util::initFrameBuffer();

    //             // if(i >= 1.04 && i <= 1.05) {
    //             //     tire2.scaleByPoint(1.5, middleClip);   
    //             // } else if(i >= 1.08 && i <= 1.09){
    //             //     tire2.scaleByPoint(0.8, middleClip);   
    //             // }
    //             tire2.scaleByPoint(i, middlePointPlane);
    //             tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
    //             tire2.scanLine(130, 130, 130, clip, frameBufferArray);  
    //             usleep(1000);
    //     } else {
    //             hit = true;
    //             parachute.scanLine(255,108,180, clip, frameBufferArray);
    //             parachute.print(0,0,255,255,255, clip, frameBufferArray);
    //             tire2.scanLine(130, 130, 130, clip, frameBufferArray);  
    //             tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
    //             j++; u++;
    //             if (u<=20) {
    //                 parachute.update(-7, -3);
    //                 tire2.update(3,5.5);
    //                 usleep(1000);
    //             } else {
    //                 parachute.update(0,2);
    //                 tire2.update(3,5.5);
    //                 usleep(1000);
    //             }
    //     } 
    // }

    // int height = 400;

    // // if(plane.isHitBy(bullet)) {
    // //     hit = true;
    // // }

    // if(hit) {
    //     while (j<=height) {
    //         Util::printScreen(frameBufferArray);
    //         frameBufferArray = Util::initFrameBuffer();

    //         clip.drawClipBorder(0,0,255,255,255, frameBufferArray);

    //         surface.print(0,0,255,255,255, frameBufferArray);
    //         parachute.scanLine(255,108,180, clip, frameBufferArray);
    //         parachute.print(0,0,255,255,255, clip, frameBufferArray);
    //         parachute.scale(1.01);
    //         tire2.scanLine(130, 130, 130, clip, frameBufferArray); 
    //         tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
            
    //         if(j < 70) {
    //             tire2.update(2,5);
    //         } else if (j >= 70 && j < 85) {
    //             tire2.update(2,-7);
    //         }
    //         else if (j >= 85 && j < 100) {
    //             tire2.update(1, 7);
    //         }
    //         else if (j >= 100 && j < 115) {
    //             tire2.update(1, -5);
    //         }
    //         else if (j >= 115 && j < 130) {
    //             tire2.update(1, 5);
    //         }
    //         else if (j >= 130 && j < 145) {
    //             tire2.update(1, -3);
    //         }
    //         else if (j >= 145 && j < 160) {
    //             tire2.update(1, 3);
    //         }
    //         else if (j >= 160 && j < 175) {
    //             tire2.update(1, -1);
    //         }
    //         else if (j >= 175 && j < 190) {
    //             tire2.update(1, 1);
    //         }
            
    //         if (u<=20) {
    //             parachute.update(-7, 2);
    //             usleep(1000);
    //         }
    //         else {
    //             parachute.update(0,2);
    //             usleep(1000);
    //         }
    //         j++; u++;
    //     }
    // }

    // tcsetattr(0, TCSANOW, &initial_settings);

    return 0;
}

