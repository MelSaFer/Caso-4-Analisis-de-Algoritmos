#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

//#define CROMO_MAX_VALUE 1 // 
#define NIBBLE_SIZE 16
#define MIN_GENOTYPE_SIZE_BY_PARENT 2 // 5
#include "point.h"
#include "Quadrant.h"
#include "cromodistribution.h"

class individual {
    private: 
        // any important related info
        // decide the size of your nibble for your problem
        float fitnessValue;
        unsigned short chromosome;
        int coordX;
        int coordY;
        int gray;
        int shape;
        int size;
        cromodistribution* chromosomaticDistr;    

    public:
        individual(unsigned short pValue) {
            this->chromosome = pValue;
        }

        individual(unsigned short pCromosoma, int pCoordX, int pCoordY, int pShape, int pSize, cromodistribution* chromoDist){
            this->chromosome = pCromosoma;
            this->coordX = pCoordX;
            this->coordY = pCoordY;
            this->shape = pShape;
            this->size = pSize;
            this->chromosomaticDistr = chromoDist;
        }

        void setCoordX (int pCoordX){
            this->coordX = pCoordX;
        }

        int getCoordX (){
            return this->coordX;
        }

        void setCoordY (int pCoordY){
            this->coordY = pCoordY;
        }

        int getCoordY (){
            return this->coordY;
        }

        unsigned short getChromosome() {
            return this->chromosome;
        }

        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }

        void setGray(int pGray){
            this->gray = pGray;
        }

        int getGray(){
            return this->gray;
        }

        void setSize(int pSize){
            this->size = pSize;
        }

        int getSize(){
            return this->size;
        }

        void setShape(int pShape){
            this->shape = pShape;
        }

        int getShape(){
            return this->shape;
        }

        void setChromoDist(cromodistribution* pChromoDist){
            this->chromosomaticDistr = pChromoDist;
        }

        cromodistribution* getCromoDist(){
            return this->chromosomaticDistr;
        }

        // void setPointInfo(point* pNewPoint){
        //     this->pointInfo = pNewPoint;
        // }

        // point* getPointInfo(){
        //     return this->pointInfo;
        // }
};


#endif