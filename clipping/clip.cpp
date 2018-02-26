#ifndef CLIP
#define CLIP

#include <iostream>
#include "../line/line.cpp"

using namespace std;

#define TRIVIAL_ACCEPT 0
#define TRIVIAL_REJECT 1
#define NON_TRIVIAL 2

class Clip {
    public:
        Clip() {

        };

        Clip(Line topBorder, Line rightBorder, Line bottomBorder, Line leftBorder) {
            this->topBorder.setFirstPoint(topBorder.getFirstPoint());
            this->topBorder.setSecondPoint(topBorder.getSecondPoint());
            
            this->bottomBorder.setFirstPoint(bottomBorder.getFirstPoint());
            this->bottomBorder.setSecondPoint(bottomBorder.getSecondPoint());
            
            this->leftBorder.setFirstPoint(leftBorder.getFirstPoint());
            this->leftBorder.setSecondPoint(leftBorder.getSecondPoint());
            
            this->rightBorder.setFirstPoint(rightBorder.getFirstPoint());
            this->rightBorder.setSecondPoint(rightBorder.getSecondPoint());
        }

        Clip(Point topLeft, Point bottomRight){
            int x = bottomRight.getAxis() - topLeft.getAxis();
            int y = bottomRight.getOrdinat() - topLeft.getOrdinat();

            Point upperRight(bottomRight.getAxis(),topLeft.getOrdinat());
            Point downLeft(topLeft.getAxis(),bottomRight.getOrdinat());

            this->topBorder.setFirstPoint(topLeft);
            this->topBorder.setSecondPoint(upperRight);
            
            this->bottomBorder.setFirstPoint(bottomRight);
            this->bottomBorder.setSecondPoint(downLeft);
            
            this->leftBorder.setFirstPoint(downLeft);
            this->leftBorder.setSecondPoint(topLeft);
            
            this->rightBorder.setFirstPoint(upperRight);
            this->rightBorder.setSecondPoint(bottomRight);


        }

        

        void drawClipBorder(int divx, int divy, int r, int g, int b, int *** buffer) {
            topBorder.print(divx, divy, r, g, b, buffer);
            bottomBorder.print(divx, divy, r, g, b, buffer);
            leftBorder.print(divx, divy, r, g, b, buffer);
            rightBorder.print(divx, divy, r, g, b, buffer);
        }

            
        

        void setCodeForPoint(Point &p){
            if(p.getOrdinat() < topBorder.getFirstPoint().getOrdinat()){
                p.setCode(0, '1'); // Top
            }else{
                p.setCode(0, '0');
            }
            if(p.getOrdinat() > bottomBorder.getFirstPoint().getOrdinat()){
                p.setCode(1, '1'); // Bottom
            }else{
                p.setCode(1, '0');
            }
            if(p.getAxis() > rightBorder.getFirstPoint().getAxis()){
                p.setCode(2, '1'); // Right
            }else{
                p.setCode(2, '0');
            }
            if(p.getAxis() < leftBorder.getFirstPoint().getAxis()){
                p.setCode(3, '1'); // Left
            }else{
                p.setCode(3, '0');
            }
        }

        int isVisible(Point p1,Point p2) 
        // Assumption = p1, p2 already coded
        {
            int i,flag=0, same=1;
            
            for(i=0;i<4;i++)
            {
                if((p1.getCode(i)!='0') || (p2.getCode(i)!='0'))
                    flag=1; // change the flag if there is a 1
            }
            
            if(flag==0) return TRIVIAL_ACCEPT; // trivial accept
            
            for(i=0;i<4;i++)
            {
                if((p1.getCode(i)==p2.getCode(i)) && (p1.getCode(i)=='1')) {
                    flag=0; // change the flag if '1' code appear in both points
                }
                if(p1.getCode(i)==p2.getCode(i)) {
                    same=0; // handles if points are in the same area
                }
            }

            if(flag==0){
                return TRIVIAL_REJECT; // trivial reject
            } else if(same == 1){
                return TRIVIAL_REJECT;
            } else {
                return NON_TRIVIAL; // non trivial
            }
        }

