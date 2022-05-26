#ifndef PROBABILISTIC
#define PROBABILISTIC

// LIBRARIES
#include <iostream>
#include <random>
#include "Classes/Greys.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "Classes/Pixel.h"

using namespace std;

#define MAX_SAMPLING_PORCENTAGE 0.25
// #define TOTAL_PIXELS_IMAGE 1166400
// #define TOTAL_PIXELS_IMAGE 648000
#define TOTAL_PIXELS_IMAGE 648000
#define SIDE_LENGHT 1080.0
#define WIDTH_LENGHT 600.0
#define EXPAND_RANGES 30.0
#define AREA_ADDITION 15
int pixelsQuantity = 0;



void updateProbability (vector<Quadrant*> &pProbabilityTable){

    int indexTable = pProbabilityTable.size();
    int largo, ancho, area;
    float probability;
    float lastPorcentage = 0.0;

    for(int pRowPosition = 0; pRowPosition < indexTable; pRowPosition++){
        if(pRowPosition != indexTable - 1){
            largo = pProbabilityTable.at(pRowPosition)->getMaxX() - pProbabilityTable.at(pRowPosition)->getMinX();
            ancho = pProbabilityTable.at(pRowPosition)->getMaxY() - pProbabilityTable.at(pRowPosition)->getMinY();
            cout << pProbabilityTable.at(pRowPosition)->getMinX() << ", " << pProbabilityTable.at(pRowPosition)->getMaxX() << endl;
            cout << pProbabilityTable.at(pRowPosition)->getMinY() << ", " << pProbabilityTable.at(pRowPosition)->getMaxY() << endl;
            cout << "Largo: " << largo << ", Ancho: " << ancho << endl;
            area = largo * ancho;
            probability = (area + 0.0) / (SIDE_LENGHT*WIDTH_LENGHT);

            pProbabilityTable.at(pRowPosition)->setBottomRandom(lastPorcentage);
            pProbabilityTable.at(pRowPosition)->setTopRandom(lastPorcentage + probability);
            lastPorcentage += probability;
        }

        else{
            pProbabilityTable.at(pRowPosition)->setBottomRandom(lastPorcentage);
        }     
    }
}

void totalAreaCase (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage, int indexTable){
    cout << "===================================" << endl;
    cout << "Funcion del area grande" << endl;
    random_device rd;
    default_random_engine eng(rd());

    // the 2 randoms for the x and the y
    uniform_real_distribution<> distr(pProbabilityTable.at(indexTable)->getMinX(), pProbabilityTable.at(indexTable)->getMaxX() + 1); // random range
    uniform_real_distribution<> distr2(pProbabilityTable.at(indexTable)->getMinY(), pProbabilityTable.at(indexTable)->getMaxY() + 1); // random range

    int newCoordX = distr(eng);
    int newCoordY = distr2(eng);

    cout << "Coordenadas random: " << newCoordX << ", " << newCoordY << endl;

    pixelsQuantity++;

    Pixel* newQuadrantPixel = new Pixel();
    newQuadrantPixel->setCoordinateX(newCoordX);
    newQuadrantPixel->setCoordinateY(newCoordY);

    // create the new quadrant
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
    
    
    
    newQuadrant->setBottomRandom(0.0);
    newQuadrant->setTopRandom((EXPAND_RANGES * EXPAND_RANGES) / (SIDE_LENGHT*WIDTH_LENGHT));

    

    cout << "Bottom range: " << newQuadrant->getBottomRandom() << endl;
    cout << "Top range: " << newQuadrant->getTopRandom() << endl;

    // add the pixel to the new quadrant
    newQuadrant->addPixel(newQuadrantPixel);

    // add the new quadrant
    pProbabilityTable.insert(pProbabilityTable.begin(), newQuadrant);
    updateProbability(pProbabilityTable);

}

