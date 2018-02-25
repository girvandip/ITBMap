#ifndef LINE
#define LINE

#include "../point/point.cpp"
#include <utility>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <iostream>

using namespace std;

class Line {
    public:
        Line() {

        }
        
        Line(Point p1, Point p2) {
            this->p1.setAxis(p1.getAxis());
            this->p1.setOrdinat(p1.getOrdinat());
            this->p2.setAxis(p2.getAxis());
            this->p2.setOrdinat(p2.getOrdinat());
        }

        Line(int x1, int y1, int x2, int y2) {
            this->p1.setAxis(x1);
            this->p1.setOrdinat(y1);
            this->p2.setAxis(x2);
            this->p2.setOrdinat(y2);
        }

        Point getFirstPoint() {
            return p1;
        }

        Point getSecondPoint() {
            return p2;
        }

        Point setFirstPoint(Point p1) {
            this->p1 = p1;
        }

        Point setSecondPoint(Point p2) {
            this->p2 = p2;
        }

        pair<float, float> makeLine() {
            float x1 = p1.getAxis() * 1.0;
            float y1 = p1.getOrdinat() * 1.0;
            float x2 = p2.getAxis() * 1.0;
            float y2 = p2.getOrdinat() * 1.0;

            float a,b;
            if(x2 - x1 == 0){
                a = 0;
                b = 0;    
            } else {
                a = (y2 - y1) / (x2 - x1);
                b = y1 - (x1 * (y2 - y1) / (x2 - x1));
            }

            return make_pair(a, b);
        }

        void print(int divx, int divy, int r, int g, int b, int*** buffer){
            int fbfd = 0;
            //struct fb_var_screeninfo vinfo;
            //struct fb_fix_screeninfo finfo;
            long int screensize = 0;
            char *fbp = 0;
            int x = 0, y = 0, timer = 0;
            long int location = 0;
            int maxY;

            // Open the file for reading and writing
            // fbfd = open("/dev/fb0", O_RDWR);
            // if (fbfd == -1) {
            //     perror("Error: cannot open framebuffer device");
            //     exit(1);
            // }
            // //printf("The framebuffer device was opened successfully.\n");

            // // Get fixed screen information
            // if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
            //     perror("Error reading fixed information");
            //     exit(2);
            // }

            // // Get variable screen information
            // if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
            //     perror("Error reading variable information");
            //     exit(3);
            // }

            // //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

            // // Figure out the size of the screen in bytes
            // screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

            // // Map the device to memory
            // fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
            // if (*fbp == -1) {
            //     perror("Error: failed to map framebuffer device to memory");
            //     exit(4);
            // }

            int x0 = p1.getAxis();
            int y0 = p1.getOrdinat();
            int x1 = p2.getAxis();
            int y1 = p2.getOrdinat();

            int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
            int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
            int err = (dx>dy ? dx : -dy)/2, e2;

            x0 += divx;
            y0 += divy;
            x1 += divx;
            y1 += divy;
            
            for(;;){
                //setPixel(x0,y0);
                // location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                //                 (y0+vinfo.yoffset) * finfo.line_length;
                if(y0 > 10 && y0 < 750 -10 && x0 > 5 && x0 < 1430){ // escape seg fault
                //     *(fbp + location) = b;        // Some blue
                //     *(fbp + location + 1) = g;     // A little green
                //     *(fbp + location + 2) = r;    // A lot of red
                //     *(fbp + location + 3) = 0;      // No transparency
                // }
                //cout << "masuk print line ga?" << endl;
                buffer[y0][x0][0] = b;
                buffer[y0][x0][1] = g;
                buffer[y0][x0][2] = r;
                buffer[y0][x0][3] = 0;
                }

                if (x0==x1 && y0==y1) break;
                e2 = err;
                if (e2 >-dx) { err -= dy; x0 += sx; }
                if (e2 < dy) { err += dx; y0 += sy; }
            }

            // munmap(fbp, screensize);
            // close(fbfd);
        }

        void rotate(float degree, Point topLeft, Point bottomRight) {
            p1.rotate(degree, topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());
            p2.rotate(degree, topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());;
        }

        void scale(float scale, Point topLeft, Point bottomRight) {
            p1.scale(scale, topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());
            p2.scale(scale, topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());
        }

        void scaleByPoint(float scale, Point P) {
            p1.scaleByPoint(scale, P);
            p2.scaleByPoint(scale, P);
        }

		
        void move(int h, int v, Point topLeft, Point bottomRight) {
			p1.move(h,v,topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());
			p2.move(h,v,topLeft.getAxis(), topLeft.getOrdinat(), bottomRight.getAxis(), bottomRight.getOrdinat());
		}
		
        void update(int x, int y){
            p1.update(x, y);
            p2.update(x, y);
        }
        

    private:
        Point p1, p2;
};

#endif
