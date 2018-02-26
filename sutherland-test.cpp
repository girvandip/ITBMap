/* code reference: https://www.thecrazyprogrammer.com/2017/02/cohen-sutherland-line-clipping-algorithm.html */

#include<iostream>
#include<stdlib.h>
#include<math.h>
#include <unistd.h>
#include "line/line.cpp"
#include "utils/util.cpp"
#include "polygon/polygon.cpp"

using namespace std;

void renderClip(Clip c,int scale, int *** buffer ,Polygon p, int x ,int y){

            int n_width = (c.getTopBorder().getSecondPoint().getAxis() - c.getTopBorder().getFirstPoint().getAxis()) * scale;
            int n_height = (c.getBottomBorder().getSecondPoint().getOrdinat() - c.getTopBorder().getSecondPoint().getOrdinat()) * scale;
            
            Line top(c.getTopBorder().getFirstPoint().getAxis()+20,c.getTopBorder().getFirstPoint().getOrdinat(),
            c.getTopBorder().getFirstPoint().getAxis()+20+n_width,c.getTopBorder().getSecondPoint().getOrdinat()
            );

            Line bottom(c.getTopBorder().getFirstPoint().getAxis()+20,c.getTopBorder().getFirstPoint().getOrdinat()+n_height,
            c.getTopBorder().getFirstPoint().getAxis()+20+n_width,c.getTopBorder().getFirstPoint().getOrdinat()+n_height);

            Line left(c.getTopBorder().getFirstPoint().getAxis()+20,c.getTopBorder().getFirstPoint().getOrdinat() ,
            c.getTopBorder().getFirstPoint().getAxis()+20,c.getTopBorder().getFirstPoint().getOrdinat() + n_height);

            Line right(c.getTopBorder().getFirstPoint().getAxis()+20+n_width,c.getRightBorder().getFirstPoint().getOrdinat(),
            c.getTopBorder().getFirstPoint().getAxis()+20+n_width,c.getTopBorder().getFirstPoint().getOrdinat() + n_height);

            
            Clip cRender(top,right,bottom,left);

            cRender.drawClipBorder(c.getTopBorder().getSecondPoint().getAxis() ,0,255,255,255,buffer);
 
                     

            p.print(0,0,255,255,255,cRender,buffer);
            p.scanLine(255,25,25,cRender,buffer);

            p.update(x*scale, y*scale);
            
        };


  
int main()
{
    Line l1(50,50,250,50);
    Line l2(250,50,250,250);
    Line l3(250,250,50,250);
    Line l4(50,250,50,50);
    Clip cl(l1, l2, l3, l4);

    int scale_ratio = 2;

    Line l5 (270, 50, 670, 50);
    Line l6 (670, 50, 670, 450);
    Line l7 (670,450, 270, 450);
    Line l8 (270,450, 270, 50);
    Clip cl2(l5,l6,l7,l8);

    Line l9(170,100,195,100);
    Line l10(195,100,195,125);
    Line l11(195,125,170,125);
    Line l12(170,125,170,100);
    Clip cl3(l9,l10,l11,l12);

    int *** frameBufferArray = Util::initFrameBuffer();
    
//     int v, gm;
//     Point p1, p2;
//     int x, y;
//     //PT p1,p2,p3,p4,ptemp;
    
//     cout<<"\nEnter x1 and y1\n";
//     cin>> x >> y;
//     p1.setAxis(x); p1.setOrdinat(y);
//     cout<<"\nEnter x2 and y2\n";
//     cin>> x >> y;
//     p2.setAxis(x); p2.setOrdinat(y);
//     Line line(p1, p2);
    
    
//     Util::clearScreen();
//     cl.drawClipBorder(0,0,255,255,255);
//     usleep(500000);
    
//     line.print(0,0,255,255,255);
//     usleep(500000);
//     Util::clearScreen();
    
//     usleep(500000);
//     cl.setCodeForPoint(p1);
//     cl.setCodeForPoint(p2);
//     line.setFirstPoint(p1);
//     line.setSecondPoint(p2);
//     v= cl.isVisible(p1, p2);
//     cout << v << endl;
//     usleep(500000);
    
//     switch(v)
//     {
//     case 0: cl.drawClipBorder(0, 0, 255,255,255);
//             usleep(500000);
//             line.print(0,0,255,255,255);
//             break;
//     case 1: cl.drawClipBorder(0, 0, 255,255,255);
//             usleep(500000);
//             break;
//     case 2: cl.resetEndPoint(p1, p2);
//             cl.resetEndPoint(p2, p1);
//             line.setFirstPoint(p1);
//             line.setSecondPoint(p2);
//             cl.drawClipBorder(0,0,255,255,255);
//             usleep(500000);
//             line.print(0,0,255,255,255);
//             break;
//     }
    
//     usleep(500000);
    Polygon square((char*)"objects/plane.txt");
    //Polygon square1((char*)"objects/tire.txt");
    Polygon square1 = square;
    square.update(30,50);
    square1.scale(16);
    square1.update(0,130);
    

    for(int i = 0; i < 100; i++){
        //cout << i << endl;
        Util::printScreen(frameBufferArray);
        frameBufferArray = Util::initFrameBuffer();

        cl.drawClipBorder(0,0,255,255,255,frameBufferArray);
        cl2.drawClipBorder(0,0,255,255,255,frameBufferArray);
       
        
        square.print(0,0,255,255,255,cl,frameBufferArray);
        square.scanLine(255,25,25,cl,frameBufferArray);

        // renderClip(cl,2,frameBufferArray,square1,5,5);

        square1.print(0,0,255,255,255,cl2,frameBufferArray);
        square1.scanLine(255,25,25,cl2,frameBufferArray);

        cl3.drawClipBorder(0,0,255,255,255,frameBufferArray);

        // square.print(0,0,255,255,255,cl3,frameBufferArray);
        // square.scanLine(255,25,25,cl3,frameBufferArray);

        
        
        // square1.print(cl.getTopLine().getSecondPoint().getAxis() + 50,0,255,255,255,c2,frameBufferArray);
        // square1.scanLine(255,25,25,c2,frameBufferArray);

        //square1.print(0,0,255,255,255,cl);
        //square1.scanLine(255,25,25,cl);
        
    //    renderClip(cl,2, frameBufferArray, square1,5,5);
        // cl.renderClip(2,frameBufferArray);
        
        // cl2.drawClipBorder(0,0,255,255,255,frameBufferArray);
        // cl2.renderClip(cl , 2);
        // square.update(5,5);
        // square1.update(10,10);

        delete [] **frameBufferArray;
        
        usleep(20000);
    }

    return 0;
}