void otherQuadrantCases (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage, int indexTable){
    cout << "===================================" << endl;
    cout << "Funcion de otras areas" << endl;

    random_device rd;
    default_random_engine eng(rd());

    // the 2 randoms for the x and the y
    uniform_real_distribution<> distr(pProbabilityTable.at(indexTable)->getMinX(), pProbabilityTable.at(indexTable)->getMaxX() + 1); // random range
    uniform_real_distribution<> distr2(pProbabilityTable.at(indexTable)->getMinY(), pProbabilityTable.at(indexTable)->getMaxY() + 1); // random range

    int newCoordX = distr(eng);
    int newCoordY = distr2(eng);

    cout << "Coordenadas del cuadrante: " << pProbabilityTable.at(indexTable)->getMinX() << ", " << pProbabilityTable.at(indexTable)->getMaxX() << \
    ", " << pProbabilityTable.at(indexTable)->getMinY() << ", " << pProbabilityTable.at(indexTable)->getMaxY() << endl;
    cout << "Coordenadas random: " << newCoordX << ", " << newCoordY << endl;

    pixelsQuantity++;

    Pixel* newQuadrantPixel = new Pixel();
    newQuadrantPixel->setCoordinateX(newCoordX);
    newQuadrantPixel->setCoordinateY(newCoordY);

    //Updating the dimentions of the quadrant
    int newMaxX = newQuadrantPixel->getCoordinateX() + AREA_ADDITION ;
    int newMinX = newQuadrantPixel->getCoordinateX() - AREA_ADDITION ;
    int newMaxY = newQuadrantPixel->getCoordinateY() + AREA_ADDITION ;
    int newMinY = newQuadrantPixel->getCoordinateY() - AREA_ADDITION ;

    bool increase = false;

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
        if(newMinY < 240){
            pProbabilityTable.at(indexTable)->setMinX(240);
        }
        else{
            pProbabilityTable.at(indexTable)->setMinX(newMinY);
        }   
        increase = true;
    }

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

    cout << "Coordenadas del cuadrante: " << pProbabilityTable.at(indexTable)->getMinX() << ", " << pProbabilityTable.at(indexTable)->getMaxX() << \
    ", " << pProbabilityTable.at(indexTable)->getMinY() << pProbabilityTable.at(indexTable)->getMaxY() << endl;

    // add the pixel to the new quadrant
    pProbabilityTable.at(indexTable)->addPixel(newQuadrantPixel);

    if(increase)
        updateProbability(pProbabilityTable);
}





void probabilisticFunction (unsigned char* pImageFile, vector<Quadrant*> &pProbabilityTable, vector<Grey> pGreyInImage) {

    random_device rd;
    default_random_engine eng(rd());
    uniform_real_distribution<> distr(0, 1); // random range
    // srand(time(NULL));
    // num = 0 + (float)(rand()) / ((float)(RAND_MAX/(1 - 0)));
    
    float maxSamplingPixels = TOTAL_PIXELS_IMAGE * MAX_SAMPLING_PORCENTAGE;
    cout << "\nCantidad de pixeles [25p]: " << (float)maxSamplingPixels << endl;
    
    float randomNumber;

    float num;
    for(int i = 0; i < 1000; i++){ // while loop while 25% has not been sampled
        randomNumber = distr(eng);
        // cout << "-------------" << endl;
        cout << randomNumber << ", " << i << endl;
        // cout << i << ", " << num << endl;   

        int size = pProbabilityTable.size();
        for(int tablePosition = 0; tablePosition < size; tablePosition++){
            if( (randomNumber >= pProbabilityTable.at(tablePosition)->getBottomRandom()) && (randomNumber < pProbabilityTable.at(tablePosition)->getTopRandom()) ){
                if(tablePosition == pProbabilityTable.size() - 1){
                    totalAreaCase(pImageFile, pProbabilityTable, pGreyInImage, tablePosition);
                }

                else{
                    otherQuadrantCases(pImageFile, pProbabilityTable, pGreyInImage, tablePosition);
                }
                break;
            }
        }

    }

}

#endif