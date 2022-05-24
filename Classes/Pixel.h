#ifndef PIXEL
#define PIXEL

#include <iostream>
#include "Greys.h"

using namespace std;

//ClassCuadrant

class Pixel{
    private:
        int coordinateX;
        int coordinateY;
        int RGBColor[3];
        int greyColor;
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

        void setGrey(int pRed, int pGreen, int pBlue, vector<Grey> pGreyInImage){
            float trueGrey = RGBtoGreyScale(pRed, pGreen, pBlue);
            this-> greyColor = classifyGrey(trueGrey, pGreyInImage);
            cout << "El gris del pixel es: " << this->greyColor << endl;

        }

        int getGrey(){
            return this->greyColor;
        }

        void toString(){
            cout <<"----------------PIXEL----------------" <<endl;
            cout << "\tX Coordinate: " << coordinateX \
            << "\n\tY Coordinate: " << coordinateY << endl;
        }

};


#endif