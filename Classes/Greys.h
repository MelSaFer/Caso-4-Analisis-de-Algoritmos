#ifndef GREYS
#define GREYS

//LIBRARIES------------------------------------------------------
#include <iostream>
#include <vector>


using namespace std;

#define MAX_GRAY 20.0

class Grey{
    private:
        int identificationId;
        float minValue;
        float maxValue;

    public:
        Grey(){};

        Grey( int pIdentificationId, float pMinValue, float pMaxValue){
            this->identificationId = pIdentificationId;
            this->maxValue = pMaxValue;
            this->minValue = pMinValue;
        }
        //---------------------------------------------------
        void setIdentification( int pNewIdentification){
            this->identificationId = pNewIdentification;
        }

        int getIdentification(){
            return this->identificationId;
        }
        //---------------------------------------------------
        void setMinValue( float pNewMinValue){
            this->minValue = pNewMinValue;
        }

        float getMinValue(){
            return this->minValue;
        }
        //---------------------------------------------------
        void setMaxValue( float pNewMaxValue){
            this->maxValue = pNewMaxValue;
        }

        float getMaxValue(){
            return this->maxValue;
        }
        //---------------------------------------------------

        void toString(){
            cout <<"------------------------------------------\n"<< "Id: " << this->identificationId \
            << "\nMin Value: " << this->minValue << "\nMax Value: " << this->maxValue << endl;
        }

};

//FUN.

float RGBtoGreyScale(int pRed, int pGreen, int pBlue){
    float greyValue = 0.299 * (pRed + 0.0) + 0.587 * (pGreen + 0.0) + 0.114 * (pBlue + 0.0);
    cout << "Grey value: " << greyValue << endl;
    return greyValue;
}

Grey generateGrey(float pNewMinValue, int pNewIdentification){
    float newMaxValue = pNewMinValue + (256.0/MAX_GRAY);
    Grey newGrey(pNewIdentification, pNewMinValue, newMaxValue);
    return newGrey;
}

int classifyGrey(float pAGrey, vector<Grey> scaleOfGreys){
    for (int currentGrey = 0; currentGrey < MAX_GRAY ; currentGrey++){
        if( (scaleOfGreys.at(currentGrey).getMinValue() <= pAGrey) && (scaleOfGreys.at(currentGrey).getMaxValue() > pAGrey) ){
            cout << "Es gris: " << scaleOfGreys.at(currentGrey).getIdentification() << endl;
            return scaleOfGreys.at(currentGrey).getIdentification();
        }
    }
    return 0;
}

vector<Grey> greysInit(){
    vector<Grey> greysRanges;
    float minValue = 0.0;
    for(int currentGray = 1; currentGray <= MAX_GRAY; currentGray++){
        greysRanges.push_back(generateGrey(minValue, currentGray));
        minValue = greysRanges.at(greysRanges.size()-1).getMaxValue();
    }
    return greysRanges;
}




#endif