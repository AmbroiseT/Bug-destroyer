#ifndef NIVEAU_H
#define NIVEAU_H

#include <vector>

#include "Enemi.h"
#include "EnemiFort.h"
#include "Vaisseau.h"
#include "Sprite.h"
#include "Rayon.h"
#include "Background.h"


class Niveau
{
    public:
        Niveau();
        virtual ~Niveau();

        void reIniEchelle(int w, int h);

        int conversionDistanceTR(int d);

        int conversionPositionXTR(double pos);
        int conversionPositionYTR(double pos);

        std::vector<Sprite*> getElements();
        void passerTemps(int temps);
        void nettoyer();
        void ajoutEnemis(int temps);
        int getX0();
        int getY0();
        int getDimX();

        int getDimY();

        void gauchePressed();

        void droitePressed();
        void gaucheReleased();
        void droiteReleased();

        Vaisseau* getVaisseau();


        void spacePressed();
        void spaceReleased();

        void ajouterRayonAllie(Rayon * rayon);
        void ajouterRayonEnemi(Rayon * rayon);

        std::vector<Rayon*> getRayonsAllies();
        std::vector<Rayon*> getRayonsEnemis();
        std::vector<Enemi*> getEnemis();

        bool estSorti(Sprite* sprite);

        bool getPerdu();
        int getScore();
        std::string scoreString();
        void addScore(int val);
        void gestionBackground(int temps);

    protected:
    private:
        Vaisseau* vaisseau;
        std::vector<Sprite*> elements;
        std::vector<Rayon*> rayonsAllies;
        std::vector<Rayon*> rayonsEnemis;
        std::vector<Enemi*> enemis;
        int dimX;
        int dimY;

        bool perdu;
        int lastEnemy;
        int x0;
        int y0;
        double echelle;
        int score;

        Background* background1;
        Background* background2;
};

#endif // NIVEAU_H
