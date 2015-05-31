#include "Jeu.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Jeu::Jeu()
{
    chargerScores();
}

Jeu::~Jeu()
{
    //dtor
}

void Jeu::printScores(){
    for(unsigned int i=0;i<scores.size();i++){
        cout << i+1 << " = " << scores.at(i) << "\n";
    }
}

int Jeu::convertionString(std::string nombre){
    int Result;

    stringstream convert(nombre);

    if ( !(convert >> Result) )
        Result = 0;
    return Result;
}


string Jeu::StringScore(){
    stringstream stream;
    stream << "------------------------------\n";
    for(unsigned int i=0;i<scores.size();i++){
        stream << i+1 << ". " << scores.at(i) << "\n";
    }
    return stream.str();
}

string Jeu::get(int i){
    stringstream stream;
    stream << i+1 << ". " << scoreString(scores.at(i));
    return stream.str();
}

void Jeu::chargerScores(){

    ifstream flux("Ressources/Score/scores.txt");

    if(!flux){
        cout << "Erreur dans l'ouverture du fichier" << endl;
        return ;
    }
    else{
        string lecture;
        while(getline(flux, lecture)){
            if(lecture!=""){
                //cout << "Line = " << convertionString(lecture) << "\n";
                scores.push_back(convertionString(lecture));
            }
        }
        flux.close();
    }
}

void Jeu::sauverScores(){
    ofstream flux("Ressources/Score/scores.txt");

    if(!flux){
        cout << "Erreur dans l'ouverture du fichier" << endl;
        return ;
    }
    else{
        for(unsigned int i=0;i<scores.size();i++){
            flux << scores.at(i) << "\n";
        }
        flux.close();
    }
}

string Jeu::scoreString(int score){
    int a = score;
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

void Jeu::ajouterScore(int s){

    if(s>scores.at(scores.size()-1)){
        unsigned int i=scores.size()-1;
        scores[i]= s;
        while(i>0 && scores[i-1]<s){
            scores[i]=scores[i-1];
            i--;
        }
        scores[i]=s;
    }
}
