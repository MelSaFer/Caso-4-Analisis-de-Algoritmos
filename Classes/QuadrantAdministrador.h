#ifndef QUADRANT_ADMIN
#define QUADRANT_ADMIN

//LIBRARIES---------------------------------
#include <vector>
#include "Quadrant.h"
#include "Pixel.h"
#include <random>
#include "Greys.h"


#define EXPAND_RANGE 20.0

class QuadrantAdmin{
    private:
        int pixelsQuantity;
        vector<Quadrant*> quadrantsInImage;
    
    public:
        //Methods
        void incrementPixelsQuantity()
        {
            this->pixelsQuantity++;
        }

        int getPixelsQuantity()
        {
            return pixelsQuantity;
        }

        void setQuadrantsInImage(vector<Quadrant*> pListOfQuadrants){
            quadrantsInImage = pListOfQuadrants;
        }

        vector<Quadrant*> getQuadrantsInImage(){
            return quadrantsInImage;
        }

        Quadrant* getQuadrant(int pIndexQuadrant){
            return quadrantsInImage.at(pIndexQuadrant);
        }

        void addQuadrant(Quadrant* pNewQuadrant){
            quadrantsInImage.insert(quadrantsInImage.begin(), pNewQuadrant);
        }

        void addQuadrant(float pProbability, unsigned char* pImageFile, vector<Grey> pGreyInImage){
            random_device rd;
            default_random_engine eng(rd());

            int quantityQuadrants = this->quadrantsInImage.size();
            int red, green, blue;
            const size_t RGB = 3;
            size_t index;

            for(int indexOfQuadrant = 0; indexOfQuadrant < quantityQuadrants; indexOfQuadrant++){

                // cout << "================" << endl;
                // cout << "Proba: " << pProbability << endl;
                // cout << "Bottom range: " << quadrantsInImage.at(indexOfQuadrant)->getBottomRandom() << endl;
                // cout << "Top range: " << quadrantsInImage.at(indexOfQuadrant)->getTopRandom() << endl;
                // cout << "================" << endl;

                // if the probability is between the range of the quadrant
                if(pProbability >= quadrantsInImage.at(indexOfQuadrant)->getBottomRandom() && pProbability < quadrantsInImage.at(indexOfQuadrant)->getTopRandom()){
                    cout << "Index: " << indexOfQuadrant << ", " << quadrantsInImage.size()-1 << endl;

                    // if the probability doesn't match with anyone, the last is the case 1080 x 1080
                    // we select an aleatory coordenate between 0 - 1080 and make a pixel, then we create a new quadrant
                    // surrounding that pixel.
                    if(indexOfQuadrant == (quadrantsInImage.size()-1)){ 
                        cout << "Caso final" << endl;

                        // the 2 randoms for the x and the y
                        uniform_real_distribution<> distr(quadrantsInImage.at(indexOfQuadrant)->getMinX(), quadrantsInImage.at(indexOfQuadrant)->getMaxX()); // random range
                        uniform_real_distribution<> distr2(quadrantsInImage.at(indexOfQuadrant)->getMinY(), quadrantsInImage.at(indexOfQuadrant)->getMaxY()); // random range

                        // create the new pixel and asign the coordenates and the color
                        this->pixelsQuantity++;
                        Pixel* newQuadrantPixel = new Pixel();
                        newQuadrantPixel->setCoordinateX(distr(eng));
                        newQuadrantPixel->setCoordinateY(distr2(eng));

                        index = RGB * (newQuadrantPixel->getCoordinateY() * 1080 + newQuadrantPixel->getCoordinateX());

                        red = pImageFile[index + 0];
                        green = pImageFile[index + 1];
                        blue = pImageFile[index + 2];

                        cout << "Colores: " << red << ", " << green << ", " << blue << endl;

                        newQuadrantPixel->setRGBColor(red,green,blue);
                        newQuadrantPixel->setGrey(red, green, blue, pGreyInImage);
                        
                        // sacar ese punto, su color
                        
                        // create the new quadrant
                        Quadrant* newQuadrant = new Quadrant();
                        newQuadrant->setBottomRandom(0);
                        newQuadrant->setTopRandom(1);
                        newQuadrant->setMinX(newQuadrantPixel->getCoordinateX()-10);
                        newQuadrant->setMinY(newQuadrantPixel->getCoordinateY()-10);
                        newQuadrant->setMaxX(newQuadrantPixel->getCoordinateX()+10);
                        newQuadrant->setMaxY(newQuadrantPixel->getCoordinateY()+10);
                        newQuadrant->setBottomRandom(0.0);
                        newQuadrant->setTopRandom((EXPAND_RANGE * EXPAND_RANGE) / (1080.0*1080.0));

                        // newQuadrant->setBottomRandom(quadrantsInImage.at(indexOfQuadrant)->getBottomRandom());
                        // newQuadrant->setTopRandom(quadrantsInImage.at(indexOfQuadrant)->getBottomRandom() + ((EXPAND_RANGE*EXPAND_RANGE)/(1080.0*1080.0)));

                        cout << "Bottom range: " << newQuadrant->getBottomRandom() << endl;
                        cout << "Top range: " << newQuadrant->getTopRandom() << endl;

                        // add the pixel to the new quadrant
                        newQuadrant->addPixel(newQuadrantPixel);

                        // add the new quadrant
                        this->addQuadrant(newQuadrant);
                        updateProbability(0);

                        return;
                    }
                    else{
                        uniform_real_distribution<> distr(quadrantsInImage.at(indexOfQuadrant)->getMinX(), quadrantsInImage.at(indexOfQuadrant)->getMaxX()); // random range
                        uniform_real_distribution<> distr2(quadrantsInImage.at(indexOfQuadrant)->getMinY(), quadrantsInImage.at(indexOfQuadrant)->getMaxY()); // random range

                        this->pixelsQuantity++;
                        Pixel* newQuadrantPixel = new Pixel();
                        newQuadrantPixel->setCoordinateX(distr(eng));
                        newQuadrantPixel->setCoordinateY(distr2(eng));

                        index = RGB * (newQuadrantPixel->getCoordinateY() * 1080 + newQuadrantPixel->getCoordinateX());

                        red = pImageFile[index + 0];
                        green = pImageFile[index + 1];
                        blue = pImageFile[index + 2];

                        cout << "Colores: " << red << ", " << green << ", " << blue << endl;
                        newQuadrantPixel->setRGBColor(red,green,blue);

                        // se tiene que convertir a escala de grises, si el color del nuevo pixel es igual
                        // al del dominante se hace lo de expandir el area, sino solo se agrega

                        //Updating the dimentions of the quadrant
                        int newMaxX = newQuadrantPixel->getCoordinateX() + 20 ;
                        int newMinX = newQuadrantPixel->getCoordinateX() - 20 ;
                        int newMaxY = newQuadrantPixel->getCoordinateY() + 20 ;
                        int newMinY = newQuadrantPixel->getCoordinateY() - 20 ;

                        bool increase = false;

                        if(newMaxX > quadrantsInImage.at(indexOfQuadrant)->getMaxX()){
                            quadrantsInImage.at(indexOfQuadrant)->setMaxX(newMaxX);
                            increase = true;
                        }
                        if(newMinX < quadrantsInImage.at(indexOfQuadrant)->getMinX()){
                            quadrantsInImage.at(indexOfQuadrant)->setMinX(newMinX);
                            increase = true;
                        }
                        if(newMaxY > quadrantsInImage.at(indexOfQuadrant)->getMaxY()){
                            quadrantsInImage.at(indexOfQuadrant)->setMaxY(newMaxY);
                            increase = true;
                        }
                        if(newMinY < quadrantsInImage.at(indexOfQuadrant)->getMinY()){
                            quadrantsInImage.at(indexOfQuadrant)->setMinY(newMinY);
                            increase = true;
                        }
                        // sacar ese punto, su color
                        quadrantsInImage.at(indexOfQuadrant)->addPixel(newQuadrantPixel);

                        if(increase)
                            updateProbability(indexOfQuadrant);
                        return;
                    }
                }
            }           
        }

