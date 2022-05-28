#include <iostream>

using namespace std;

class point {
    private: 
        int coordX;
        int coordY;
        // int yMin;
        // int yMax;
        int gray;
        int size;
        int shape;
    public:
        point(int pCoordX, int pCoordY, int pGray, int pSize, int pShape) {
            this->coordX = pCoordX;
            this->coordY = pCoordY;
            this->gray = pGray;
            this->size = pSize;
            this->shape = pShape;
        }

        void setCoordX (int pCoordX){
            this->coordX = pCoordX;
        }

        int getCoordX (){
            return this->coordX;
        }

        void setCoordY (int pCoordY){
            this->coordY = pCoordY;
        }

        int getCoordY (){
            return this->coordY;
        }
        
        void setGray(int pGray){
            this->gray = pGray;
        }

        int getGray(){
            return this->gray;
        }

        void setSize(int pSize){
            this->size = pSize;
        }

        int getSize(){
            return this->size;
        }

        void setShape(int pShape){
            this->shape = pShape;
        }

        int getShape(){
            return this->shape;
        }
};