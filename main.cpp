#include "MClip.cpp"
#include "SClip.cpp"
#include <iostream>
#include "utils/util.cpp"
#include "utils/UserInput.cpp"

using namespace std;

int main() {
    UserInput input;

    vector<Polygon> objects;
    string result;
    for(int i = 2;i < 97;i++) {
        result = "objects/" + std::to_string(i) + ".txt";
        Polygon obj (result);
        obj.update(0,50);
        objects.push_back(obj);
    }
    Point A(10,20);
    Point B(410,500);

    Point X(100,190);
    Point Y(480,640);

    // Point C(170,230);
    // Point D(245,300);

    Point C(80,60);
    Point D(150,130);

    Point E(520,20);
    Point F(1220,720);

    Clip Lclip(E,F);
    SClip sClip(C,D,Lclip);

    MClip mClip(A,B,objects);
    int *** frameBufferArray = Util::initFrameBuffer();

    while(1){
        Util::clearFrameBuffer(frameBufferArray);
        if(input.getKeyPress('q')){
            break;
        } else {
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
        
        
        sClip.render(mClip,frameBufferArray, 255,255,255);

        Util::printScreen(frameBufferArray);
        usleep(16); // sleep = 1000/fps
    }
    

    return 0;
}