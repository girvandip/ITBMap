#ifndef POINT
#define POINT
#define PI 3.14159265
#include <math.h>

using namespace std;

class Point {
    public:
        Point() {
            x = 0;
            y = 0;
            for(int i = 0; i < 4; i++) code[i] = '\0';
        }
        Point(int x, int y) {
            this->x = x;
            this->y = y;
            for(int i = 0; i < 4; i++) code[i] = '\0';
        }

        Point(const Point& p) {
            this->x = p.x;
            this->y = p.y;
            for(int i = 0; i < 4; i++) this->code[i] = p.code[i];
        }

        int getAxis() {
            return this->x;
        }

        int getOrdinat() {
            return this->y;
        }

        char getCode(int i) {
            return code[i];
        }

        void setAxis(int x) {
            this->x = x;
        }

        void setOrdinat(int y) {
            this->y = y;
        }

        void setCode(int i, char code) {
            this->code[i] = code;
        }
        
        void rotate(int degree, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
            double val = PI/180;
            float sinus = sin(degree*val);
            float minsin = -sinus;
            float cosinus = cos(degree*val);
            float centerX = ((topLeftX + bottomRightX) / 2);
            float centerY = ((topLeftY + bottomRightY) / 2);
            
            float tempx = getAxis() - centerX;
            float tempy = getOrdinat() - centerY;
            float finalx = (tempx * cosinus + tempy * minsin) + centerX; 
            float finaly = (tempx * sinus + tempy * cosinus) + centerY;
            //round to int
            setAxis(finalx);
            setOrdinat(finaly);
        }
        
        void move(int h, int v,int topLeftX, int topLeftY, int bottomRightX, int bottomRightY){
			float centerX = ((topLeftX + bottomRightX) / 2);
            float centerY = ((topLeftY + bottomRightY) / 2);
            float finalx = getAxis() + h;
            float finaly = getOrdinat() + v;
            
            setAxis(finalx);
            setOrdinat(finaly);
		}

        void scaleByPoint(float scale, Point P) {
            float finalx = scale * (getAxis() - P.getAxis()) + P.getAxis();
            float finaly = scale * (getOrdinat() - P.getOrdinat()) + P.getOrdinat();
            setAxis(finalx);
            setOrdinat(finaly);
        }
        
        void scaleNew(float scale) {
            setAxis(scale * getAxis());
            setOrdinat(scale * getOrdinat());
        }

        void scale(float scale, int topLeftX, int topLeftY, int bottomRightX, int bottomRightY) {
            float centerX = ((topLeftX + bottomRightX) / 2);
            float centerY = ((topLeftY + bottomRightY) / 2);
            
            float finalx = scale * (getAxis() - centerX) + centerX;
            float finaly = scale * (getOrdinat() - centerY) + centerY;
            setAxis(finalx);
            setOrdinat(finaly);
        }

        void update(int divx, int divy) {
            x += divx;
            y += divy;
        }
    
    private:
        float x, y;
        char code[4];
};

#endif
