#ifndef SCLIP
#define SCLIP


#define TRIVIAL_ACCEPT 0
#define TRIVIAL_REJECT 1
#define NON_TRIVIAL 2

#include "clipping/clip.cpp"
#include "utils/util.cpp"
#include "point/point.cpp"
#include "MClip.cpp"
#include "line/line.cpp"

using namespace std;

class SClip {

    public:
    
        SClip(){    

        }

        SClip (Point _topLeft, Point _bottomRight, Clip _lClip) {
            this->topLeft = _topLeft;
            this->bottomRight = _bottomRight ;
            this->lClip = _lClip;

        }

        void zoomIn(){
            topLeft.setAxis(topLeft.getAxis() + 10);
            topLeft.setOrdinat(topLeft.getOrdinat() + 10);
            bottomRight.setAxis(bottomRight.getAxis() - 10);
            bottomRight.setOrdinat(bottomRight.getOrdinat() - 10);
        }

        void zoomOut(){
            topLeft.setAxis(topLeft.getAxis() - 10);
            topLeft.setOrdinat(topLeft.getOrdinat() - 10);
            bottomRight.setAxis(bottomRight.getAxis() + 10);
            bottomRight.setOrdinat(bottomRight.getOrdinat() + 10);
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

         void setCodeForPoint(Point &p){

            Point upperRight(bottomRight.getAxis(),topLeft.getOrdinat());
            Point downLeft(topLeft.getAxis(),bottomRight.getOrdinat());

            Line topBorder(topLeft, upperRight);
            Line bottomBorder(bottomRight, downLeft);
            Line leftBorder (downLeft,topLeft);
            Line rightBorder(upperRight, bottomRight);

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

        bool clipLine(Line &line) {
            Point temp1 = line.getFirstPoint();
            Point temp2 = line.getSecondPoint();
            setCodeForPoint(temp1);
            setCodeForPoint(temp2);
                
            int visibility = isVisible(temp1, temp2);
            //cout << visibility << endl;
            if(visibility == TRIVIAL_ACCEPT){
                return true; // print the line
            } else{
                return false; // don't print the line
            } 
        }

        void render(MClip mClip, int *** framebuffer, vector<bool> active){
            float Sx= (lClip.getBottomRight().getAxis()-lClip.getTopLeft().getAxis())/
                (bottomRight.getAxis() - topLeft.getAxis());

            float Sy =(lClip.getBottomRight().getOrdinat()-lClip.getTopLeft().getOrdinat())/
                (bottomRight.getOrdinat() - topLeft.getOrdinat());

            float tX = (((bottomRight.getAxis()*lClip.getTopLeft().getAxis())-
                (topLeft.getAxis()*lClip.getBottomRight().getAxis()))/
                (bottomRight.getAxis()-topLeft.getAxis()));
                
            float tY = (((bottomRight.getOrdinat()*lClip.getTopLeft().getOrdinat())-
                (topLeft.getOrdinat()*lClip.getBottomRight().getOrdinat()))/
                (bottomRight.getOrdinat()-topLeft.getOrdinat()));

            vector<Polygon> inClip;


            for (int i = 0 ; i < mClip.getObjects().size(); ++i){
               
                Polygon test = mClip.getObjects()[i];
                  if (active[test.getCategori()]) {  
                    bool found = false;
                    int j = 0;
                    while(!found && j < test.getLines().size()) {
                        if (this->clipLine(test.getLines()[j])) {
                            found = true;
                        } else {
                            j++;
                        }
                    }

                    if(found) {
                        Polygon X;

                        Point newTopLeft((test.getTopLeft().getAxis()*Sx)+tX,
                                test.getTopLeft().getOrdinat()*Sy+tY);
                        
                        Point newBottomRight((test.getBottomRight().getAxis()*Sx)+tX,
                            (test.getBottomRight().getOrdinat()*Sy)+tY );

                        X.setTopLeft(newTopLeft);
                        X.setBottomRight(newBottomRight);
                        //cout <<"FOUND"<<endl;
                        for (int k = 0 ; k < test.getLines().size(); ++k) {
                            
                            Point P1((test.getLines()[k].getFirstPoint().getAxis()*Sx)+tX,
                                test.getLines()[k].getFirstPoint().getOrdinat()*Sy+tY);
                        
                            Point P2((test.getLines()[k].getSecondPoint().getAxis()*Sx)+tX,
                                (test.getLines()[k].getSecondPoint().getOrdinat()*Sy)+tY );
                            
                            Line set(P1,P2);
                            X.addLine(set);
                            X.setBlue(mClip.getObjects()[i].getBlue());
                            X.setRed(mClip.getObjects()[i].getRed());
                            X.setGreen(mClip.getObjects()[i].getGreen());
                            
                        }
                        inClip.push_back(X);
                    }
                  }
            }

            for (int i = 0 ; i < inClip.size(); ++ i){
                inClip[i].print(0,0,inClip[i].getRed(),inClip[i].getGreen(),
                inClip[i].getBlue(),lClip,framebuffer);
                inClip[i].scanLine(inClip[i].getRed(),inClip[i].getGreen(),
                inClip[i].getBlue(),lClip,framebuffer);
            }

            mClip.printObjects(framebuffer,0,0, active);

            mClip.drawClipBorder(0,0,255,255,255,framebuffer);
            
            lClip.drawClipBorder(0,0,255,255,255,framebuffer);

            this->drawClipBorder(0,0,255,0,0,framebuffer);

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



        void setlClip(Clip lCplip) {
            this->lClip = lClip;
        }

        void setTopLeft(Point left){
            this->topLeft = left;
        }

        void setBottomRight(Point right){
            this->bottomRight = right;
        }


        Clip getlClip() {
            return this->lClip;
        } 

        Point getTopLeft(){
            return this->topLeft;
        }

        Point getBottomRight(){
            return this->bottomRight;
        }



    private:
        Clip lClip;
        Point topLeft;
        Point bottomRight;

};


#endif