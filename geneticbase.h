#ifndef _GENETICBASE_
#define _GENETICBASE_ 1
#include <vector>
#include "Classes/cromodistribution.h"
#include "Classes/individual.h"
#include <algorithm>

int cromoMaxValue = 65536;

#define MAXIMUM_DISTANCE 45

//Sizes
#define SMALL 2
#define MEDIUM 9
#define LARGE 17

using namespace std;

class GeneticBase {
    private:
        vector<cromodistribution*> *representation;
        vector<individual*> *population;
        vector<individual*> *fitnessPopulation;
        vector<individual*> *unfitnessPopulation;
        int populationQuantity;
        int targetGenerations;
        socketclient javaSocket;

        // function that sends to evaluate the fitness of the population
        void evaluateFitness() {
            fitnessPopulation->clear();
            unfitnessPopulation->clear();

            // assign fitness value
            for(int i=0;i < population->size(); i++) {
               population->at(i)->setFitnessValue(fitness(population->at(i)));
            }

            // Sort
            std::sort(population->begin(), population->end(),
            [](auto &a, auto &b){ return a->getFitnessValue() > b->getFitnessValue(); });

            // the most fit are selected
            int importantPixels = (int)(population->size() * 0.6);
            for(int i = 0; i < population->size(); i++){
                if(i < importantPixels){
                    fitnessPopulation->push_back(population->at(i));
                }
                else{
                    unfitnessPopulation->push_back(population->at(i));
                }
            }
            // for(int i = 0; i < this->fitnessPopulation->size(); i++){
            //     cout << "Valor fit: " << this->fitnessPopulation->at(i)->getFitnessValue() << endl;
            // }
        }

        // Calculate the distance between two pixels
        int evaluateDistance( int pCoordX1, int pCoordY1, int pCoordX2, int pCoordY2){
            //sqrt((x2-x1)^2 + (y2-y1)^2)
            int distance = sqrt(pow((pCoordX2-pCoordX1), 2) + pow((pCoordY2-pCoordY1), 2));

            return distance;
        }

        // Calculate the fitness value of one individual
        int fitness(individual *pIndividual) {
            //We use the "Fitness family" tecnique, the fitness value is assign acording tho te cuantity of
            // neighbours
            int distance;
            int fitnessValue=0;

            // compare the distance of a point with all neighbors
            for(int currentIndividual = 0; currentIndividual < this->population->size(); currentIndividual++){
                distance = evaluateDistance(pIndividual->getCoordX(), pIndividual->getCoordY(), this->population->at(currentIndividual)->getCoordX(), this->population->at(currentIndividual)->getCoordY());
                
                if(distance <= MAXIMUM_DISTANCE){ //Evaluate if a pixel is a neighbour
                    fitnessValue++;
                } 
            }
            return fitnessValue;
        }

        // two parents have children
        void reproduce(int pAmountOfChildrens) {
            // previous population will be cleared, full saved, partial saved depending on the problem
            population->clear();

            for(int i=0; i<pAmountOfChildrens; i++) {
                // select any two fitness parents
                int parent_a_index = rand() % fitnessPopulation->size();
                individual* parent_a = fitnessPopulation->at(parent_a_index);

                int parent_b_index = rand() % fitnessPopulation->size();
                individual* parent_b = fitnessPopulation->at(parent_b_index);

                population->push_back(cross(parent_a, parent_b));
            }
        }

