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
#include "Classes/QuadrantAdministrador.h"

using namespace std;

#define MAX_SAMPLING_PORCENTAGE 0.4
#define TOTAL_PIXELS_IMAGE 1166400
#define SIDE_LENGHT 1080

void probabilisticFunction (unsigned char* pImageFile, QuadrantAdmin &pProbabilityTable, vector<Grey> pGreyInImage) {
    
    float maxSamplingPixels = TOTAL_PIXELS_IMAGE * MAX_SAMPLING_PORCENTAGE;
    cout << "\nCantidad de pixeles [40p]: " << (float)maxSamplingPixels << endl;

    random_device rd;
    default_random_engine eng(rd());
    // uniform_real_distribution<> distr(0, 1); // random range
    
    // 
    int x = 1;
    float f;
    int z;
    for(int i = 0; i < 10; i++){
        uniform_real_distribution<> distr(0, 1); // random range
        uniform_real_distribution<> distr2(5, 11); // random range
        f = distr(eng);
        z = distr2(eng);
        cout << f << ", " << z << endl;
        x += 10;

        pProbabilityTable.addQuadrant(f, pImageFile, pGreyInImage);

        
    }

}

#endif