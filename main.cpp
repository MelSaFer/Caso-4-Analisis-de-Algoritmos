//https://github.com/nothings/stb  --> link to the repositorie to download the stb libraries
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
    const char* filename = "images/rostro1.jpg";
    unsigned char *image = stbi_load(filename, &width, &height, &channels,0);

    //Size of the image
    size_t imageSize = width*height*channels;

    //Verify if the image exists
    if(image == NULL){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    //Creates the grays in the range we defined
    vector<Grey> greyInImage = greysInit();
    
    //Prueba de manejo de grises
    float p = RGBtoGreyScale(155, 255, 255);
    classifyGrey(p, greyInImage);

        //  for(int i = 0; i < 20; i++){
    //      greyInImage.at(i).toString();
    //  }

    //We create the administrador of quadrants
    // QuadrantAdmin* theAdmin = new QuadrantAdmin();
    vector<Quadrant*> probabilityTable;
    Quadrant* newQuadrant = new Quadrant();
    newQuadrant->setBottomRandom(0);
    newQuadrant->setTopRandom(1);
    newQuadrant->setMinX(240);
    newQuadrant->setMinY(0);
    newQuadrant->setMaxX(840);
    newQuadrant->setMaxY(1080);
    newQuadrant->setProbability();

    newQuadrant->toString();

    probabilityTable.push_back(newQuadrant);

    probabilisticFunction(image, probabilityTable, greyInImage);

    // ------------------------------------------------------------------------------
    // GENETIC
    // ------------------------------------------------------------------------------

    GeneticBase genetic;

    vector<cromodistribution*> geneticDistribution;

    
    srand(time(NULL));

    int totalPoints = 0;

    for(int probabiltyIndex = 0; probabiltyIndex < probabilityTable.size(); probabiltyIndex++){
        totalPoints += probabilityTable.at(probabiltyIndex)->getPixelsInQuadrant().size();
    }
    cromodistribution* cromoRow;

    cout << "Puntos totales: " << totalPoints << endl;
    int lastValue = 0;

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

    for (int i = 0; i < geneticDistribution.size(); i ++){
        std :: cout << "Indice: " << i << ", size: " << geneticDistribution.at(i)->size << ", shape: " <<\
        geneticDistribution.at(i)->shape << ", pixeles: " << geneticDistribution.at(i)->quantityOfPixels <<\
        ", TPixeles: " << geneticDistribution.at(i)->totalPopulation << ", probability: " << \
        float(geneticDistribution.at(i)->probability) << ", minValue: " << geneticDistribution.at(i)->minCromoValue << ", maxValue: " << geneticDistribution.at(i)->maxCromoValue << endl << endl;
    }

    int population = 300;
    genetic.initPopulation(population, geneticDistribution);
    genetic.produceGenerations(6, 400, geneticDistribution);


    return 0;
}





// #include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include "Classes/Quadrant.h"
// #include "Classes/Pixel.h"
// #include "Classes/QuadrantAdministrador.h"
// #include "Probabilistic.h"
// #include "Classes/Greys.h"
// #include "socketWin.h"

// using namespace std;


// int main (){
//     //Values we are going to use for reading the image

//     int width, height, channels;

//     //Image we are going to use
//     const char* filename = "images/rostro1.jpg";
//     unsigned char *image = stbi_load(filename, &width, &height, &channels,0);

//     //Size of the image
//     size_t imageSize = width*height*channels;

//     //Verify if the image exists
//     if(image == NULL){
//         cout << "Error al abrir el archivo" << endl;
//         return 1;
//     }

//     //Creates the grays in the range we defined
//     vector<Grey> greyInImage = greysInit();
    
//     //Prueba de manejo de grises
//     float p = RGBtoGreyScale(155, 255, 255);
//     classifyGrey(p, greyInImage);

//     //  for(int i = 0; i < 20; i++){
//     //      greyInImage.at(i).toString();
//     //  }

//     //We create the administrador of quadrants
//     // QuadrantAdmin* theAdmin = new QuadrantAdmin();
//     vector<Quadrant*> probabilityTable;
//     Quadrant* newQuadrant = new Quadrant();
//     newQuadrant->setBottomRandom(0);
//     newQuadrant->setTopRandom(1);
//     newQuadrant->setMinX(240);
//     newQuadrant->setMinY(0);
//     newQuadrant->setMaxX(840);
//     newQuadrant->setMaxY(1080);
//     newQuadrant->setProbability();

//     newQuadrant->toString();

//     probabilityTable.push_back(newQuadrant);

