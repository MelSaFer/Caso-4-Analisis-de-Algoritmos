#ifndef QUADRANT
#define QUADRANT

//------------------------------------LIBRARIES-------------------------------------
#include <vector>
#include "Pixel.h"
#include "Greys.h"

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
        int greyScale;
        float probability;
        float bottomRandom;
        float topRandom;

    
    public:

        void setMaxX(int pMaxX){
            maxX = pMaxX;
        }

        int getMaxX(){
            return maxX;
        }

        void setMinX(int pMinX){
            minX = pMinX;
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
            minY = pMinY;
        }

        int getMinY(){
            return minY;
        }

        void addPixel(Pixel* pNewPixel){
            pixelsInQuadrant.push_back(pNewPixel);
        }

        vector<Pixel*> getPixelsInQuadrant(){
            return pixelsInQuadrant;
        }

        void setDominantRGBColor(int pRed, int pGreen, int pBlue){
            dominantRGBColor[0] = pRed;
            dominantRGBColor[1] = pGreen;
            dominantRGBColor[2] = pBlue;
        }

        int* getDominantRGBColor(){
            return dominantRGBColor;
        }

        void setGreyScale(int pRed, int pGreen, int pBlue, vector<Grey> pGreyInImage){
            float trueGrey = RGBtoGreyScale(pRed, pGreen, pBlue);            
        }

        int getGreyInScale(){
            return greyScale;
        }

        void setProbability(){
            probability = (100 * ((maxX - minX)*(maxY - minY))) / (TOTAL_PIXELS*TOTAL_PIXELS);
            cout <<"Prob: " << probability << endl;
        }

        float getProbability(){
            return probability;
        }

        void setBottomRandom(float pBottom){
            this->bottomRandom = pBottom;
        }

        float getBottomRandom(){
            return this->bottomRandom;
        }

        void setTopRandom(float pTop){
            this->topRandom = pTop;
        }

        float getTopRandom(){
            return this->topRandom;
        }

        void toString(){
            cout << "\n\tX Max: " << maxX << "\n\tX Min: " << minX << \
                "\n\tY Max: " << maxY << "\n\tY Min: " << minY << \
                "\n\tBottomRandom:" << bottomRandom << "\n\tTopRandom:" << topRandom <<\
                "\n\tProbability: " << probability << "\n\tPixels in Quadrant: "<< endl;
            for (int currentPixel = 0; currentPixel < pixelsInQuadrant.size(); currentPixel++){
                pixelsInQuadrant.at(currentPixel)->toString();
            } 
        }

};


#endif