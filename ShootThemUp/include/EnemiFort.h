#ifndef ENEMIFORT_H
#define ENEMIFORT_H

#include "Enemi.h"

class EnemiFort : public Enemi
{
    public:
        EnemiFort(int dimX, int dimY, int x, int y);
        virtual ~EnemiFort();
        virtual void passerTemps(int temps, Niveau* niveau);
        virtual void tirer(Niveau* niveau);
    protected:
    private:
};

#endif // ENEMIFORT_H
