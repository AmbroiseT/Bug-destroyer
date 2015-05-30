#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

#include "Sprite.h"
#include "Niveau.h"
#include "Vaisseau.h"
#include <vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include <map>
#include <time.h>

class Interface
{
    public:
        Interface();
        virtual ~Interface();

        int initialiserSDL();

        void logSDLError(std::ostream &os, const std::string &msg);
        SDL_Texture * loadTextureDeux(const std::string &file, SDL_Renderer *ren);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
        void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
        void jouer();
        void gameOver();
        void menuPrincipal();

    protected:
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        SDL_Window *win;
        SDL_Renderer *ren;

};

#endif // INTERFACE_H
