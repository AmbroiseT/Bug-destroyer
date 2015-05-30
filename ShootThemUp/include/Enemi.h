#ifndef ENEMI_H
#define ENEMI_H

#include "Sprite.h"

class Enemi : public Sprite
{
    public:
        Enemi(int dimX, int dimY, int x, int y);
        virtual ~Enemi();
        virtual void passerTemps(int temps, Niveau* niveau);
        virtual void tirer(Niveau* niveau);
    protected:
        int pv;
        int lastShot;
        int cadence;
    private:
};

#endif // ENEMI_H
