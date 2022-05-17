//https://github.com/nothings/stb  --> link to the repositorie to download the stb libraries
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;


int main (){
    cout << "Lectura de la imagen" << endl;
    //Definir valores de la imagen a trabajar
    int width, height, channels;
    /*
    Cantidad de "channels" o componentes hace referencia a los valores de color referentes de la imagen. Es decir:
     No. comp      components
       1       ||    grey
       2       ||    grey, alpha
       3       ||    red, green, blue        (RGB)
       4       ||    red, green, blue, alpha (RGBA)

    **Valor alpha: Hace referencia a la transparencia/opacidad de los valores de color de la imagen
    */
    unsigned char *image = stbi_load("images/prueba.jpg", &width, &height, &channels,0);
    size_t imageSize = width*height*channels;

    cout<<"Width of the image: "<<width<<endl;
    cout<<"Height of the image: "<<height<<endl;
    cout<<"Number of channels of the image: "<<channels<<endl;
    cout<<endl;

    //recorrer los primeros 10 pixeles de la imagen

    for(unsigned char *p = image;p!=image + 30; p+=channels){
      cout<< *p+0<<" "<<*p+1<<" "<<*p +2<<endl;
    }

  //Retornar valores RGB de un pixel en especifico
    const size_t RGB = 3;
    int xPosition = 3, yPosition = 80;
    size_t index = RGB * (yPosition * width + xPosition);
    cout << "RGB pixel @ (x=3, y=80): " 
          << static_cast<int>(image[index + 0]) << " "  //red value
          << static_cast<int>(image[index + 1]) << " "  //green value
          << static_cast<int>(image[index + 2]) << " "<<endl; //blue value

    //Limpiar 
    stbi_image_free(image);
    return 0;
}