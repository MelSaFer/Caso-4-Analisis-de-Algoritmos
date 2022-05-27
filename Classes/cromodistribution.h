#ifndef _CROMODISTRIBUTION_
#define _CROMODISTRIBUTION_ 1

#include "Quadrant.h"
using namespace std;

#define MIN_X_QUADRANT 240
#define INCREASE_OF_AREAS 90


struct cromodistribution {
    float minProbability;           //Min probability
    float maxProbability;           //Max probability
    int quantityOfPixels;           //Total of pixels
    Quadrant* quadrant;             //The area- has max Coodinates, grey scale, rgb, probability, top and
                                    //      bottom random and pixels in quadrant
};

#endif