        int resetEndPoint(Point &p1, Point p2)
        {
            Point temp;
            int x,y,i;
            float m,k;
            
            if(p1.getCode(3)=='1')
                x = leftBorder.getFirstPoint().getAxis();
            
            if(p1.getCode(2)=='1')
                x = rightBorder.getFirstPoint().getAxis();
            
            if((p1.getCode(3)=='1') || (p1.getCode(2)=='1'))
            {
                m=(float)(p2.getOrdinat() - p1.getOrdinat())/(p2.getAxis() - p1.getAxis());
                k=(p1.getOrdinat() + (m*(x-p1.getAxis())));
                temp.setOrdinat(k);
                temp.setAxis(x);
                
                for(i=0;i<4;i++)
                    temp.setCode(i, p1.getCode(i));
                
                if(temp.getOrdinat() <= bottomBorder.getFirstPoint().getOrdinat()
                        && temp.getOrdinat() >= topBorder.getFirstPoint().getOrdinat()){
                    p1.setAxis(temp.getAxis());
                    p1.setOrdinat(temp.getOrdinat());
                    return 0;
                }
            }
            
            if(p1.getCode(0)=='1')
                y = topBorder.getFirstPoint().getOrdinat();
            
            if(p1.getCode(1)=='1')
                y = bottomBorder.getFirstPoint().getOrdinat();
                
            if((p1.getCode(0)=='1') || (p1.getCode(1)=='1'))
            {
                m=(float)(p2.getOrdinat()-p1.getOrdinat())/(p2.getAxis()-p1.getAxis());
                k=(float)p1.getAxis()+(float)(y-p1.getOrdinat())/m;
                temp.setAxis(k);
                temp.setOrdinat(y);
                
                for(i=0;i<4;i++)
                    temp.setCode(i, p1.getCode(i));
                
                p1.setAxis(temp.getAxis());
                p1.setOrdinat(temp.getOrdinat());
                return 0;
            } else {
                return 0;
            }
        }

        bool clipLine(Line &line) {
            Point temp1 = line.getFirstPoint();
            Point temp2 = line.getSecondPoint();
            setCodeForPoint(temp1);
            setCodeForPoint(temp2);
                
            int visibility = isVisible(temp1, temp2);
            //cout << visibility << endl;
            if(visibility == TRIVIAL_ACCEPT){
                return true; // print the line
            } else if(visibility == TRIVIAL_REJECT){
                return false; // don't print the line
            } else {
                // clip the line
                resetEndPoint(temp1, temp2);
                resetEndPoint(temp2, temp1);

                // cout << "lama" << line.getFirstPoint().getAxis() << line.getFirstPoint().getOrdinat() 
                //     << line.getSecondPoint().getAxis() << line.getSecondPoint().getOrdinat() << endl;
 
                line.setFirstPoint(temp1);
                line.setSecondPoint(temp2);

                // cout << "baru" << line.getFirstPoint().getAxis() << line.getFirstPoint().getOrdinat() 
                //     << line.getSecondPoint().getAxis() << line.getSecondPoint().getOrdinat() << endl;

                return true;
            }
        }

        Line getTopBorder() {
            return this->topBorder;
        }


        Line getRightBorder() {
            return this->rightBorder;
        }

        Line getBottomBorder() {
            return this->bottomBorder;
        }

        Line getLeftBorder() {
            return this->leftBorder;
        }

        Point getTopLeft() {
            return topBorder.getFirstPoint();
        }
        
        Point getBottomRight() {
            return rightBorder.getSecondPoint();
        }

    private:
        Line topBorder;
        Line bottomBorder;
        Line leftBorder;
        Line rightBorder;
};

#endif
