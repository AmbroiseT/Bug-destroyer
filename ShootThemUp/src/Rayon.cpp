#include "Rayon.h"
#include "Niveau.h"
#include <iostream>

Rayon::Rayon(int x, int y):
Sprite(2, 5, x, y, "rayon")
{
    vitesseX=0;
    vitesseY=-0.2;
}

Rayon::Rayon(int x, int y, double vitX, double vitY):
Sprite(2, 5, x, y, "rayon")
{
    vitesseX=vitX;
    vitesseY=vitY;
}



Rayon::~Rayon()
{
    //std::cout << "Destruction de rayon!\n";
}
