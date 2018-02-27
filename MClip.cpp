#ifndef MCLIP
#define MCLIP


#include <iostream>
#include "polygon/polygon.cpp"
#include "point/point.cpp"
#include <vector>

using namespace std;

class MClip {

    public:
        MClip() {

        }

        MClip(Point _topLeft, Point _bottomRight, vector<Polygon> _objects) {

            this-> topLeft = _topLeft;
            this-> bottomRight = _bottomRight;
            this-> objects = _objects;

        }


        void printObjects(int ***framebuffer,int dx, int dy,int r, int g, int b){
            
            for (int i = 0 ; i< objects.size() ; ++i){
                //objects[i].update(topLeft.getAxis(),topLeft.getOrdinat());
                objects[i].printNoCLip(dx,dy,r,g,b,framebuffer);
                objects[i].scanLineNoClip(r,g,b,framebuffer);
            }
        }

        vector<Polygon> getObjects(){
            return this->objects;
        }

        void setTopLeft(Point left){
            this->topLeft = left;
        }

        void drawClipBorder(int divx, int divy, int r, int g, int b, int *** buffer) {
            
            Point upperRight(bottomRight.getAxis(),topLeft.getOrdinat());
            Point downLeft(topLeft.getAxis(),bottomRight.getOrdinat());

            Line topBorder(topLeft, upperRight);
            Line bottomBorder(bottomRight, downLeft);
            Line leftBorder (downLeft,topLeft);
            Line rightBorder(upperRight, bottomRight);
            
            
            topBorder.print(divx, divy, r, g, b, buffer);
            bottomBorder.print(divx, divy, r, g, b, buffer);
            leftBorder.print(divx, divy, r, g, b, buffer);
            rightBorder.print(divx, divy, r, g, b, buffer);
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
        vector<Polygon> objects ;
        Point topLeft;
        Point bottomRight;


};


#endif