#ifndef PROBABILISTIC
#define PROBABILISTIC

//------------------------------------LIBRARIES-------------------------------------
#include <iostream>
#include <random>
#include "Classes/Greys.h"
#include <algorithm>
// #include <vector>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "Classes/Pixel.h"

using namespace std;

// Total pixels of the image 1080 * 1080
#define TOTAL_PIXELS_IMAGE 648000 
// The porcentage of the sampling (0-1)
#define MAX_SAMPLING_PORCENTAGE 0.40
// The xMin - xMax distance
#define SIDE_LENGHT 1080.0
// The yMin - yMax distance
#define WIDTH_LENGHT 600.0
// #define EXPAND_RANGES 30.0
// The half of the side of a expand quadrant
#define AREA_ADDITION 15


// Global Variables
// -------------------------------------------
// Sampled pixels
int pixelsQuantity = 0;
// The area of the initial image + the area of each generated quadrant
int actualArea = SIDE_LENGHT * WIDTH_LENGHT;

//FUNTIONS--------------------------------------------------------------------------------------------------
/*___________________________________________________________________________________________________________
Function for update de probability of the Table
Entries: the probability table
*/
void updateProbability (vector<Quadrant*> &pProbabilityTable){

    int indexTable = pProbabilityTable.size();
    int quadrantLenght, quadrantWidth, quadrantArea;
    float probability; // probability of each quadrant
    float lastPorcentage = 0.0;

    for(int pRowPosition = 0; pRowPosition < indexTable; pRowPosition++){ // go through the elements of the table

        if(pRowPosition != indexTable - 1){ // if is not the last element
            // update de dimensions of the quadrant
            quadrantLenght = pProbabilityTable.at(pRowPosition)->getMaxX() - pProbabilityTable.at(pRowPosition)->getMinX();
            quadrantWidth = pProbabilityTable.at(pRowPosition)->getMaxY() - pProbabilityTable.at(pRowPosition)->getMinY();
            quadrantArea = quadrantLenght * quadrantWidth; // calculate the area

            probability = (quadrantArea + 0.0) / (actualArea + 0.0);

            // assign the range of the random of the current quadrant
            pProbabilityTable.at(pRowPosition)->setBottomRandom(lastPorcentage); 
            pProbabilityTable.at(pRowPosition)->setTopRandom(lastPorcentage + probability);

            lastPorcentage += probability;
        }
        else{ // last element
            pProbabilityTable.at(pRowPosition)->setBottomRandom(lastPorcentage);
        }     
    }
}

