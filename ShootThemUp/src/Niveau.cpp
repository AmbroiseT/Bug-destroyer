#include "Niveau.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

Niveau::Niveau()
{
    vaisseau = new Vaisseau(7, 7, 0, 90);

    dimX=70;
	dimY=100;

	x0=0;
	y0=0;
	echelle=1;
    lastEnemy=0;
    perdu=false;
    score=0;

    background1=new Background();
    background2=new Background();
    background2->setY(-dimY);
}

Niveau::~Niveau()
{
    //dtor
}


void Niveau::reIniEchelle(int w, int h){
    double echelleY=((double)h)/dimY;
    double echelleX=((double)w)/dimX;
    if(echelleY<echelleX){
        echelle=echelleY;
        int dX=(int)(echelle*dimX);
        int dec=w-dX;
        x0=dec/2;
    }
    else{
        echelle=echelleX;
        int dy=(int)(echelle*dimY);
        int dec=w-dy;
        y0=dec/2;
    }
}

int Niveau::conversionDistanceTR(int d){
    return (int)(d*echelle);
}

int Niveau::conversionPositionXTR(double pos){
    return (int)(pos*echelle)+x0;
}
int Niveau::conversionPositionYTR(double pos){
    return (int)(pos*echelle)+y0;
}


vector<Sprite*> Niveau::getElements(){
    vector<Sprite*> retour=vector<Sprite*>();

    retour.push_back(background1);
    retour.push_back(background2);

    retour.push_back(vaisseau);
    for(unsigned int i=0;i<rayonsAllies.size();i++){
        retour.push_back(rayonsAllies.at(i));
    }
    for(unsigned int i=0;i<rayonsEnemis.size();i++){
        retour.push_back(rayonsEnemis.at(i));
    }
    for(unsigned int i=0;i<enemis.size();i++){
        retour.push_back(enemis.at(i));
    }

    return retour;
}

vector<Rayon*> Niveau::getRayonsAllies(){
    return rayonsAllies;
}

vector<Rayon*> Niveau::getRayonsEnemis(){
    return rayonsEnemis;
}

std::vector<Enemi*> Niveau::getEnemis(){
    return enemis;
}

void Niveau::passerTemps(int temps){

    gestionBackground(temps);
    vector<Sprite*> vect=this->getElements();
    Sprite* s;
    unsigned int i=0;
    while(i<vect.size()){
        s=vect.at(i);
        s->passerTemps(temps, this);
        i++;
    }
    ajoutEnemis(temps);
    nettoyer();

    if(vaisseau->getDetruit()){
        perdu=true;
    }
}

void Niveau::gestionBackground(int temps){
    background1->passerTemps(temps);
    background2->passerTemps(temps);
    if(background1->getY()>this->getDimY()){
        Background* tmp=background1;
        background1=background2;
        background2=tmp;
        background2->setY(background1->getY()-this->getDimY());
    }
}

void Niveau::ajoutEnemis(int temps){
    lastEnemy+=temps;
    if(lastEnemy>=500){
        lastEnemy=0;
        int x=rand()%(dimX-5);
        if(this->getScore()>100 && rand()%3==0){
            enemis.push_back(new EnemiFort(5, 5, x, 3));
        }
        else{
            enemis.push_back(new Enemi(5, 5, x, 3));
        }
    }
}

void Niveau::nettoyer(){
    unsigned int i;
    for(i=0;i<rayonsAllies.size();i++){
        Rayon* ray=rayonsAllies.at(i);
        if(estSorti(ray) || ray->getDetruit()){
            rayonsAllies.erase(rayonsAllies.begin()+i);
            delete ray;
        }
    }

    for(i=0;i<rayonsEnemis.size();i++){
        Rayon* ray=rayonsEnemis.at(i);
        if(estSorti(ray) || ray->getDetruit()){
            rayonsEnemis.erase(rayonsEnemis.begin()+i);
            delete ray;
        }
    }

    for(i=0;i<enemis.size();i++){
        Enemi* enemi=enemis.at(i);
        if(estSorti(enemi) || enemi->getDetruit()){
            enemis.erase(enemis.begin()+i);
            delete enemi;
        }
    }
}

 bool Niveau::estSorti(Sprite* sprite){
    return (sprite->getX()+sprite->getY()<0) || (sprite->getDimY()+sprite->getY()<0) || (sprite->getX()>dimX) || (sprite->getY()>dimY);
 }

void Niveau::ajouterRayonAllie(Rayon * rayon){
    rayonsAllies.push_back(rayon);
}

void Niveau::ajouterRayonEnemi(Rayon * rayon){
    rayonsEnemis.push_back(rayon);
}

int Niveau::getX0() {
    return x0;
}

int Niveau::getY0() {
    return y0;
}

int Niveau::getDimX() {
    return dimX;
}

int Niveau::getDimY() {
    return dimY;
}

void Niveau::gauchePressed() {
    vaisseau->setVitesseX(-0.1);
}

void Niveau::droitePressed() {
    vaisseau->setVitesseX(0.1);
}

void Niveau::gaucheReleased() {
    vaisseau->setVitesseX(0);
}

void Niveau::droiteReleased() {
    vaisseau->setVitesseX(0);
}

void Niveau::spacePressed(){
    vaisseau->activerCanon();
}

void Niveau::spaceReleased(){
    vaisseau->desactiverCanon();
}

Vaisseau* Niveau::getVaisseau(){
    return vaisseau;
}

bool Niveau::getPerdu(){
    return perdu;
}

int Niveau::getScore(){
    return score;
}

string Niveau::scoreString(){
    int a = this->getScore();
    stringstream ss;
    int tmp=a+1;
    while(tmp<100000){
        ss << "0";
        tmp=tmp*10;
    }
    ss << a;
    string str = ss.str();
    return str;
}

void Niveau::addScore(int val){
    score+=val;
}
