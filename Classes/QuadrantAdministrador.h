#ifndef QUADRANT_ADMIN
#define QUADRANT_ADMIN

//LIBRARIES---------------------------------
#include <vector>
#include "Quadrant.h"
#include "Pixel.h"

class QuadrantAdmin{
    private:
        vector<Quadrant*> quadrantsInImage;
    
    public:
        //Metodos
        void setQuadrantsInImage(vector<Quadrant*> pListOfQuadrants){
            quadrantsInImage = pListOfQuadrants;
        }

        vector<Quadrant*> getQuadrantsInImage(){
            return quadrantsInImage;
        }

        void addQuadrant(Pixel* pNewPixel){
            cout <<"\nEn lista hay: " <<  quadrantsInImage.size() << " cuadrantes" << endl;
            //We analice the quadrants in the image to verify if the pixel is in one or if we have to create one
            for(int indexOfQuadrant = 0; indexOfQuadrant < quadrantsInImage.size(); indexOfQuadrant++){
                //if the pixel is in the quadrant
                if( (quadrantsInImage.at(indexOfQuadrant)->getMaxX() > pNewPixel->getCoordinateX()) &&
                    (quadrantsInImage.at(indexOfQuadrant)->getMinX() < pNewPixel->getCoordinateX()) &&
                    (quadrantsInImage.at(indexOfQuadrant)->getMaxY() > pNewPixel->getCoordinateY()) && 
                    (quadrantsInImage.at(indexOfQuadrant)->getMinY() < pNewPixel->getCoordinateY())){
                        cout << "Antes..." << endl;
                        quadrantsInImage.at(indexOfQuadrant)->toString();

                        //We add the new Pixel
                        quadrantsInImage.at(indexOfQuadrant)->addPixel(pNewPixel);
                        
                        //Se llama a la funcion para actualizar estadisticas, o no?

                        cout << "\nEl cuadrante ya existia\n" << "Se agrego el pixel: " << endl;
                        pNewPixel->toString();

                        //Updating the dimentions of the quadrant
                        int newMaxX = pNewPixel->getCoordinateX() + 20 ;
                        int newMinX = pNewPixel->getCoordinateX() - 20 ;
                        int newMaxY = pNewPixel->getCoordinateY() + 20 ;
                        int newMinY = pNewPixel->getCoordinateY() - 20 ;

                        if(newMaxX > quadrantsInImage.at(indexOfQuadrant)->getMaxX()){
                            quadrantsInImage.at(indexOfQuadrant)->setMaxX(newMaxX);
                        }

                        if(newMinX < quadrantsInImage.at(indexOfQuadrant)->getMinX()){
                            quadrantsInImage.at(indexOfQuadrant)->setMinX(newMinX);
                        }

                        if(newMaxY > quadrantsInImage.at(indexOfQuadrant)->getMaxY()){
                            quadrantsInImage.at(indexOfQuadrant)->setMaxY(newMaxY);
                        }

                        if(newMinY < quadrantsInImage.at(indexOfQuadrant)->getMinY()){
                            quadrantsInImage.at(indexOfQuadrant)->setMinY(newMinY);
                        }
                        
                        cout << "Despues..." << endl;
                        quadrantsInImage.at(indexOfQuadrant)->toString();
                        
                        return;
                    }
            }   

            //We create a new quadrant for the pixel  
            Quadrant* newQuadrant = new Quadrant();
            //Adds the pixel to the quadrant
            newQuadrant->addPixel(pNewPixel);

            newQuadrant->setMaxX(pNewPixel->getCoordinateX() + 20);
            newQuadrant->setMinX(pNewPixel->getCoordinateX() - 20);

            newQuadrant->setMaxY(pNewPixel->getCoordinateY() + 20);
            newQuadrant->setMinY(pNewPixel->getCoordinateY() - 20);

            newQuadrant->setProbability();

            quadrantsInImage.insert(quadrantsInImage.begin(), newQuadrant);
            //Se llama a la funcion para actualizar estadisticas
            cout << "El cuadrante no existia, se creo uno\n" << "Se agrego el pixel en: " << endl;
            pNewPixel->toString();
            
        }
        
};


















#endif