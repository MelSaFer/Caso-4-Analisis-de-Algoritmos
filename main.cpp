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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Classes/Quadrant.h"
#include "Classes/Pixel.h"
#include "Classes/QuadrantAdministrador.h"

using namespace std;


int main (){
    //Values we are going to use for reading the image
    int width, height, channels;
    //Image we are going to use
    unsigned char *image = stbi_load("images/rostro1.jpg", &width, &height, &channels,0);
    //Size of the image
    size_t imageSize = width*height*channels;

    if(image == NULL){
        cout << "Error al abrir el archivo" << endl;
        return 1;
    }

    QuadrantAdmin* theAdmin = new QuadrantAdmin();

    Pixel* p1 = new Pixel();
    Pixel* p2 = new Pixel();
    Pixel* p3 = new Pixel();
    Pixel* p4 = new Pixel();
    Pixel* p5 = new Pixel();

    p1->setCoordinates(20,20);
    p2->setCoordinates(15,5);
    p3->setCoordinates(200,14);

    theAdmin->addQuadrant(p1);
    theAdmin->addQuadrant(p2);
    theAdmin->addQuadrant(p3);



    cout <<"--------------------------------------" << endl;
    cout <<"Lista" << endl;
    for(int i = 0 ; i < theAdmin->getQuadrantsInImage().size(); i++){
        cout <<"--------------------------------------" << endl; 
        theAdmin->getQuadrantsInImage().at(i)->toString();
    }

    

    //cout<<"Width of the image: "<<width<<endl;
    //cout<<"Height of the image: "<<height<<endl;
    //cout<<"Number of channels of the image: "<<channels<<endl;
    //cout<<endl;

    //recorrer los primeros 10 pixeles de la imagen

    // for(unsigned char *p = image;p!=image + 30; p+=channels){
    //   cout<< *p+0<<" "<<*p+1<<" "<<*p +2<<endl;
    // }

//   //Retornar valores RGB de un pixel en especifico

//     const size_t RGB = 3;
//     int xPosition = 500, yPosition = 400;
//     size_t index = RGB * (yPosition * width + xPosition);
//     cout << "RGB pixel @ (x=3, y=80): " 
//           << static_cast<int>(image[index + 0]) << " "  //red value
//           << static_cast<int>(image[index + 1]) << " "  //green value
//           << static_cast<int>(image[index + 2]) << " "<<endl; //blue value

//     int red = image[index + 0];
//     cout << "Red: " << red << endl;

//     //Limpiar 

    stbi_image_free(image);

	cout << "Creando ob" << endl;
	

    //Deletes
    delete theAdmin;
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;

    return 0;
}