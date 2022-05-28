#ifndef _GENETICBASE_
#define _GENETICBASE_ 1
#include <vector>
#include "Classes/cromodistribution.h"
#include "Classes/individual.h"
#include <algorithm>
//#include "Classes/point.h"

int cromoMaxValue = 65535;

#define MAXIMUM_DISTANCE 35

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

        void evaluateFitness() {
            cout << "Evaluate fitness" << endl;
            fitnessPopulation->clear();
            unfitnessPopulation->clear();

            for(int i=0;i < population->size(); i++) {
                // cout << i <<  "''''''" << endl;
               population->at(i)->setFitnessValue(fitness(population->at(i)));

                // if (population->at(i)->getFitnessValue()> 50) {  // fitness criteria of selection never will be an absolute value always is relative to the population
                //     fitnessPopulation->push_back(population->at(i));
                // } else {
                //     unfitnessPopulation->push_back(population->at(i));
                // }
            }

            // sort(population->begin(), population->end(), sortByFitness);

            // // Empezamos copiando los taxistas en un vector
            // std::vector<individual*> horas(population->size());
            // std::copy(population->begin(), population->end(), horas.begin());

            // Ordenamos
            std::sort(population->begin(), population->end(),
            [](auto &a, auto &b){ return a->getFitnessValue() > b->getFitnessValue(); });

            int importantPixels = (int)(population->size() * 0.6);
            for(int i = 0; i < population->size(); i++){
                if(i < importantPixels){
                    fitnessPopulation->push_back(population->at(i));
                }
                else{
                    unfitnessPopulation->push_back(population->at(i));
                }
            }

            for(int i = 0; i < this->fitnessPopulation->size(); i++){
                cout << "Valor fit: " << this->fitnessPopulation->at(i)->getFitnessValue() << endl;
            }
        }

        int evaluateDistance( int pCoordX1, int pCoordY1, int pCoordX2, int pCoordY2){
            //raiz((x2-x1)^2 + (y2-y1)^2)
            int distance = sqrt(pow((pCoordX2-pCoordX1), 2) + pow((pCoordY2-pCoordY1), 2));

            return distance;
        }

        int fitness(individual *pIndividual) {
            //We use the "Fitness family" tecnique, the fitness value is assign acording tho te cuantity of
            // neighbours
            int distance;
            int fitnessValue=0;
            for(int currentIndividual = 0; currentIndividual < this->population->size(); currentIndividual++){
                // cout << "fitness" << endl;
                distance = evaluateDistance(pIndividual->getCoordX(), pIndividual->getCoordY(), this->population->at(currentIndividual)->getCoordX(), this->population->at(currentIndividual)->getCoordY());
                if(distance <= MAXIMUM_DISTANCE){//Evaluate if a pixel is a neighbour
                    fitnessValue++;
                } 
            }

            return fitnessValue;
        }

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

        individual* cross(individual *pParent_a, individual *pParent_b) {
            // this operation will depends on: nibble size, fixed o variable point

            int cut_position = (rand() % (NIBBLE_SIZE-MIN_GENOTYPE_SIZE_BY_PARENT*2)) + MIN_GENOTYPE_SIZE_BY_PARENT;

            unsigned char mask_a = cromoMaxValue - 1; // 255 -> 11111111
            mask_a <<= cut_position;

            unsigned char mask_b = cromoMaxValue - 1; // 255 -> 11111111
            mask_b >>= NIBBLE_SIZE - cut_position;

            unsigned char kid = (pParent_a->getChromosome() & mask_a) | (pParent_b->getChromosome() & mask_b);

            //----------Mutacion-----------
            if(rand() % (100)<7){
                unsigned short pos = rand() % (NIBBLE_SIZE);
                unsigned short bit = (kid>>pos);
                bit = (bit & 1)^1;
                unsigned short clearBit= ~(1<<pos);
                unsigned short mask= kid & clearBit;
                kid= mask | (bit<<pos);
            }
            //-----------------------------
            individual *children = new individual((pParent_a->getChromosome() & mask_a) | (pParent_b->getChromosome() & mask_b));
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

        cromodistribution* assignCromosomaticDist(int pCurrentDist, vector<cromodistribution*> pGeneticDistribution){
            cromodistribution* selectedCromoDist = new cromodistribution();
            for(int currentRow = 0; currentRow < pGeneticDistribution.size(); currentRow++){
                if((pCurrentDist < pGeneticDistribution.at(currentRow)->maxCromoValue) && (pCurrentDist >= pGeneticDistribution.at(currentRow)->minCromoValue)){
                    //cout << "Este es mi croma :" << pCurrentDist << "\nmin: " << pGeneticDistribution.at(currentRow)->minCromoValue\
                    //<< " max: " << pGeneticDistribution.at(currentRow)->maxCromoValue << endl;
                    selectedCromoDist = pGeneticDistribution.at(currentRow);
                    return selectedCromoDist;
                }
            }
            return selectedCromoDist;
        }

        void initPopulation(int pAmountOfIndividuals, vector<cromodistribution*> pGeneticDistribution) {
            population->clear();

            //For the random of cromodist
            random_device rd;
            default_random_engine eng(rd());
            uniform_real_distribution<> distr(0, cromoMaxValue); // random range

            // javaSocket.init(); //  ver si nos sirve antes o despues del for

            // javaSocket.paintLine(100, 255, 176, 255, 100, 100, 250, 600);
            // javaSocket.paintDot(200, 0, 15, 200, 500, 600, 15);
            // javaSocket.paintDot(220, 150, 15, 200, 600, 600, 20);

            int currentDistribution;
            int coordX;
            int coordY;
            cout << "AQUIII2-------------------------" <<endl;

            for(int i = 0; i < pAmountOfIndividuals; i++) {
                cout << "Creando individuo " << i << endl;
                currentDistribution = distr(eng);
                cromodistribution* selectedCromoDist = new cromodistribution();
                //cout << currentDistribution << endl;
                selectedCromoDist = assignCromosomaticDist(currentDistribution, pGeneticDistribution);
                //Random of the new point coord
                uniform_real_distribution<> distrPointX(selectedCromoDist->quadrant->getMinX(), selectedCromoDist->quadrant->getMaxX()); 
                uniform_real_distribution<> distrPointY(selectedCromoDist->quadrant->getMinY(), selectedCromoDist->quadrant->getMaxY()); 

                coordX = distrPointX(eng);
                coordY = distrPointY(eng);

                individual* newInd = new individual((unsigned char) currentDistribution, coordX, coordY, \
                            selectedCromoDist->shape, selectedCromoDist->size, selectedCromoDist);
                
                this->population->push_back(newInd);

            }
            cout << "AQUIII-------------------------" <<endl;
            for(int i = 0; i < this->population->size(); i++){
                cout << "Individuo # " << i << endl;
                // cout << "Cromo: " << this->population->at(i)->getChromosome() << endl;
                cout << "X: " << this->population->at(i)->getCoordX() << endl;
                cout << "Y: " << this->population->at(i)->getCoordY() << endl;
                cout << "Gray: " << this->population->at(i)->getGray()<< endl;
                cout << "Shape: " << this->population->at(i)->getShape() << endl;
                cout << "Size: " << this->population->at(i)->getSize() << endl;
            }
            // javaSocket.closeConnection();
        }
        
        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations) {
            for(int i=0; i<ptargetGenerations; i++) {
                evaluateFitness();
                reproduce(pChildrensPerGenerations);
            }
        }

        vector<individual*> getPopulation() {
            return *this->population;
        }
};

#endif