#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

#define CROMO_MAX_VALUE 65535 // 
#define NIBBLE_SIZE 16
#define MIN_GENOTYPE_SIZE_BY_PARENT 2 // 5
#include "point.h"

class individual {
    private: 
        // any important related info
        // decide the size of your nibble for your problem
        float fitnessValue;
        unsigned char cromosoma;
        point* pointInfo;

        //int XCoordinate;
        //int YCoordinate;
        //int color;
        

    public:
        individual(unsigned char pValue) {
            this->cromosoma = pValue;
        }

        unsigned char getCromosoma() {
            return this->cromosoma;
        }

        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }

        void setPointInfo(point* pNewPoint){
            this->pointInfo = pNewPoint;
        }

        point* getPointInfo(){
            return this->pointInfo;
        }
};


#endif