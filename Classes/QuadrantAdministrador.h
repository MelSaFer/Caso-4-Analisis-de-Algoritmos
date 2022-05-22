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
            cout <<"\nEn lista hay: " <<  quadrantsInImage.size() << endl;

            for(int indexOfQuadrant = 0; indexOfQuadrant < quadrantsInImage.size(); indexOfQuadrant++){
                //cout << "Cuadrante actual: ";
                //quadrantsInImage.at(indexOfQuadrant)->toString();
                
                if( (quadrantsInImage.at(indexOfQuadrant)->getMaxX() > pNewPixel->getCoordinateX()) &&
                    (quadrantsInImage.at(indexOfQuadrant)->getMinX() < pNewPixel->getCoordinateX()) &&
                    (quadrantsInImage.at(indexOfQuadrant)->getMaxY() > pNewPixel->getCoordinateY()) && 
                    (quadrantsInImage.at(indexOfQuadrant)->getMinY() < pNewPixel->getCoordinateY())){
                        quadrantsInImage.at(indexOfQuadrant)->addPixel(pNewPixel);
                        //HAY QUE ACTUALIZAR LAS DIMENSIONES DEL CUADRANTE
                        //Se llama a la funcion para actualizar estadisticas, o no?
                        cout << "El cuadrante ya existia\n" << "Se agrego el pixel en: " << endl;
                        pNewPixel->toString();
                        
                        return;
                    }
            }     
            Quadrant* newQuadrant = new Quadrant();
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