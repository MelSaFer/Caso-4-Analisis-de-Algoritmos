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
    unsigned char *image = stbi_load("images/rostro1.jpg", &width, &height, &channels,0);
    size_t imageSize = width*height*channels;

    //Pixel* p = new Pixel();
    const size_t RGB = 3;
    int xPosition = 3, yPosition = 80;
    size_t index = RGB * (yPosition * width + xPosition);
    cout <<  " 1" << endl;
    int red = image[index + 0];  //red value
    int green = image[index + 1]; //green value
    int blue = image[index + 2]; //blue value
    //cout << red << " " << green << " " << blue << endl;
    q->addPixel(xPosition, yPosition, red, green, blue);

    //Clean memory
    delete q;
    stbi_image_free(image);
    return 0;
}