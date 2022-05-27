#ifndef _CROMODISTRIBUTION_
#define _CROMODISTRIBUTION_ 1

#include "Quadrant.h"
// using namespace std;

#define MIN_X_QUADRANT 240
#define INCREASE_OF_AREAS 90


// struct cromodistribution {
//     float minProbability;           //Min probability
//     float maxProbability;           //Max probability
//     int quantityOfPixels;           //Total of pixels
//     Quadrant* quadrant;             //The area- has max Coodinates, grey scale, rgb, probability, top and
//                                     //      bottom random and pixels in quadrant
// };

struct cromodistribution {
    // int minXValue;                  //Min X value for the quadrant
    // int maxXValue;                  //Max X value for the quadrant
    // int minYValue;                  //Min Y value for the quadrant
    // int maxYValue;                  //Max Y value for the quadrant
    // int grey;                       //One grey between 1 and 20
    int size;                       //if its 1 is small, 2 is for medium and 3 for large
    int shape;   
    float probability;                   //Line or circle
    int minCromoValue;
    int maxCromoValue;
    int quantityOfPixels;           //Total of pixels
    int totalPopulation;            //Total population
    Quadrant* quadrant;
};

#endif