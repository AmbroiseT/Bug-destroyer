#include <iostream>

#include "Sprite.h"
#include "Niveau.h"
#include "Vaisseau.h"
#include <vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "main.h"
#include <map>
#include <time.h>

#include "Interface.h"

using namespace std;


int main()
{
    srand(time(NULL));

    Interface inter;
    inter.menuPrincipal();

    return 0;
}



/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
SDL_Texture * loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Surface* img=IMG_Load(file.c_str());
    if(img == NULL){
        logSDLError(std::cout, "Chargement de l'image");
        return NULL;
    }
    else{
        SDL_Texture* tex=SDL_CreateTextureFromSurface(ren, img);
        SDL_FreeSurface(img);
        if(tex == NULL){
            logSDLError(std::cout, "Render de l'image");
            return NULL;
        }
        else{
            return tex;
        }
    }
}

SDL_Texture * loadTextureDeux(const std::string &file, SDL_Renderer *ren){
    SDL_Texture* tex=IMG_LoadTexture(ren, file.c_str());
    if(tex == NULL){
        logSDLError(std::cout, "Chargement de l'image");
        return NULL;
    }
    else{
        return tex;
    }
}

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;

    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(ren, tex, NULL, &rect);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    SDL_RenderCopy(ren, tex, NULL, &rect);
}
