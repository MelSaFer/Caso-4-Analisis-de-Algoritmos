#ifndef PIXEL
#define PIXEL

using namespace std;

//ClassCuadrant

class Pixel{
    private:
        int coordinateX;
        int coordinateY;
        int RGBColor[3];
        //RGB

    public:

        void setCoordinateX( int pCoordinateX){
            coordinateX = pCoordinateX;
        }

        int getCoordinateX(int pCoordinateX){
            return coordinateX;
        }

        void setCoordinateY( int pCoordinateY){
            coordinateY = pCoordinateY;
        }

        int getCoordinateY(int pCoordinateY){
            return coordinateY;
        }

        void setRGBColor(int pRed, int pGreen, int pBlue){
            RGBColor[0] = pRed;
            RGBColor[1] = pGreen;
            RGBColor[2] = pBlue;
        }

        int* getRGBColor(){
            return RGBColor;
        }

};


#endif