/*___________________________________________________________________________________________________________
Function to add a new quadrant
    We pick a pixel between (xMin, xMax) in X and (yMin, yMax) in Y
    The area of the newArea is (AREA_ADDITION*2) * (AREA_ADDITION*2)
Entries: image data, the probability table, grays, index of the table
*/
void totalAreaCase (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage, int indexTable){
    // cout << "===================================" << endl;
    // cout << "Funcion del area grande" << endl;

    // Random process
    random_device rd;
    default_random_engine eng(rd());

    // the 2 randoms for the new x and the new y
    uniform_real_distribution<> distr(pProbabilityTable.at(indexTable)->getMinX(), pProbabilityTable.at(indexTable)->getMaxX() + 1); // random range
    uniform_real_distribution<> distr2(pProbabilityTable.at(indexTable)->getMinY(), pProbabilityTable.at(indexTable)->getMaxY() + 1); // random range

    int newCoordX = distr(eng);
    int newCoordY = distr2(eng);

    // cout << "Coordenadas random: " << newCoordX << ", " << newCoordY << endl;

    // increase the generated pixels
    pixelsQuantity++;

    // create the new pixel
    Pixel* newQuadrantPixel = new Pixel();
    newQuadrantPixel->setCoordinateX(newCoordX);
    newQuadrantPixel->setCoordinateY(newCoordY);

    // asign the grey color
    int red, green, blue;
    const size_t RGB = 3;
    size_t index;

    index = RGB * (newQuadrantPixel->getCoordinateY() * 1080 + newQuadrantPixel->getCoordinateX());

    red = pImageFile[index + 0];
    green = pImageFile[index + 1];
    blue = pImageFile[index + 2];

    // cout << "Colores: " << red << ", " << green << ", " << blue << endl;

    newQuadrantPixel->setRGBColor(red,green,blue);
    newQuadrantPixel->setGrey(red, green, blue, pGreyInImage);

    // Create the new quadrant
    // we check if the area of the new pixel is outside the limits of the image
    Quadrant* newQuadrant = new Quadrant();
    if((newCoordX-AREA_ADDITION) >= 240){
        newQuadrant->setMinX(newCoordX-AREA_ADDITION);
    }
    else{
        newQuadrant->setMinX(240);
    }

    if((newCoordY-AREA_ADDITION) >= 0){
        newQuadrant->setMinY(newCoordY-AREA_ADDITION);
    }
    else{
        newQuadrant->setMinY(0);
    }

    if((newCoordX+AREA_ADDITION) <= 840){
        newQuadrant->setMaxX(newCoordX+AREA_ADDITION);
    }
    else{
        newQuadrant->setMaxX(840);
    }

    if((newCoordY+AREA_ADDITION) <= 1080){
        newQuadrant->setMaxY(newCoordY+AREA_ADDITION);
    }
    else{
        newQuadrant->setMaxY(1080);
    }

    // calculate the area of the quadrant
    int sideX = newQuadrant->getMaxX() - newQuadrant->getMinX();
    int sideY = newQuadrant->getMaxY() - newQuadrant->getMinY();
    int quadrantArea = sideX * sideY;

    // increase the total area
    actualArea += quadrantArea; 

    // asign the probability range of the new quadrant
    newQuadrant->setBottomRandom(0.0);
    newQuadrant->setTopRandom((quadrantArea + 0.0) / (actualArea + 0.0));

    // cout << "Bottom range: " << newQuadrant->getBottomRandom() << endl;
    // cout << "Top range: " << newQuadrant->getTopRandom() << endl;

    // add the pixel to the new quadrant
    newQuadrant->addPixel(newQuadrantPixel);

    // add the new quadrant
    pProbabilityTable.insert(pProbabilityTable.begin(), newQuadrant);

    // update the probability of all quadrants each 1%
    if((pixelsQuantity % 11664) == 0)
        updateProbability(pProbabilityTable);
}

