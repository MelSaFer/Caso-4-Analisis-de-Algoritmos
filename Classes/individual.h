#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

#define CROMO_MAX_VALUE 32
#define NIBBLE_SIZE 16
#define MIN_GENOTYPE_SIZE_BY_PARENT 2

class individual {
    private: 
        // any important related info
        // decide the size of your nibble for your problem
        float fitnessValue;
        unsigned char cromosoma;
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
};


#endif