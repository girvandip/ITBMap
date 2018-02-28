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


        Point getTopLeft(){
            return this->topLeft;
        }

        Point getBottomRight(){
            return this->bottomRight;
        }

        vector<Polygon> getObjects(){
            return this->objects;
        }

        void setTopLeft(Point left){
            this->topLeft = left;
        }
        void setBottomRight(Point right){
            this->bottomRight = right;
        }

        void setPolygon (vector<Polygon> objects) {
            this->objects = objects;
        }

        void printObjects(int ***framebuffer,int dx, int dy,int r, int g, int b){
            for (int i = 0 ; i< objects.size() ; ++i){
                objects[i].printNoCLip(0,0,objects[i].getRed(),
                    objects[i].getGreen(),objects[i].getBlue(),framebuffer);
                objects[i].scanLineNoClip(objects[i].getRed(),
                    objects[i].getGreen(),objects[i].getBlue(),framebuffer);
            }
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



    private:
        vector<Polygon> objects ;
        Point topLeft;
        Point bottomRight;


};


#endif