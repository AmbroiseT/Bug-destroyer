#include <iostream>

#include "Enemi.h"
#include "Rayon.h"
#include "Niveau.h"
#include <vector>

Enemi::Enemi(int dimX, int dimY, int x, int y):
Sprite(dimX, dimY, x, y, "Enemi")
{
    vitesseX=0.02;
    vitesseY=0.02;
    detruit=false;
    cadence=1000;
    lastShot=cadence;
    pv=0;
}

Enemi::~Enemi()
{
    //dtor
}

void Enemi::tirer(Niveau* niveau){
    Rayon* ray =new Rayon((2*x+dimX)/2, y-7, this->vitesseX, 0.1);
    ray->setNomSprite("rayonVert");
    ray->setDimX(1);
    ray->setDimY(3);
    niveau->ajouterRayonEnemi(ray);
}

void Enemi::passerTemps(int temps, Niveau* niveau){
    Sprite::passerTemps(temps, niveau);
    std::vector<Rayon*> rays=niveau->getRayonsAllies();
    for(unsigned int i=0; i<rays.size();i++){
        Rayon* ray=rays.at(i);
        if(this->enCollision(ray)){
            ray->setDetruit(true);
            pv--;
            if(pv<0){
                detruit=true;
                niveau->addScore(10);
            }
            break;
        }
    }
    if(x>50 && vitesseX>0){
        vitesseX=-0.01;
    }
    if(x<10 && vitesseX<0){
        vitesseX=0.01;
    }

    lastShot+=temps;
    if(lastShot>cadence){
        this->tirer(niveau);
        lastShot=0;
    }
}

