#ifndef QUADRANT
#define QUADRANT

//------------------------------------LIBRARIES-------------------------------------
#include <vector>
#include "Pixel.h"
#include "Greys.h"


#define TOTAL_PIXELS 1080

using namespace std;

//-------------------------------------CLASSES---------------------------------------
//ClassQuadrant
//Class for handling the quadrants in the samplimg
class Quadrant{
    private:
        //Attributes
        //Coodinates of the quadrant
        int maxX;
        int maxY;
        int minX;
        int minY;
        //Colors (RGB and Grey)
        int dominantRGBColor[3];
        int greyScale;
        //Probability
        float probability;
        float bottomRandom;
        float topRandom;
        vector<Pixel*> pixelsInQuadrant; 
    
    public:
        //---------------------------------------------------
        //Set and get of the max value in X
        void setMaxX(int pMaxX){
            this->maxX = pMaxX;
        }

        int getMaxX(){
            return this->maxX;
        }
        //---------------------------------------------------
        //Set and get of the min value in X
        void setMinX(int pMinX){
            this->minX = pMinX;
        }

        int getMinX(){
            return this->minX;
        }

        //---------------------------------------------------
        //Set and get of the max value in Y
        void setMaxY(int pMaxY){
            this->maxY = pMaxY;
        }

        int getMaxY(){
            return this->maxY;
        }

        //---------------------------------------------------
        //Set and get of the min value in Y
        void setMinY(int pMinY){
            this->minY = pMinY;
        }

        int getMinY(){
            return this->minY;
        }

        //---------------------------------------------------
        //Set and get of the RGB color
        void setDominantRGBColor(int pRed, int pGreen, int pBlue){
            this->dominantRGBColor[0] = pRed;
            this->dominantRGBColor[1] = pGreen;
            this->dominantRGBColor[2] = pBlue;
        }

        int* getDominantRGBColor(){
            return this->dominantRGBColor;
        }

        //---------------------------------------------------
        //Set and get of the grey scale
        void setGreyScale(int pRed, int pGreen, int pBlue, vector<Grey> pGreyInImage){
            //float trueGrey = RGBtoGreyScale(pRed, pGreen, pBlue);            
        }
        void setGreyScale(int pGray){
            //float trueGrey = RGBtoGreyScale(pRed, pGreen, pBlue); 
            this->greyScale = pGray;           
        }

        int getGreyInScale(){
            return this->greyScale;
        }

        //---------------------------------------------------
        //set and get of the probability of the quadrant
        void setProbability(){
            this->probability = (100 * ((maxX - minX)*(maxY - minY))) / (TOTAL_PIXELS*TOTAL_PIXELS);
            // cout <<"Prob: " << probability << endl;
        }

        float getProbability(){
            return this->probability;
        }

        //---------------------------------------------------
        //Set and get of the bottomRandom
        void setBottomRandom(float pBottom){
            this->bottomRandom = pBottom;
        }

        float getBottomRandom(){
            return this->bottomRandom;
        }

        //---------------------------------------------------
        //set and get of the too random
        void setTopRandom(float pTop){
            this->topRandom = pTop;
        }

        float getTopRandom(){
            return this->topRandom;
        }

        //---------------------------------------------------
        //Add a pixel in the quadrant
        void addPixel(Pixel* pNewPixel){
            this->pixelsInQuadrant.push_back(pNewPixel);
        }
        //Get the list of pixels
        vector<Pixel*> getPixelsInQuadrant(){
            return this->pixelsInQuadrant;
        }


        void deletePixel(int pPixelIndex){
            this->pixelsInQuadrant.erase(pixelsInQuadrant.begin() + pPixelIndex);
        }

        //---------------------------------------------------
        //to_string
        void toString(){
            cout << "\n\tX Max: " << maxX << "\n\tX Min: " << minX << \
                "\n\tY Max: " << maxY << "\n\tY Min: " << minY << \
                "\n\tBottomRandom:" << bottomRandom << "\n\tTopRandom:" << topRandom <<\
                "\n\tProbability: " << probability << "\n\tPixels in Quadrant: "<< pixelsInQuadrant.size() << endl;
            // for (int currentPixel = 0; currentPixel < pixelsInQuadrant.size(); currentPixel++){
            //     pixelsInQuadrant.at(currentPixel)->toString();
            // } 
        }

};


#endif