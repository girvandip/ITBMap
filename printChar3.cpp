#include "shootPlane3.h"

void line3(int x0, int y0, int x1, int y1, int divx, int divy, int r, int g, int b) {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0, timer = 0;
    long int location = 0;
    int maxY;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    //printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (*fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = (dx>dy ? dx : -dy)/2, e2;

    x0 += divx;
    y0 += divy;
    x1 += divx;
    y1 += divy;
    
    for(;;){
        //setPixel(x0,y0);
        location = (x0+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y0+vinfo.yoffset) * finfo.line_length;
        if(y0 > 10 && y0 < vinfo.yres -10){ // escape seg fault
            *(fbp + location) = r;        // Some blue
            *(fbp + location + 1) = g;     // A little green
            *(fbp + location + 2) = b;    // A lot of red
            *(fbp + location + 3) = 0;      // No transparency
        }
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }

    munmap(fbp, screensize);
    close(fbfd);
}

void floodFill3(int x, int y, int r, int g, int b, int newcolor)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int timer = 0;
    long int location = 0;
    int maxY;
    int oldRed, oldGreen, oldBlue;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    //printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    //printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (*fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    
    // Test
    location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                        (y+vinfo.yoffset) * finfo.line_length;
    
    if(y > 10 && y < vinfo.yres -10){ // escape seg fault
        oldRed = *(fbp + location);
        oldGreen = *(fbp + location + 1);
        oldBlue = *(fbp + location + 2);
    }

    //printf("%d %d %d\n", oldRed, oldGreen, oldBlue);

    if(oldRed == r && oldGreen == g && oldBlue == b)
    {
        *(fbp + location) = newcolor;        // Some blue
        *(fbp + location + 1) = newcolor;     // A little green
        *(fbp + location + 2) = newcolor;    // A lot of red
        *(fbp + location + 3) = 0;      // No transparency

        munmap(fbp, screensize);
        close(fbfd);

        floodFill3(x+1,y,r,g,b,newcolor);
        floodFill3(x,y+1,r,g,b,newcolor);
        floodFill3(x-1,y,r,g,b,newcolor);
        floodFill3(x,y-1,r,g,b,newcolor);
    } else {
        munmap(fbp, screensize);
        close(fbfd);
    }
    
}

void printChar3(char character, int dx, int dy, int r, int g, int b){
    int lines, j;
    char i;
    int *coordinates, *triangles;
    FILE *file;
    
    switch (character) {
        case 'S':
            file = fopen("characters3/S.txt", "r");
            break;
        case 's':
            file = fopen("characters3/s.txt", "r");
            break;
        case 'c':
            file = fopen("characters3/c.txt", "r");
            break;
        case 'j':
            file = fopen("characters3/j.txt", "r");
            break;
        case 'V':
            file = fopen("characters3/V.txt", "r");
            break;
        case 'r':
            file = fopen("characters3/r.txt", "r");
            break;
        case 'q':
            file = fopen("characters3/q.txt", "r");
            break;
        case 'f':
            file = fopen("characters3/f.txt", "r");
            break;
    }

    //clearScreen();

    // get number of point
    fscanf(file, "%d", &lines);
    
    // array of point
    coordinates = (int*) malloc ((2 * lines) * sizeof(int));
    for(j = 0; j < lines; j++){
        int x = 0, y = 0;
        fscanf(file, "%d %d", &x, &y);        
        coordinates[j*2] = x + dx;
        coordinates[(j*2)+1] = y + dy;
    }

    // get number of triangles
    fscanf(file, "%d", &lines);
    
    // array of point
    triangles = (int*) malloc ((3 * lines) * sizeof(int));
    for(j = 0; j < lines; j++){
        int point1, point2, point3;
        fscanf(file, "%d %d %d", &point1, &point2, &point3);        
        triangles[j*3] = point1;
        triangles[(j*3)+1] = point2;
        triangles[(j*3)+2] = point3;
    }

    // print the char
    for(i = 0; i < lines; i++){
        int point1, point2, point3;
        int x0, y0, x1, y1, x2, y2;

        point1 = triangles[(i*3)];
        point2 = triangles[(i*3)+1];
        point3 = triangles[(i*3)+2];
        
        x0 = coordinates[point1*2];
        y0 = coordinates[(point1*2+1)];

        x1 = coordinates[point2*2];
        y1 = coordinates[(point2*2+1)];

        x2 = coordinates[point3*2];
        y2 = coordinates[(point3*2+1)];

        line3(x0, y0, x1, y1, 0, 0, 255, 255, 255);
        line3(x0, y0, x2, y2, 0, 0, 255, 255, 255);
        line3(x2, y2, x1, y1, 0, 0, 255, 255, 255);

        int middleX = (x0 + x1 + x2)/3;
        int middleY = (y0 + y1 + y2)/3;

        floodFill3(middleX, middleY, 0,0,0, 255);
    }

    fclose(file);
}

void clearScreen3() {
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    char *fbp = 0;
    int x = 0, y = 0, timer = 0;
    long int location = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (*fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    for (y = 0; y < vinfo.yres - 10; y++) {
        for (x = 0; x < vinfo.xres; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
                       (y+vinfo.yoffset) * finfo.line_length;

            *(fbp + location) = 0;        // Some blue
            *(fbp + location + 1) = 0;     // A little green
            *(fbp + location + 2) = 0;    // A lot of red
            *(fbp + location + 3) = 0;      // No transparency
        }
    }

    munmap(fbp, screensize);
    close(fbfd);
}
