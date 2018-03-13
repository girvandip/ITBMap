    #include "shootPlane.h"

void line(int x0, int y0, int x1, int y1, int divx, int divy, int r, int g, int b) {
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

void printChar2(char character, int dx, int dy, int r, int g, int b){
    FILE *test;
    char i;
    int lines, j;
    int *coordinates;

    switch (character) {
        case 'a':
            test = fopen("characters2/a.txt", "r");
            break;
        case 'b':
            test = fopen("characters2/b.txt", "r");
            break;
        case 'c':
            test = fopen("characters2/c.txt", "r");
            break;
        case 'd':
            test = fopen("characters2/d.txt", "r");
            break;
        case 'f':
            test = fopen("characters2/f.txt", "r");
            break;
        case 'g':
            test = fopen("characters2/g.txt", "r");
            break;
        case 'h':
            test = fopen("characters2/h.txt", "r");
            break;
        case 'i':
            test = fopen("characters2/i.txt", "r");
            break;
        case 'j':
            test = fopen("characters2/j.txt", "r");
            break;
        case 'l':
            test = fopen("characters2/l.txt", "r");
            break;
        case 'm':
            test = fopen("characters2/m.txt", "r");
            break;
        case 'n':
            test = fopen("characters2/n.txt", "r");
            break;
        case 'o':
            test = fopen("characters2/o.txt", "r");
            break;
        case 'r':
            test = fopen("characters2/r.txt", "r");
            break;
        case 'u':
            test = fopen("characters2/u.txt", "r");
            break;
        case 'y':
            test = fopen("characters2/y.txt", "r");
            break;
        case 'z':
            test = fopen("characters2/z.txt", "r");
            break;
    }

    if(test != NULL){
        i = fgetc(test);
        lines = atoi(&i); // number of lines
        i = fgetc(test); // delete enter
        
        coordinates = (int*) malloc ((4 * lines) * sizeof(int));

        for(i = 0; i < lines; i++){
            int temp = 0, temp1 = 0, temp2 = 0, temp3 = 0;
            for(j = 0; j < 3; j++){
                char c = fgetc(test) - 48;
                temp = temp*10 + c;
            }
            fgetc(test);

            for(j = 0; j < 3; j++){
                char c = fgetc(test) - 48;
                temp1 = temp1*10 + c;
            }
            fgetc(test);

            for(j = 0; j < 3; j++){
                char c = fgetc(test) - 48;
                temp2 = temp2*10 + c;
            }
            fgetc(test);

            for(j = 0; j < 3; j++){
                char c = fgetc(test) - 48;
                temp3 = temp3*10 + c;
            }
            fgetc(test);

            coordinates[(i*4)] = temp;
            coordinates[(i*4)+1] = temp1;
            coordinates[(i*4)+2] = temp2;
            coordinates[(i*4)+3] = temp3;
        }
        //printf("keluar\n");

        for(i = 0; i < lines; i++){
            line(coordinates[i*4], 
                coordinates[i*4+1],
                coordinates[i*4+2],
                coordinates[i*4+3],
                dx, dy, r, g, b);
        }
    
        free(coordinates);
        fclose(test);
    }
}

void clearScreen2() {
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