        // two parents cross their bits to have a child
        individual* cross(individual *pParent_a, individual *pParent_b) {
            // this operation will depends on: nibble size, fixed o variable point

            int cut_position = (rand() % (NIBBLE_SIZE-MIN_GENOTYPE_SIZE_BY_PARENT*2)) + MIN_GENOTYPE_SIZE_BY_PARENT;

            unsigned short mask_a = cromoMaxValue - 1; // 255 -> 11111111
            mask_a <<= cut_position;

            unsigned short mask_b = cromoMaxValue - 1; // 255 -> 11111111
            mask_b >>= NIBBLE_SIZE - cut_position;

            unsigned short kid = (pParent_a->getChromosome() & mask_a) | (pParent_b->getChromosome() & mask_b);

            // ------------------------------------------------------------------------------
            //                                  MUTATION
            //
            // we want to select a bit and depending on the probability it will be inverted
            // ------------------------------------------------------------------------------

            // the kid only has a 7% chance to mutate
            if(rand() % (100) < 7){

                // a bit is selected to be modified
                unsigned short bitPosition = rand() % (NIBBLE_SIZE);

                unsigned short bit = (kid>>bitPosition); // bit of the kid shift to the right, until out of range

                bit = (bit & 1)^1; // set all bits to 0
                
                // the 1 is put in the change position and all the bits are inverted in order to leave a 0 in the bit
                unsigned short auxiliarBit = ~(1<<bitPosition); // shift left a one in bit position

                unsigned short mask = kid & auxiliarBit;

                kid = mask | (bit<<bitPosition); // finally the selected bit is inverted
            }

            //-----------------------------
            individual *children = new individual(kid);
            return children;
        }

    public:
        GeneticBase() {
            this->population = new vector<individual*>();
            this->fitnessPopulation = new vector<individual*>();
            this->unfitnessPopulation = new vector<individual*>();
            this->representation = new vector<cromodistribution*>(); 
            this->populationQuantity = 0;
            this->targetGenerations = 20;
        }

        void addDistribution(cromodistribution* pDistribution) {
            representation->push_back(pDistribution);
        }

        // look in the table to wich chromosome a number belongs
        cromodistribution* assignCromosomaticDist(int pCurrentDist, vector<cromodistribution*> pGeneticDistribution){
            cromodistribution* selectedCromoDist = new cromodistribution();
            for(int currentRow = 0; currentRow < pGeneticDistribution.size(); currentRow++){
                if((pCurrentDist < pGeneticDistribution.at(currentRow)->maxCromoValue) && (pCurrentDist >= pGeneticDistribution.at(currentRow)->minCromoValue)){
                    selectedCromoDist = pGeneticDistribution.at(currentRow);
                    return selectedCromoDist;
                }
            }
            return selectedCromoDist;
        }

        // paint
        void paitingInJavaServer(individual* theIndividual, vector<Grey> pScaleGreys){
            int size = (theIndividual->getSize()+1);
            int length;

            if(size == 0){
                length = SMALL;
            }
            else if(size == 1){
                length = MEDIUM;
            }
            else{
                length = LARGE;
            }

            int grey = 0;

            for(int indexGrey = 0; indexGrey < pScaleGreys.size(); indexGrey++){
                if(theIndividual->getGray() == pScaleGreys.at(indexGrey).getIdentification()){
                    grey = pScaleGreys.at(indexGrey).getMinValue();
                }
            }
            //Evaluate if we are going to paint a circle or a line
            if(theIndividual->getShape() == 0){ // line
                int minCoordX = (theIndividual->getCoordX()) - (length);
                int maxCoordX = (theIndividual->getCoordX()) + (length);
                int minCoordY = (theIndividual->getCoordY()) - (length);
                int maxCoordY = (theIndividual->getCoordY()) + (length);

                int direction = rand() % 2;

                if(direction == 0){
                    javaSocket.paintLine(grey, grey, grey, 255, minCoordX, minCoordY, maxCoordX, maxCoordY);
                } else{
                    javaSocket.paintLine(grey, grey, grey, 255, minCoordX, maxCoordY, maxCoordX, minCoordY);
                }

            }else{ // point
                int coordX = (theIndividual->getCoordX());
                int coordY = (theIndividual->getCoordY());
                //int radius = ((length/2)*size)/2;
                javaSocket.paintDot(grey, grey, grey, 200, coordX,coordY, (size*2));
            }
            

        }

