#include "EnemiFort.h"
#include "Rayon.h"
#include "Niveau.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

EnemiFort::EnemiFort(int dimX, int dimY, int x, int y) : Enemi(dimX, dimY, x, y)
{
    pv=0;
    this->setNomSprite("EnemiFort");
    lastShot=cadence+1;
}

EnemiFort::~EnemiFort()
{
    //dtor
}

void EnemiFort::tirer(Niveau* niveau){
    Rayon* ray =new Rayon((2*x+dimX)/2, y-2, 0, 0.1);
    ray->setNomSprite("rayonVert");
    ray->setDimX(1);
    ray->setDimY(1);
    niveau->ajouterRayonEnemi(ray);

    ray=new Rayon((2*x+dimX)/2, y-2, -0.01, 0.1);
    ray->setNomSprite("rayonVert");
    ray->setDimX(1);
    ray->setDimY(1);
    niveau->ajouterRayonEnemi(ray);

    ray=new Rayon((2*x+dimX)/2, y-2, 0.01, 0.1);
    ray->setNomSprite("rayonVert");
    ray->setDimX(1);
    ray->setDimY(1);
    niveau->ajouterRayonEnemi(ray);

}

void EnemiFort::passerTemps(int temps, Niveau* niveau){
    Enemi::passerTemps(temps, niveau);
}
