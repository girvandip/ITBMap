// reference : https://stackoverflow.com/questions/11451618/how-do-you-read-the-mouse-button-state-from-dev-input-mice

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "point/point.cpp"
#include "utils/util.cpp"
#include <pthread.h>

Point p(150,150);
int ***framebuffer = Util::initFrameBuffer();

void *getInput(void * threadid){
    int fd, bytes;
    unsigned char data[3];

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        //return -1;
    }

    int left = 0, middle = 0, right = 0;
    signed char x, y;
   
    while(1)
    {
        //Util::clearFrameBuffer(framebuffer);

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

            if(right == 2){
                break;
            }

            if(left == 1){
                p.update(x, -y);
                p.print(framebuffer, 255, 255, 255);
            }
            
        }

        Util::printScreen(framebuffer);
    }
}

int main(int argc, char** argv)
{
    pthread_t mouse;
    pthread_create(&mouse, NULL, getInput, 0);

    pthread_exit(NULL);

    return 0; 
}