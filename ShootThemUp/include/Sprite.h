#ifndef SPRITE_H
#define SPRITE_H
#include <string>


class Niveau;


class Sprite
{
    public:
        virtual ~Sprite();

        Sprite(int dimX, int dimY, int x, int y, std::string nomSprite);

        Sprite(int dimX, int dimY, int x, int y);

        virtual void passerTemps(int temps);

        virtual void passerTemps(int temps, Niveau* niveau);

        bool enCollision(Sprite* s);

        int getDimX();
        void setDimX(int dimX);

        int getDimY();

        void setDimY(int dimY);

        double getX();

        void setX(int x);

        double getY();

        void setY(int y);

        double getVitesseX();

        void setVitesseX(double vitesseX);

        double getVitesseY();
        void setVitesseY(double vitesseY);

        std::string getNomSprite();

        void setNomSprite(std::string nomSprite);

        void setDetruit(bool b);

        bool getDetruit();


    protected:
        int dimX;
        int dimY;
        double x;
        double y;

        double vitesseX;
        double vitesseY;
        bool detruit;


        std::string nomSprite;
    private:

};

#endif // SPRITE_H
