#ifndef PIXEL
#define PIXEL

#include <iostream>

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

        int getCoordinateX(){
            return coordinateX;
        }

        void setCoordinateY( int pCoordinateY){
            coordinateY = pCoordinateY;
        }

        int getCoordinateY(){
            return coordinateY;
        }

        void setCoordinates(int pCoordinateX, int pCoordinateY){
            coordinateX = pCoordinateX;
            coordinateY = pCoordinateY;
        }

        void setRGBColor(int pRed, int pGreen, int pBlue){
            RGBColor[0] = pRed;
            RGBColor[1] = pGreen;
            RGBColor[2] = pBlue;
        }

        int* getRGBColor(){
            return RGBColor;
        }

        void toString(){
            cout <<"----------------PIXEL----------------" <<endl;
            cout << "\tX Coordinate: " << coordinateX \
            << "\n\tY Coordinate: " << coordinateY << endl;
        }

};


#endif