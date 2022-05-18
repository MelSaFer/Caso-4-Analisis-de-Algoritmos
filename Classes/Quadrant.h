#ifndef QUADRANT
#define QUADRANT

//------------------------------------LIBRARIES-------------------------------------
#include <vector>
#include "Pixel.h"

using namespace std;

//ClassCuadrant

class Quadrant{
    private:
        //Attributes
        int maxX;
        int maxY;
        int minX;
        int minY;
        vector<Pixel*> pixelsInQuadrant; //Hay que revisar si tiene que ser puntero
        //Color dominante
        int dominantRGBColor[3];
    
    public:

        void setMaxX(int pMaxX){
            maxX = pMaxX;
        }

        int getMaxX(){
            return maxX;
        }

        void setMinX(int pMinX){
            maxX = pMinX;
        }

        int getMinX(){
            return minX;
        }

        void setMaxY(int pMaxY){
            maxY = pMaxY;
        }

        int getMaxY(){
            return maxY;
        }

        void setMinY(int pMinY){
            maxY = pMinY;
        }

        int getMinY(){
            return minY;
        }

        void addPixel(int pXCoord, int pYCoord){
            Pixel* p = new Pixel();
            pixelsInQuadrant.push_back(p);
        }

        void setDominantRGBColor(int pRed, int pGreen, int pBlue){
            dominantRGBColor[0] = pRed;
            dominantRGBColor[1] = pGreen;
            dominantRGBColor[2] = pBlue;
        }

        int* getDominantRGBColor(){
            return dominantRGBColor;
        }




};


#endif