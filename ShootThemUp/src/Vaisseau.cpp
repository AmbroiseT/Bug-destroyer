#include "Vaisseau.h"
#include "Rayon.h"
#include "Niveau.h"

#include<string>
#include <iostream>

using namespace std;

Vaisseau::Vaisseau(int dimX, int dimY, int x, int y, string nomSprite) :
Sprite(dimX, dimY, x, y, nomSprite), tempsTouche(200) {
    limiteX=70;
    canonActive=false;
    lastShot=0;
    cadence=100;
    detruit=false;
    touche=false;

    lastTouche=0;
}

Vaisseau::Vaisseau(int dimX, int dimY, int x, int y) :
Sprite(dimX, dimY, x, y, "fighter"), tempsTouche(200) {
    limiteX=70;
    canonActive=false;
    lastShot=0;
    cadence=100;
    detruit=false;
    touche=false;
    PV=10;
}


Vaisseau::~Vaisseau()
{
    //dtor
}

bool Vaisseau::isCanonActive(){
    return canonActive;
}

void Vaisseau::activerCanon(){
    canonActive=true;
}

void Vaisseau::desactiverCanon(){
    canonActive=false;
    lastShot=cadence;
}

void Vaisseau::passerTemps(int temps){
    Sprite::passerTemps(temps);
    if(this->x<0){
        this->x=0;
    }
    if(this->dimX+this->x>limiteX){
        this->x=limiteX-this->dimX;
    }
}

void Vaisseau::passerTemps(int temps, Niveau* level){

    Sprite::passerTemps(temps);
    if(this->x<0){
        this->x=0;
    }
    if(this->dimX+this->x>limiteX){
        this->x=limiteX-this->dimX;
    }
    if(isCanonActive()){
        lastShot+=temps;
        if(lastShot/cadence>=1){
            lastShot=0;
            Rayon* ray =new Rayon((2*x+dimX)/2, y-7, (this->vitesseX)/5, -0.1);
            level->ajouterRayonAllie(ray);
        }
    }

    if(touche){
        lastTouche+=temps;
        if(lastTouche>tempsTouche){
            touche=false;
            this->setNomSprite("fighter");
        }
    }
    else{
        std::vector<Rayon*> rays=level->getRayonsEnemis();
        for(unsigned int i=0; i<rays.size();i++){
            Rayon* ray=rays.at(i);
            if(this->enCollision(ray)){
                PV--;
                cout << "Touché\n";
                touche=true;
                lastTouche=0;
                this->setNomSprite("fighterRed");
                ray->setDetruit(true);
                if(PV<0){
                    this->setDetruit(true);
                    cout << "Destruction\n";
                }
                break;
            }
        }
    }
}

int Vaisseau::getLastShot(){
    return lastShot;
}
