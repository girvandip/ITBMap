#include <iostream>
#include "polygon/polygon.cpp"
#include "utils/util.cpp"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

using namespace std;

// Frame array
int *** frameBufferArray = Util::initFrameBuffer();

// Global Clip border
Line mtop(100,100,1200,100);
Line mright(1200,100,1200,600);
Line mbottom(1200,600,100,600);
Line mleft(100,600,100,100);
Clip clip(mtop, mright, mbottom, mleft);
Point middleClip(650, 350);

int tugas5(bool *running) {
    Polygon plane ((char*)"objects/plane.txt");
    Polygon tire ((char*)"objects/tire.txt");
    Polygon tire2 ((char*)"objects/tire.txt");
    Polygon propeller ((char*)"objects/propeller.txt");
    Polygon propeller2 ((char*)"objects/propeller.txt");
    Polygon bullet((char*)"objects/bullet.txt");
    Polygon parachute((char*)"objects/parachuteperson.txt");
    
    int dx = 500;
    int dy = 150;
    parachute.update(dx, dy);

    float middlePlaneX = (plane.getTopLeft().getAxis() + plane.getBottomRight().getAxis()) / 2;
    float middlePlaneY = (plane.getTopLeft().getOrdinat() + plane.getBottomRight().getOrdinat()) / 2;
    Point middlePointPlane = Point(middlePlaneX, middlePlaneY + 400);

    plane.update(300,400);
    bullet.update(100, 1000);
    tire.scale(0.2);
    tire2.scale(0.2);
    propeller.scale(0.65);
    propeller2.scale(0.65);
    tire.update(310,314);
    tire2.update(397,314);
    propeller.update(380, 335);
    propeller2.update(220, 335);
    float i = 1;
    int j = 0;
    int u = 0;
    int n;

    Point p1(100, 900);
    Point p2(1500, 900);
    Line surface(p1,p2);
    bool hit =  false;
    frameBufferArray = Util::initFrameBuffer();
    bool hitByBullet = false;
    while(i < 1.12) {
        if(!(*running)) break;

        Util::printScreen(frameBufferArray);
        Util::clearFrameBuffer(frameBufferArray);

        clip.drawClipBorder(0,0,255,255,255, frameBufferArray);
        surface.print(0,0,255,255,255, frameBufferArray);
        i += 0.005;
        tire.scaleByPoint(i, middlePointPlane);
        plane.scaleByPoint(i, middlePointPlane);
        propeller.scaleByPoint(i, middlePointPlane);
        propeller2.scaleByPoint(i, middlePointPlane);
        propeller.rotate(20);
        propeller2.rotate(20);
        plane.print(0, 0, 0, 191, 255,clip, frameBufferArray);
        plane.scanLine(0, 191, 255, clip, frameBufferArray);
        tire.print(0, 0, 70, 70, 70,clip, frameBufferArray);
        tire.scanLine(130, 130, 130, clip, frameBufferArray);
        propeller.print(0, 0, 0, 128, 0, clip, frameBufferArray);
        propeller.scanLine(0, 128, 0, clip, frameBufferArray);
        propeller2.print(0, 0, 0, 128, 0, clip, frameBufferArray);
        propeller2.scanLine(0, 128, 0, clip, frameBufferArray);
        if(!hitByBullet) {
            hitByBullet = plane.isHitBy(bullet);
        } 
        if(!hitByBullet) {
            if (!hit){
                bullet.print(0,0,255,0,0, clip, frameBufferArray);
                bullet.scanLine(255, 0, 0, clip, frameBufferArray);
                bullet.update(30,-58);
                bullet.rotate(2.5);
            }
                tire2.scaleByPoint(i, middlePointPlane);
                tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
                tire2.scanLine(130, 130, 130, clip, frameBufferArray);  
                usleep(1000);
        } else {
                hit = true;
                parachute.scanLine(255,108,180, clip, frameBufferArray);
                parachute.print(0,0,255,255,255, clip, frameBufferArray);
                tire2.scanLine(130, 130, 130, clip, frameBufferArray);  
                tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
                j++; u++;
                if (u<=20) {
                    parachute.update(-7, -3);
                    tire2.update(3,5.5);
                    usleep(1000);
                } else {
                    parachute.update(0,2);
                    tire2.update(3,5.5);
                    usleep(1000);
                }
        } 
        usleep(70);
    }

    int height = 100;
    if(hit) {
        while (j<=height) {
            if(!(*running)) break;

            Util::printScreen(frameBufferArray);
            Util::clearFrameBuffer(frameBufferArray);
            clip.drawClipBorder(0,0,255,255,255, frameBufferArray);
            surface.print(0,0,255,255,255, frameBufferArray);
            parachute.scanLine(255,108,180, clip, frameBufferArray);
            parachute.print(0,0,255,255,255, clip, frameBufferArray);
            parachute.scale(1.01);
            tire2.scanLine(130, 130, 130, clip, frameBufferArray); 
            tire2.print(0, 0, 70, 70, 70, clip, frameBufferArray);
            
            if(j < 70) {
                tire2.update(2,5);
            } else if (j >= 70 && j < 85) {
                tire2.update(2,-7);
            }
            else if (j >= 85 && j < 100) {
                tire2.update(1, 7);
            }
            else if (j >= 100 && j < 115) {
                tire2.update(1, -5);
            }
            else if (j >= 115 && j < 130) {
                tire2.update(1, 5);
            }
            else if (j >= 130 && j < 145) {
                tire2.update(1, -3);
            }
            else if (j >= 145 && j < 160) {
                tire2.update(1, 3);
            }
            else if (j >= 160 && j < 175) {
                tire2.update(1, -1);
            }
            else if (j >= 175 && j < 190) {
                tire2.update(1, 1);
            }
            
            if (u<=20) {
                parachute.update(-7, 2);
                usleep(1000);
            }
            else {
                parachute.update(0,2);
                usleep(1000);
            }
            j++; 
            u++;
            usleep(70);
        }
    }

    Util::clearFrameBuffer(frameBufferArray);
    Util::printScreen(frameBufferArray);

    *running = true;
    return 0;
}

