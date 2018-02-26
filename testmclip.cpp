#include "MClip.cpp"
#include "SClip.cpp"
#include <iostream>
#include "utils/util.cpp"
#include "utils/UserInput.cpp"

using namespace std;

int main() {
    UserInput input;

    vector<Polygon> objects;
    Polygon a((char*)"objects/plane.txt");
    objects.push_back(a);
    Point A(10,20);
    Point B(310,320);

    Point C(80,60);
    Point D(155,130);

    Point E(320,20);
    Point F(920,620);

    Clip Lclip(E,F);
    SClip sClip(C,D,Lclip);

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

        MClip mClip(A,B,objects);
        
        sClip.render(mClip,frameBufferArray, 255,255,255);

        Util::printScreen(frameBufferArray);
        usleep(16); // sleep = 1000/fps
    }
    

    return 0;
}