/*___________________________________________________________________________________________________________
Function to update a quadrant
    We pick a pixel between (xMin, xMax) in X and (yMin, yMax) in Y of the current quadrant
    Expand the area if necessary, to a maximun if approximately 90*90 
Entries: image data, the probability table, grays, index of the table
*/
void otherQuadrantCases (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage, int indexTable){
    // cout << "===================================" << endl;
    // cout << "Funcion de otras areas" << endl;

    // Random process
    random_device rd;
    default_random_engine eng(rd());

    // the 2 randoms for the x and the y
    uniform_real_distribution<> distr(pProbabilityTable.at(indexTable)->getMinX(), pProbabilityTable.at(indexTable)->getMaxX() + 1); // random range
    uniform_real_distribution<> distr2(pProbabilityTable.at(indexTable)->getMinY(), pProbabilityTable.at(indexTable)->getMaxY() + 1); // random range

    int newCoordX = distr(eng);
    int newCoordY = distr2(eng);

    // cout << "Coordenadas del cuadrante: " << pProbabilityTable.at(indexTable)->getMinX() << ", " << pProbabilityTable.at(indexTable)->getMaxX() << \
    // ", " << pProbabilityTable.at(indexTable)->getMinY() << ", " << pProbabilityTable.at(indexTable)->getMaxY() << endl;
    // cout << "Coordenadas random: " << newCoordX << ", " << newCoordY << endl;

    // increase the generated pixels
    pixelsQuantity++;

    // create the new pixel
    Pixel* newQuadrantPixel = new Pixel();
    newQuadrantPixel->setCoordinateX(newCoordX);
    newQuadrantPixel->setCoordinateY(newCoordY);

    // asign the grey color
    int red, green, blue;
    const size_t RGB = 3;
    size_t index;

    index = RGB * (newQuadrantPixel->getCoordinateY() * 1080 + newQuadrantPixel->getCoordinateX());

    red = pImageFile[index + 0];
    green = pImageFile[index + 1];
    blue = pImageFile[index + 2];

    // cout << "Colores: " << red << ", " << green << ", " << blue << endl;

    newQuadrantPixel->setRGBColor(red,green,blue);
    newQuadrantPixel->setGrey(red, green, blue, pGreyInImage);

    // save the last value of the quadrant size
    int beforeSideX = pProbabilityTable.at(indexTable)->getMaxX() - pProbabilityTable.at(indexTable)->getMinX();
    int beforeSideY = pProbabilityTable.at(indexTable)->getMaxY() - pProbabilityTable.at(indexTable)->getMinY();
    int beforeArea = beforeSideX * beforeSideY;

    // Updating the dimentions of the quadrant
    int newMaxX = newCoordX + AREA_ADDITION ;
    int newMinX = newCoordX - AREA_ADDITION ;
    int newMaxY = newCoordY + AREA_ADDITION ;
    int newMinY = newCoordY - AREA_ADDITION ;

    // if the area of the quadrant increased
    bool increase = false;

    // we verify if the area of the quadrant exceeds the maximum (90 pixels)
    if(((pProbabilityTable.at(indexTable)->getMaxX() - pProbabilityTable.at(indexTable)->getMinX()) < 90)) { // max expand area is 90 pixels

        if(newMaxX > pProbabilityTable.at(indexTable)->getMaxX()){
            if(newMaxX > 840){
                pProbabilityTable.at(indexTable)->setMaxX(840);
            }
            else{
                pProbabilityTable.at(indexTable)->setMaxX(newMaxX);
            }  
            increase = true;  
        }

        if(newMinX < pProbabilityTable.at(indexTable)->getMinX()){
            if(newMinX < 240){
                pProbabilityTable.at(indexTable)->setMinX(240);
            }
            else{
                pProbabilityTable.at(indexTable)->setMinX(newMinX);
            }   
            increase = true;
        }
    }

    // we verify if the area of the quadrant exceeds the maximum
    if(((pProbabilityTable.at(indexTable)->getMaxY() - pProbabilityTable.at(indexTable)->getMinY()) < 90)) {

        if(newMaxY > pProbabilityTable.at(indexTable)->getMaxY()){
            if(newMaxY > 1080){
                pProbabilityTable.at(indexTable)->setMaxY(1080);
            }
            else{
                pProbabilityTable.at(indexTable)->setMaxY(newMaxY);
            }
            increase = true;
        }

        if(newMinY < pProbabilityTable.at(indexTable)->getMinY()){
            if(newMinY < 0){
                pProbabilityTable.at(indexTable)->setMinY(0);
            }
            else{
                pProbabilityTable.at(indexTable)->setMinY(newMinY);
            }    
            increase = true;
        }
    }

    // the area after the updates
    int afterArea = (pProbabilityTable.at(indexTable)->getMaxX() - pProbabilityTable.at(indexTable)->getMinX()) * \
                    (pProbabilityTable.at(indexTable)->getMaxY() - pProbabilityTable.at(indexTable)->getMinY());

    // calculate the difference of the areas
    int areaDifference = afterArea - beforeArea;
    // cout << "La diferencia del area es: " << areaDifference << endl;

    // update the total area
    actualArea += areaDifference;
  
    // cout << "Coordenadas del cuadrante: " << pProbabilityTable.at(indexTable)->getMinX() << ", " << pProbabilityTable.at(indexTable)->getMaxX() << \
    // ", " << pProbabilityTable.at(indexTable)->getMinY() << ", " << pProbabilityTable.at(indexTable)->getMaxY() << endl;

    // add the pixel to the new quadrant
    pProbabilityTable.at(indexTable)->addPixel(newQuadrantPixel);

    // update the probability of all quadrants
    if(increase)
        updateProbability(pProbabilityTable);

    if((pixelsQuantity % 11664) == 0){
        updateProbability(pProbabilityTable);
    }
}

// structure to calculate the dominant grays
struct GrayColor {
    int type;
    int quantity;
};

