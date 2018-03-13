// reference : https://stackoverflow.com/questions/11451618/how-do-you-read-the-mouse-button-state-from-dev-input-mice

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "point/point.cpp"
#include "utils/util.cpp"
#include <pthread.h>
#include "polygon/polygon.cpp"

int ***cursorbuffer = Util::initFrameBuffer();
int ***paintbuffer = Util::initFrameBuffer();
int ***framebuffer = Util::initFrameBuffer();


void *getInput(void * threadid){
    int fd, bytes;
    int printX, printY;
    unsigned char data[3];

    const char *pDevice = "/dev/input/mice";
    // Point p1(50, 50);
    // Point p2(49, 50);
    // Point p3(50, 49);
    // Point p4(49, 49);

    string name = "objects/painter.txt";
    Polygon painter(name);

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        //return -1;
    }

    int left = 0, middle = 0, right = 0;
    signed char x, y;
    name = "objects/crosshair.txt";
    Polygon cross(name);
    while(1)
    {
        bool running = *((bool*) threadid);
        if(!running) break;

        Util::clearFrameBuffer(cursorbuffer);
        Util::clearFrameBuffer(framebuffer);

        cross.printNoClip(0,0,255,255,255,cursorbuffer);
        // Read Mouse     
        bytes = read(fd, data, sizeof(data));

        if(bytes > 0)
        {
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

            x = data[1];
            y = data[2];
            //printf("x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left, middle, right);

            cross.update(x, -y);
            painter.update(x, -y);  
            
            if(right == 2){
                
                painter.printNoClip(0,0,0,0,0,paintbuffer);
                painter.scanLineNoClip(0,0,0,paintbuffer);
                // printX = (cross.getBottomRight().getAxis() + cross.getTopLeft().getAxis())/2;
                // printY = (cross.getBottomRight().getOrdinat() + cross.getTopLeft().getOrdinat())/2;
                // p1.setAxis(printX);
                // p1.setOrdinat(printY);
                // p2.setAxis(printX-1);
                // p2.setOrdinat(printY);
                // p3.setAxis(printX);
                // p3.setOrdinat(printY-1);
                // p4.setAxis(printX-1);
                // p4.setOrdinat(printY-1);

                // p1.print(paintbuffer, 0, 0, 0);
                // p2.print(paintbuffer, 0, 0, 0);
                // p3.print(paintbuffer, 0, 0, 0);
                // p4.print(paintbuffer, 0, 0, 0);            
            }
            
            if(left == 1){
                painter.printNoClip(0,0,255,255,255,paintbuffer);
                painter.scanLineNoClip(255,255,255,paintbuffer);
                // printX = (cross.getBottomRight().getAxis() + cross.getTopLeft().getAxis())/2;
                // printY = (cross.getBottomRight().getOrdinat() + cross.getTopLeft().getOrdinat())/2;

                // p1.setAxis(printX);
                // p1.setOrdinat(printY);
                // p2.setAxis(printX-1);
                // p2.setOrdinat(printY);
                // p3.setAxis(printX);
                // p3.setOrdinat(printY-1);
                // p4.setAxis(printX-1);
                // p4.setOrdinat(printY-1);

                // p1.print(paintbuffer, 255, 255, 255);
                // p2.print(paintbuffer, 255, 255, 255);
                // p3.print(paintbuffer, 255, 255, 255);
                // p4.print(paintbuffer, 255, 255, 255);
            }
            
            if(middle != 0){
                break;
            }
        }
        Util::mergeFrameBuffer(cursorbuffer, paintbuffer, framebuffer);
        Util::printScreen(framebuffer);
    }
}

int tugas7(bool *running)
{
    pthread_t mouse;
    pthread_create(&mouse, NULL, getInput, running);

    pthread_join(mouse, NULL);

    Util::clearFrameBuffer(framebuffer);
    Util::printScreen(framebuffer);

    *running = true;

    return 0; 
}