#include "MClip.cpp"
#include "SClip.cpp"
#include <iostream>
#include "utils/util.cpp"
#include "utils/UserInput.h"

using namespace std;


    UserInput input;
    vector<bool> categories;
    vector<Polygon> objects;
    unsigned char data[3];


    void createCategories(vector<bool>& categories) {
        for(int i = 0; i < 5; i ++){
            // if (i % 2 == 0) {
            //     categories.push_back(true);
            // } else {
                categories.push_back(true);
            // }
        }
    }

    void createObjects(vector<Polygon>& objects) {
        string result;
        for(int i = 2;i < 96;i++) {
            result = "objects/" + std::to_string(i) + ".txt";
            Polygon obj (result);
            obj.update(0,50);
            objects.push_back(obj);
        }
    }



int tugas6() {

    // Mouse
    int mfd, bytes;


    const char *pDevice = "/dev/input/mice";
    // Open Mouse
    mfd = open(pDevice, O_RDWR | O_NONBLOCK);
    if(mfd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }

    int left, middle, right;
    signed char x, y, leftClick, rightClick;
    //initiation
    createObjects(objects);
    createCategories(categories);

    Point A(10,20);
    Point B(410,500);

    Point C(80,60);
    Point D(150,130);

    Point E(520,20);
    Point F(1220,720);

    Clip Lclip(E,F);
    SClip sClip(C,D,Lclip);

    MClip mClip(A,B,objects);
    int *** frameBufferArray = Util::initFrameBuffer();

    while(1){

        // read mouse input_event

        bytes = read(mfd, data, sizeof(data));
        //clear the buffer before print it
        Util::clearFrameBuffer(frameBufferArray);
        if(input.getKeyPress('q')){
            break;
        } else {
            if (bytes > 0 ){
              x = data[1];
              y = data[2];
              leftClick = data[0] & 0x1;
              rightClick = data[0] & 0x2;
              C.update(x,-y);
              D.update(x,-y);
              sClip.setTopLeft(C);
              sClip.setBottomRight(D);

              if (leftClick == 1) {
                C.update(10,10);
                D.update(-10,-10);
                sClip.setTopLeft(C);
                sClip.setBottomRight(D);
              } else if (rightClick == 2){
                C.update(-10,-10);
                D.update(10,10);
                sClip.setTopLeft(C);
                sClip.setBottomRight(D);
              }
            }
            if(input.getKeyPress('d')){
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
            } else if(input.getKeyPress('z')){
                C.update(10,10);
                D.update(-10,-10);
                sClip.setTopLeft(C);
                sClip.setBottomRight(D);
            } else if(input.getKeyPress('x')){
                C.update(-10,-10);
                D.update(10,10);
                sClip.setTopLeft(C);
                sClip.setBottomRight(D);
            }
        }

        Lclip.drawClipBorder(0,0,255,255,255,frameBufferArray);

        sClip.render(mClip,frameBufferArray,categories);

        Util::printScreen(frameBufferArray);
        usleep(16); // sleep = 1000/fps
    }

    Util::clearFrameBuffer(frameBufferArray);
    Util::printScreen(frameBufferArray);


    return 0;
}