//     probabilisticFunction(image, probabilityTable, greyInImage);

//     for(int i = 0; i < probabilityTable.size(); i++){
//         // probabilityTable.at(i)->toString();
//     }

//     cout << "===================================================" << endl;
//     cout << "Cantidad de cuadrantes: " << probabilityTable.size() << endl;

//     long double prueba = 400.0/1166400.0;
//     // cout << "Cantidad de cuadrantes despues del Prob: " << theAdmin->getQuadrantsInImage().size() << endl;
//     cout << (prueba) << endl;
//     // printf("%i", prueba);

//     cout << "====================================================================================================" << endl;

//     // socketclient client;

//     // client.init();

//     // client.clear();

//     // client.paintLine(100, 255, 176, 255, 100, 100, 250, 600);
//     // client.paintDot(200, 0, 15, 200, 500, 600, 15);
//     // client.paintDot(220, 150, 15, 200, 600, 600, 20);

//     // client.closeConnection();


//     // for (int i = 0; i < theAdmin->getQuadrantsInImage().size(); i++){
//     //     cout << "----------------------------" << endl;
//     //     cout << "Cuadrante: " << i << endl;
//     //     cout << "Area: " << theAdmin->getQuadrantsInImage().at(i)->getMinX() << ", " << theAdmin->getQuadrantsInImage().at(i)->getMinY();
//     //     cout << "/ " << theAdmin->getQuadrantsInImage().at(i)->getMaxX() << ", " << theAdmin->getQuadrantsInImage().at(i)->getMaxY() << endl;
//     //     cout << "Random min: " << theAdmin->getQuadrantsInImage().at(i)->getBottomRandom() << ", Random max: " << theAdmin->getQuadrantsInImage().at(i)->getTopRandom() << endl;
//     //     cout << "Puntos: " << endl;
        

//     //     for (int j = 0; j < theAdmin->getQuadrantsInImage().at(i)->getPixelsInQuadrant().size(); j++){
//     //         cout << "\t" << theAdmin->getQuadrantsInImage().at(i)->getPixelsInQuadrant().at(j)->getCoordinateX();
//     //         cout << ", " << theAdmin->getQuadrantsInImage().at(i)->getPixelsInQuadrant().at(j)->getCoordinateY() << endl;
//     //     }
//     // }



//     // Pixel* p1 = new Pixel();
//     // Pixel* p2 = new Pixel();
//     // Pixel* p3 = new Pixel();
//     // Pixel* p4 = new Pixel();
//     // Pixel* p5 = new Pixel();

//     // p1->setCoordinates(20,20);
//     // p2->setCoordinates(39,39);
//     // p3->setCoordinates(200,14);

//     // theAdmin->addQuadrant(p1);
//     // theAdmin->addQuadrant(p2);
//     // theAdmin->addQuadrant(p3);



//     // cout <<"--------------------------------------" << endl;
//     // cout <<"Lista" << endl;
//     // for(int i = 0 ; i < theAdmin->getQuadrantsInImage().size(); i++){
//     //     cout <<"--------------------------------------" << endl; 
//     //     theAdmin->getQuadrantsInImage().at(i)->toString();
//     // }

    

//     //cout<<"Width of the image: "<<width<<endl;
//     //cout<<"Height of the image: "<<height<<endl;
//     //cout<<"Number of channels of the image: "<<channels<<endl;
//     //cout<<endl;

//     //recorrer los primeros 10 pixeles de la imagen

//     // for(unsigned char *p = image;p!=image + 30; p+=channels){
//     //   cout<< *p+0<<" "<<*p+1<<" "<<*p +2<<endl;
//     // }

// //   //Retornar valores RGB de un pixel en especifico

// //     const size_t RGB = 3;
// //     int xPosition = 500, yPosition = 400;
// //     size_t index = RGB * (yPosition * width + xPosition);
// //     cout << "RGB pixel @ (x=3, y=80): " 
// //           << static_cast<int>(image[index + 0]) << " "  //red value
// //           << static_cast<int>(image[index + 1]) << " "  //green value
// //           << static_cast<int>(image[index + 2]) << " "<<endl; //blue value

// //     int red = image[index + 0];
// //     cout << "Red: " << red << endl;

// //     //Limpiar 

//     stbi_image_free(image);

// 	// cout << "Creando ob" << endl;
	

//     //Deletes
//     // delete theAdmin;
//     // delete p1;
//     // delete p2;
//     // delete p3;
//     // delete p4;
//     // delete p5;

//     return 0;
// }