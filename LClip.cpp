#ifndef LCLIP
#define LCLIP

#include "utils/util.cpp"
#include "point/point.cpp"
#include <iostream>

using namespace std;

class LClip {

    public:
        LClip(){

        }

        LClip( Point _topLeft, Point _bottomRight){
            this->topLeft = _topLeft;
            this->bottomRight = _bottomRight;
        }

        void setTopLeft(Point left){
            this->topLeft = left;
        }

        void setBottomRight(Point right){
            this->bottomRight = right;
        }

        Point getTopLeft(){
            return this->topLeft;
        }

        Point getBottomRight(){
            return this->bottomRight;
        }

    private:
        Point topLeft;
        Point bottomRight;


};


#endif