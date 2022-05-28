/*
Case 4
Instituto tecnologico de Costa Rica
Analisis de Algoritmos
Students:
        Melany Salas Fernandez
        Moises Solano Espinoza
*/

//-------------------------------------Libraries------------------------------

#include "socketWin.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Classes/Quadrant.h"
#include "Classes/Pixel.h"
#include "Classes/QuadrantAdministrador.h"
#include "Probabilistic.h"
#include "Classes/Greys.h"
#include "Classes/cromodistribution.h"
#include "geneticbase.h"
#include <cmath>
#include <algorithm>

int main(int argc, char const *argv[])
{
     //Values we are going to use for reading the image

    int width, height, channels;

    //Image we are going to use
    const char* filename = "images/rostro2.jpg";
    unsigned char *image = stbi_load(filename, &width, &height, &channels,0);

    //Size of the image
    size_t imageSize = width*height*channels;

    //Verify if the image exists
    if(image == NULL){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    // ------------------------------------------------------------------------------
    // PROBABILITY
    // ------------------------------------------------------------------------------

    //Creates the grays in the range we defined
    vector<Grey> greyInImage = greysInit();

    // We create the probability table
    // and set the first quadrant
    vector<Quadrant*> probabilityTable;
    Quadrant* newQuadrant = new Quadrant();
    newQuadrant->setBottomRandom(0);
    newQuadrant->setTopRandom(1);
    newQuadrant->setMinX(240);
    newQuadrant->setMinY(0);
    newQuadrant->setMaxX(840);
    newQuadrant->setMaxY(1080);
    newQuadrant->setProbability();

    // newQuadrant->toString();

    probabilityTable.push_back(newQuadrant);

    probabilisticFunction(image, probabilityTable, greyInImage);

    // ------------------------------------------------------------------------------
    // GENETIC
    // ------------------------------------------------------------------------------

    GeneticBase genetic;

    vector<cromodistribution*> geneticDistribution; // chromosome distribution

    srand(time(NULL));

    int totalPoints = 0; // variable that contains the total of pixels

    for(int probabiltyIndex = 0; probabiltyIndex < probabilityTable.size(); probabiltyIndex++){
        totalPoints += probabilityTable.at(probabiltyIndex)->getPixelsInQuadrant().size();
    }

    cromodistribution* cromoRow; // each row of the chromosomatic table

    // cout << "Puntos totales: " << totalPoints << endl;

    int lastValue = 0; // the last chromosomatic value

    // for to create the chromosomatic table
    for(int tableIndex = 0; tableIndex < probabilityTable.size(); tableIndex++){
        cromoRow = new cromodistribution();
        cromoRow->size = rand()%3;
        cromoRow->shape = rand()%2;
        cromoRow->totalPopulation = totalPoints;
        cromoRow->quantityOfPixels = probabilityTable.at(tableIndex)->getPixelsInQuadrant().size();
        cromoRow->probability = (cromoRow->quantityOfPixels + 0.0) / totalPoints;
        cromoRow->minCromoValue = lastValue;
        lastValue += round(65536 * cromoRow->probability);
        cromoRow->quadrant = probabilityTable.at(tableIndex);

        if(tableIndex == (probabilityTable.size() - 1)){
            cromoRow->maxCromoValue = 65536 - 1;
            geneticDistribution.push_back(cromoRow);
            break;
        }
        else
            cromoRow->maxCromoValue = lastValue;

        geneticDistribution.push_back(cromoRow);
    } 

    // for (int i = 0; i < geneticDistribution.size(); i ++){
    //     std :: cout << "Indice: " << i << ", size: " << geneticDistribution.at(i)->size << ", shape: " <<\
    //     geneticDistribution.at(i)->shape << ", pixeles: " << geneticDistribution.at(i)->quantityOfPixels <<\
    //     ", TPixeles: " << geneticDistribution.at(i)->totalPopulation << ", probability: " << \
    //     float(geneticDistribution.at(i)->probability) << ", minValue: " << geneticDistribution.at(i)->minCromoValue << ", maxValue: " << geneticDistribution.at(i)->maxCromoValue << endl << endl;
    // }

    // initial population
    int population = 150;
    int targetGenerations = 5;
    int ChildrensPerGenerations = 350;

    genetic.initPopulation(population, geneticDistribution, greyInImage);
    genetic.produceGenerations(targetGenerations, ChildrensPerGenerations, geneticDistribution, greyInImage);

    return 0;
}