        void initPopulation(int pAmountOfIndividuals, vector<cromodistribution*> pGeneticDistribution, vector<Grey> pScaleGreys) {
            population->clear();
            // cout << "Tamano de population: " << population->size();

            //For the random of cromodist
            random_device rd;
            default_random_engine eng(rd());
            uniform_real_distribution<> distr(0, cromoMaxValue); // random range

            javaSocket.init();
            javaSocket.clear();

            int currentDistribution;
            int coordX;
            int coordY;

            for(int i = 0; i < pAmountOfIndividuals; i++) {
                currentDistribution = distr(eng);
                cromodistribution* selectedCromoDist = new cromodistribution();

                selectedCromoDist = assignCromosomaticDist(currentDistribution, pGeneticDistribution);
                //Random of the new point coord
                uniform_real_distribution<> distrPointX(selectedCromoDist->quadrant->getMinX(), selectedCromoDist->quadrant->getMaxX() + 1); 
                uniform_real_distribution<> distrPointY(selectedCromoDist->quadrant->getMinY(), selectedCromoDist->quadrant->getMaxY() + 1); 

                coordX = distrPointX(eng);
                coordY = distrPointY(eng);

                individual* newInd = new individual((unsigned short)currentDistribution, coordX, coordY, \
                            selectedCromoDist->shape, selectedCromoDist->size, selectedCromoDist);
                newInd->setGray(selectedCromoDist->quadrant->getGreyInScale());
                
                this->population->push_back(newInd);

            }
            for(int i = 0; i < this->population->size(); i++){
                paitingInJavaServer(this->population->at(i), pScaleGreys);
            }
            // javaSocket.closeConnection();
        }

        // updates the kids data depending on their chromosomatic value
        void chromosomesUpdate(vector<cromodistribution*> pGeneticDistribution){
            //For the random of cromodist
            random_device rd;
            default_random_engine eng(rd());
            uniform_real_distribution<> distr(0, cromoMaxValue + 1); // random range
            unsigned short currentDistribution;
            int coordX;
            int coordY;

            for (int familyIndex = 0; familyIndex < population->size(); familyIndex++){
                currentDistribution = population->at(familyIndex)->getChromosome();
                cromodistribution* selectedCromoDist = new cromodistribution();

                selectedCromoDist = assignCromosomaticDist(currentDistribution, pGeneticDistribution);

                //Random of the new point coord
                uniform_real_distribution<> distrPointX(selectedCromoDist->quadrant->getMinX(), selectedCromoDist->quadrant->getMaxX() + 1); 
                uniform_real_distribution<> distrPointY(selectedCromoDist->quadrant->getMinY(), selectedCromoDist->quadrant->getMaxY() + 1); 

                coordX = distrPointX(eng);
                coordY = distrPointY(eng);

                population->at(familyIndex)->setCoordX(coordX);
                population->at(familyIndex)->setCoordY(coordY);
                population->at(familyIndex)->setShape(selectedCromoDist->shape);
                population->at(familyIndex)->setSize(selectedCromoDist->size);
                population->at(familyIndex)->setChromoDist(selectedCromoDist);
                population->at(familyIndex)->setGray(selectedCromoDist->quadrant->getGreyInScale());
                
            }  
            // this->population->push_back(newInd);
        }
        

        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations, vector<cromodistribution*> pGeneticDistribution, vector<Grey> pScaleGreys) {
            for(int i=0; i<ptargetGenerations; i++) {
                evaluateFitness();
                reproduce(pChildrensPerGenerations);
                chromosomesUpdate(pGeneticDistribution);

                javaSocket.clear();

                for(int individualIndex = 0; individualIndex < this->population->size(); individualIndex++){
                    paitingInJavaServer(this->population->at(individualIndex), pScaleGreys);
                }
            }
            javaSocket.closeConnection();
        }

        vector<individual*> getPopulation() {
            return *this->population;
        }
};

#endif