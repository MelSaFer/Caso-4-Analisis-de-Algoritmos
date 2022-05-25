#ifndef GREYS
#define GREYS

//------------------------------------LIBRARIES-------------------------------------
#include <iostream>
#include <vector>

//Namespace
using namespace std;

//Define the greys we are handling for traslating the RGB to greys
#define MAX_GREY 20.0

//-------------------------------------CLASSES---------------------------------------
/*
Class Grey 
This class is use to handle the color in the image 
 */
class Grey{
    private:
        int identificationId;   //This is for identify the greys (grey1, grey2, grey3...)
        float minValue;         //This are the values of the range
        float maxValue;

    public:
        Grey(){};

        /*
        Constructor
        Entries: The identificator of the grey, the min value (at first is 0, the the min is the max of the last gray)
                  and the max value (is the min value + (256 / the cuantity of grays) )  
        Output: None
        */
        
        Grey( int pIdentificationId, float pMinValue, float pMaxValue){
            this->identificationId = pIdentificationId;
            this->maxValue = pMaxValue;
            this->minValue = pMinValue;
        }
        //---------------------------------------------------
        //Set and get of the identificator
        void setIdentification( int pNewIdentification){
            this->identificationId = pNewIdentification;
        }

        int getIdentification(){
            return this->identificationId;
        }
        //---------------------------------------------------
        //Set and get of the Min Value
        void setMinValue( float pNewMinValue){
            this->minValue = pNewMinValue;
        }

        float getMinValue(){
            return this->minValue;
        }
        //---------------------------------------------------
        //Set and get of the Max Value
        void setMaxValue( float pNewMaxValue){
            this->maxValue = pNewMaxValue;
        }

        float getMaxValue(){
            return this->maxValue;
        }
        //---------------------------------------------------
        //To string
        void toString(){
            cout <<"------------------------------------------\n"<< "Id: " << this->identificationId \
            << "\nMin Value: " << this->minValue << "\nMax Value: " << this->maxValue << endl;
        }

};

//FUNTIONS--------------------------------------------------------------------------------------------------
/*___________________________________________________________________________________________________________
Function for convert and RGB color to scale of greys
Entries: the color RED, GREEN and BLUE of the RGB scale
Ouput: The RGB converted to grey scale
*/
float RGBtoGreyScale(int pRed, int pGreen, int pBlue){
    //We use the formula for converting an RGB color to grey scale
    float greyValue = 0.299 * (pRed + 0.0) + 0.587 * (pGreen + 0.0) + 0.114 * (pBlue + 0.0);
    cout << "Grey value: " << greyValue << endl;
    return greyValue;
}

/*___________________________________________________________________________________________________________
Function for generate a new grey 
Entries: the min value and the identificator of the new grey
Ouput: the new grey
*/
Grey generateGrey(float pNewMinValue, int pNewIdentification){
    float newMaxValue = pNewMinValue + (256.0/MAX_GREY);  //This calculate the max value
    Grey newGrey(pNewIdentification, pNewMinValue, newMaxValue); //Create the new grey
    return newGrey;
}

/*___________________________________________________________________________________________________________
Function classify a grey in the scale we generated
Entries: a float with the value of the grey and a list of greys
Ouput: the identificator of the current grey
*/
int classifyGrey(float pAGrey, vector<Grey> scaleOfGreys){
    for (int currentGrey = 0; currentGrey < MAX_GREY ; currentGrey++){
        if( (scaleOfGreys.at(currentGrey).getMinValue() <= pAGrey) && (scaleOfGreys.at(currentGrey).getMaxValue() > pAGrey) ){
            cout << "Es gris: " << scaleOfGreys.at(currentGrey).getIdentification() << endl;
            return scaleOfGreys.at(currentGrey).getIdentification();
        }
    }
    return 0;
}

/*___________________________________________________________________________________________________________
Function for create the scale of greys
Entries: None
Ouput: The scale of greys
*/
vector<Grey> greysInit(){
    vector<Grey> greysRanges;  //A vector for save the scale of greys
    float minValue = 0.0; //At first is 0.0 but then takes other values
    //This for is for create the MAX_GREY greys
    for(int currentGray = 1; currentGray <= MAX_GREY; currentGray++){ 
        greysRanges.push_back(generateGrey(minValue, currentGray));
        minValue = greysRanges.at(greysRanges.size()-1).getMaxValue();
    }
    return greysRanges;
}




#endif