        void updateProbability (int pRowPosition){

            float largo = getQuadrant(pRowPosition)->getMaxX() - getQuadrant(pRowPosition)->getMinX();
            float alto = getQuadrant(pRowPosition)->getMaxY() - getQuadrant(pRowPosition)->getMinY();

            float porcentage = ((largo+0.0) * (alto+0.0)) / (1080.0*1080.0);
            cout << (largo+0.0) * (alto+0.0) << endl;
            cout << "Largo: " << largo << ", Alto: " << alto << endl;
            cout << "Porcentage: -> " << porcentage << endl;

            float diferencia = (getQuadrant(pRowPosition)->getBottomRandom() + porcentage) - getQuadrant(pRowPosition)->getTopRandom();
            // cout << "Diferencia: -> " << diferencia << endl;

            // getQuadrant(pRowPosition)->setBottomRandom(0.0);
            // // this->quadrantsInImage.at(pRowPosition)->setBottomRandom(0.0);
            float suma = getQuadrant(pRowPosition)->getBottomRandom() + porcentage;
            // cout << "suma: " << suma << endl;
            this->quadrantsInImage.at(pRowPosition)->setTopRandom(suma);

            pRowPosition ++;
            // cout << "Row pos: " << pRowPosition << endl;

            for(; pRowPosition < this->quadrantsInImage.size(); pRowPosition++){
                if(pRowPosition != this->quadrantsInImage.size() - 1){
                    this->quadrantsInImage[pRowPosition]->setBottomRandom(\
                    this->quadrantsInImage[pRowPosition]->getBottomRandom() + diferencia
                    );

                    this->quadrantsInImage[pRowPosition]->setTopRandom(\
                    this->quadrantsInImage[pRowPosition]->getTopRandom() + diferencia
                    );
                }
                else{
                    this->quadrantsInImage.at(pRowPosition)->setBottomRandom(\
                    this->quadrantsInImage.at(pRowPosition)->getBottomRandom() + diferencia
                    );
                }
            }
        }
        
};




#endif