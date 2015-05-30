#ifndef VAISSEAU_H
#define VAISSEAU_H

#include <string>
#include "Sprite.h"


class Vaisseau : public Sprite
{
    public:

        Vaisseau(int dimX, int dimY, int x, int y, std::string nomSprite);

        Vaisseau(int dimX, int dimY, int x, int y);

        virtual ~Vaisseau();

        void passerTemps(int temps);

        void passerTemps(int temps, Niveau* level);

        bool isCanonActive();

        void activerCanon();

        void desactiverCanon();

        int getLastShot();


    protected:
        int limiteX;
        bool canonActive;
        int lastShot;
        int cadence;
        int PV;
        bool touche;
        const int tempsTouche;
        int lastTouche;
    private:
};

#endif // VAISSEAU_H
