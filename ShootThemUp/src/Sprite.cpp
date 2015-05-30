#include "Sprite.h"
#include <stdio.h>

#include <iostream>

using namespace std;

Sprite::Sprite(int dimX, int dimY, int x, int y, string nomSprite) {
    this->dimX = dimX;
    this->dimY = dimY;
    this->x = x;
    this->y = y;
    this->nomSprite = nomSprite;
    this->vitesseX = 0;
    this->vitesseY = 0;
    this->detruit=false;
}

Sprite::Sprite(int dimX, int dimY, int x, int y) {
    this->dimX = dimX;
    this->dimY = dimY;
    this->x = x;
    this->y = y;
    this->nomSprite = "Inconnu";
    this->detruit=false;
}


Sprite::~Sprite()
{
    //dtor
}

bool Sprite::enCollision(Sprite* autre){
        if(autre->getX() >= x+dimX)
			return false;
		else if(autre->getX()+autre->getDimX() <= x)
			return false;
		else if(autre->getY()>=y+dimY)
			return false;
		else if(autre->getY()+autre->getDimY() <=y)
			return false;
		return true;
}

void Sprite::passerTemps(int temps){
    x+=vitesseX*temps;
    y+=vitesseY*temps;
}

void Sprite::passerTemps(int temps, Niveau* niveau){
    x+=vitesseX*temps;
    y+=vitesseY*temps;
}


int Sprite::getDimX() {
    return dimX;
}

void Sprite::setDimX(int dimX) {
    this->dimX = dimX;
}

void Sprite::setDetruit(bool b) {
    this->detruit=b;
}

bool Sprite::getDetruit() {
    return this->detruit;
}

int Sprite::getDimY() {
    return dimY;
}

void Sprite::setDimY(int dimY) {
    this->dimY = dimY;
}

double Sprite::getX() {
    return x;
}

void Sprite::setX(int x) {
    this->x = x;
}

double Sprite::getY() {
    return y;
}

void Sprite::setY(int y) {
    this->y = y;
}

double Sprite::getVitesseX() {
    return vitesseX;
}

void Sprite::setVitesseX(double vitesseX) {
    this->vitesseX = vitesseX;
}

double Sprite::getVitesseY() {
    return vitesseY;
}

void Sprite::setVitesseY(double vitesseY) {
    this->vitesseY = vitesseY;
}


string Sprite::getNomSprite() {
    return nomSprite;
}

void Sprite::setNomSprite(string nomSprite) {
    this->nomSprite = nomSprite;
}
