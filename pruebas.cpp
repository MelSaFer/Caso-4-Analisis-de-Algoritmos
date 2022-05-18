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
#include <iostream>
#include "Classes/Quadrant.h"
#include "Classes/Pixel.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


int main (){ 
    Quadrant* q = new Quadrant();

    //Values we are going to use for reading the image
    int width, height, channels;
    
    //Load the image
    unsigned char *image = stbi_load("images/prueba.jpg", &width, &height, &channels,0);
    size_t imageSize = width*height*channels;

    //Pixel* p = new Pixel();
    q->addPixel(10, 21);

    //Clean memory
    delete q;
    stbi_image_free(image);
    return 0;
}