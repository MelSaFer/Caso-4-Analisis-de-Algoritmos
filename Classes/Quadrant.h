#ifndef QUADRANT
#define QUADRANT

//------------------------------------LIBRARIES-------------------------------------
#include <vector>
#include "Pixel.h"

#define TOTAL_PIXELS 1080

using namespace std;

//ClassCuadrant

class Quadrant{
    private:
        //Attributes
        int maxX;
        int maxY;
        int minX;
        int minY;
        vector<Pixel*> pixelsInQuadrant; 
        int dominantRGBColor[3];
        float probability;

    
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

        void addPixel(int pXCoord, int pYCoord, int pRed, int pGreen, int pBlue){
            Pixel* newPixel = new Pixel();
            newPixel->setCoordinateX(pXCoord);
            newPixel->setCoordinateY(pYCoord);
            newPixel->setRGBColor(pRed, pGreen, pBlue);
            pixelsInQuadrant.push_back(newPixel);
        }

        void setDominantRGBColor(int pRed, int pGreen, int pBlue){
            dominantRGBColor[0] = pRed;
            dominantRGBColor[1] = pGreen;
            dominantRGBColor[2] = pBlue;
        }

        int* getDominantRGBColor(){
            return dominantRGBColor;
        }



        void setProbability(){
            probability = (100 * ((maxX - minX)*(maxY - minY))) / (TOTAL_PIXELS*TOTAL_PIXELS);
        }

        float getProbability(){
            return probability;
        }

};


#endif