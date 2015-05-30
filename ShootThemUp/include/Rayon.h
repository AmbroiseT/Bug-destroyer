#ifndef RAYON_H
#define RAYON_H

#include "Sprite.h"

class Rayon : public Sprite
{
    public:
        Rayon(int x, int y);
        Rayon(int x, int y, double vitX, double vitY);
        virtual ~Rayon();

    protected:
    private:

};

#endif // RAYON_H
