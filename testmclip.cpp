#include "MClip.cpp"
#include "SClip.cpp"
#include <iostream>
#include "utils/util.cpp"

using namespace std;

int main() {

    vector<Polygon> objects;
    Polygon a((char*)"objects/plane.txt");
    objects.push_back(a);
    Point A(10,20);
    Point B(310,320);

    Point C(40,20);
    Point D(190,160);

    Point E(320,20);
    Point F(920,620);


    int *** frameBufferArray = Util::initFrameBuffer();

    Clip Lclip(E,F);

    


    // Lclip.drawClipBorder(0,0,255,255,255,frameBufferArray);

    MClip mClip(A,B,objects);
    


    SClip sClip(C,D,Lclip);
    sClip.render(mClip,frameBufferArray, 255,255,255);

    Util::printScreen(frameBufferArray);

    return 0;
}