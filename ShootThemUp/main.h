#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


void logSDLError(std::ostream &os, const std::string &msg);

SDL_Texture * loadTexture(const std::string &file, SDL_Renderer *ren);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);

SDL_Texture * loadTextureDeux(const std::string &file, SDL_Renderer *ren);

#endif // MAIN_H_INCLUDED