// calculate the dominant gray of each area
void calculateDominantGray(Quadrant* &pQuadrant, vector<Grey> pGreyInImage){
    vector<GrayColor> grayDistr;

    // fill vector with the posiible grays
    for (int grayIndex = 1; grayIndex < 21; grayIndex++ ){
        GrayColor gray;
        gray.type = grayIndex;
        gray.quantity = 0;
        grayDistr.push_back(gray);
    }

    int typeGray;

    for(int pixelIndex = 0; pixelIndex < pQuadrant->getPixelsInQuadrant().size(); pixelIndex++){
        typeGray = pQuadrant->getPixelsInQuadrant().at(pixelIndex)->getGrey();
        grayDistr.at(typeGray-1).quantity ++;
    }

    int dominantGray = 0;
    int maxValue = 0;

    for(int vectorIndex = 0; vectorIndex < 20; vectorIndex ++){
        if(grayDistr.at(vectorIndex).quantity > maxValue){
            maxValue = grayDistr.at(vectorIndex).quantity;
            dominantGray = grayDistr.at(vectorIndex).type;
        }
    }

    pQuadrant->setGreyScale(dominantGray);

}

// delete the non dominant points
void deletePixels (Quadrant* &pQuadrant){
    int dominantGray = pQuadrant->getGreyInScale();

    for(int pixelIndex = 0; pixelIndex < pQuadrant->getPixelsInQuadrant().size(); pixelIndex++){

        if(pQuadrant->getPixelsInQuadrant().at(pixelIndex)->getGrey() != dominantGray){
            pQuadrant->deletePixel(pixelIndex);
            pixelIndex --;
        }
    }
}

// compare the number of pixels of two quadrants
bool sortByPixels(Quadrant* &pQuadrant1, Quadrant* &pQuadrant2){
    return pQuadrant1->getPixelsInQuadrant().size() > pQuadrant2->getPixelsInQuadrant().size();
}

// sort the table from most to least elements
void sortTable(vector<Quadrant*> &pProbabilityTable){
    sort(pProbabilityTable.begin(), pProbabilityTable.end(), sortByPixels);
}

// the desired percentage of quadrants is selected
void filterTable (vector<Quadrant*> &pProbabilityTable){
    int quadrantsQuantity = pProbabilityTable.size();
    int porcentageQuantity = abs(quadrantsQuantity * 0.4);

    for(int tableIndex = porcentageQuantity; tableIndex < pProbabilityTable.size(); tableIndex++){
        pProbabilityTable.erase(pProbabilityTable.begin() + tableIndex);
        tableIndex--;
    }
}

/*___________________________________________________________________________________________________________
Main function of the probabilistic
    Random numbers are generated to sample pixels depending on the probability
    of each quadrant. 
    Runs until the desired sampling porcentage is achieved
Entries: image data, the probability table, grays
*/
void probabilisticFunction (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage) {

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> distr(0, 1); // random range
    
    float randomNumber;

    for(int i = 0; i < 349920; i++){ // while loop while 25% has not been sampled
        randomNumber = distr(eng);

        int size = pProbabilityTable.size();

        for(int tablePosition = 0; tablePosition < size; tablePosition++){
            if( (randomNumber >= pProbabilityTable.at(tablePosition)->getBottomRandom()) && (randomNumber < pProbabilityTable.at(tablePosition)->getTopRandom()) ){
                if(tablePosition == pProbabilityTable.size() - 1){ // create a new quadrant
                    totalAreaCase(pImageFile, pProbabilityTable, pGreyInImage, tablePosition);
                }

                else{ // update a quadrant
                    otherQuadrantCases(pImageFile, pProbabilityTable, pGreyInImage, tablePosition);
                }
                break;
            }
        }

    }

    // the dominant gray is calculated and those that do not have that color are eliminated
    for (int tableIndex = 0; tableIndex < pProbabilityTable.size(); tableIndex++){
        calculateDominantGray(pProbabilityTable.at(tableIndex), pGreyInImage);
        deletePixels(pProbabilityTable.at(tableIndex));
    }

    // sort the table and filter
    sortTable(pProbabilityTable);
    filterTable(pProbabilityTable);
}

#endif