#include "Interface.h"
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <map>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

Interface::Interface():SCREEN_WIDTH(1000), SCREEN_HEIGHT(800)
{
    initialiserSDL();
}

Interface::~Interface()
{
    SDL_Quit();
}

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void Interface::logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

int Interface::initialiserSDL(){
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
        logSDLError(std::cout, "SDL_Init");
        return 1;
    }

    win = SDL_CreateWindow("Shoot", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL){
        logSDLError(std::cout, "SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        SDL_DestroyWindow(win);
        logSDLError(std::cout, "SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }

    int flags = MIX_INIT_OGG;
    Mix_Init(flags);
    int result=0;
    if (flags != (result = Mix_Init(flags))) {
        printf("Could not initialize mixer (result: %d).\n", result);
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }


    TTF_Init();

    return 0;
}

SDL_Texture * Interface::loadTextureDeux(const std::string &file, SDL_Renderer *ren){
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
void Interface::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;

    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(ren, tex, NULL, &rect);
}

void Interface::renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h){
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    SDL_RenderCopy(ren, tex, NULL, &rect);
}


void Interface::highscores(){
    TTF_Font* Sans = TTF_OpenFont("font.ttf", 24);

    if(Sans==NULL){
        cout << "Police nulle!\n";
    }

    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;

    SDL_Rect Message_rect;
    Message_rect.x = SCREEN_WIDTH/3;
    Message_rect.y = SCREEN_HEIGHT/10;
    Message_rect.w = SCREEN_WIDTH/5;
    Message_rect.h = SCREEN_HEIGHT/20;

    SDL_Texture* tex=loadTextureDeux("Ressources/screens/highscores.png", ren);
    SDL_RenderClear(ren);
    //Draw the texture
    SDL_RenderCopy(ren, tex, NULL, NULL);

    //Update the screen
    SDL_RenderPresent(ren);

    bool quit=false;
    SDL_Event e;

    while(!quit){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);

        Message_rect.y=200;
        for(int i=0;i<10;i++){
            surfaceMessage = TTF_RenderText_Solid(Sans, jeu.get(i).c_str(), White);
            Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
            SDL_FreeSurface(surfaceMessage);
            SDL_RenderCopy(ren, Message, NULL, &Message_rect);
            Message_rect.y+=Message_rect.h;
        }

        SDL_RenderPresent(ren);

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit=true;
            }
            else if(e.type == SDL_KEYDOWN){
                SDL_KeyboardEvent eK= e.key;
                if(eK.keysym.sym == SDLK_x){
                    quit=true;
                }
            }
        }
    }

    SDL_DestroyTexture(tex);

}


void Interface::gameOver(){

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS("021.ogg");
    Mix_PlayMusic(music, 1);

    SDL_Texture* tex=loadTextureDeux("gameOver2.jpeg", ren);
    SDL_RenderClear(ren);
    //Draw the texture
    SDL_RenderCopy(ren, tex, NULL, NULL);

    //Update the screen
    SDL_RenderPresent(ren);

    bool quit=false;
    SDL_Event e;

    while(!quit){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit=true;
            }
            else if(e.type == SDL_KEYDOWN){
                SDL_KeyboardEvent eK= e.key;
                if(eK.keysym.sym == SDLK_x){
                    quit=true;
                }
            }
        }
    }

    SDL_DestroyTexture(tex);
    Mix_FreeMusic(music);

}

void Interface::menuPrincipal(){
    SDL_Texture* tex=loadTextureDeux("Ressources/screens/menu.png", ren);
    SDL_RenderClear(ren);
    //Draw the texture
    SDL_RenderCopy(ren, tex, NULL, NULL);

    //Update the screen
    SDL_RenderPresent(ren);

    bool quit=false;
    SDL_Event e;

    while(!quit){
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit=true;
            }
            else if(e.type == SDL_KEYDOWN){
                SDL_KeyboardEvent eK= e.key;
                if(eK.keysym.sym == SDLK_x){
                    quit=true;
                }
                else if(eK.keysym.sym == SDLK_e){
                    this->jouer();
                }
                else if(eK.keysym.sym == SDLK_h){
                    highscores();
                }
            }
        }
    }

    SDL_DestroyTexture(tex);
}

void Interface::jouer(){

    Niveau* level=new Niveau();
    Vaisseau* vaisseau=level->getVaisseau();
    level->reIniEchelle(SCREEN_WIDTH, SCREEN_HEIGHT);

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS("011.ogg");
    Mix_PlayMusic(music, -1);



    TTF_Font* Sans = TTF_OpenFont("font.ttf", 24);

    if(Sans==NULL){
        cout << "Police nulle!\n";
    }

    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;

    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = 0;
    Message_rect.w = 100;
    Message_rect.h = 30;

    map<string, SDL_Texture*> textures;

    SDL_Texture* tex2=loadTextureDeux("background.jpeg", ren);
    SDL_Texture* tex=loadTextureDeux("Ressources/galaga/whiteFighter.png", ren);
    SDL_Texture* texLaser=loadTextureDeux("Ressources/laser/laser.png", ren);
    textures["fighter"]=tex;
    textures["fighterRed"]=loadTextureDeux("Ressources/galaga/redFighter.png", ren);
    textures["rayon"]=texLaser;
    textures["Enemi"]=loadTextureDeux("Ressources/galaga/bug1.png", ren);
    textures["EnemiFort"]=loadTextureDeux("Ressources/galaga/bug2.png", ren);
    textures["rayonVert"]=loadTextureDeux("Ressources/laser/laserVert.png", ren);
    textures["background"]=loadTextureDeux("background.jpeg", ren);

    SDL_RenderClear(ren);
    //Draw the texture
    SDL_RenderCopy(ren, tex2, NULL, NULL);

    //Update the screen
    SDL_RenderPresent(ren);

    bool quit=false;
    bool perdu=false;
    SDL_Event e;

    while(!quit && !perdu){
        perdu=level->getPerdu();
        //cout << "Perdu = "<<perdu<<"\n";
        SDL_RenderClear(ren);
        //Draw the texture

        renderTexture(tex2, ren, level->conversionPositionXTR(0), level->conversionPositionYTR(0), level->conversionDistanceTR(level->getDimX()), level->conversionDistanceTR(level->getDimY()));

        string str=level->scoreString();

        surfaceMessage = TTF_RenderText_Solid(Sans, str.c_str(), White);
        Message = SDL_CreateTextureFromSurface(ren, surfaceMessage);
        SDL_FreeSurface(surfaceMessage);
        SDL_RenderCopy(ren, Message, NULL, &Message_rect);

        vector<Sprite*> sprites=level->getElements();
        for(unsigned int i=0;i<sprites.size();i++){
            Sprite* sp=sprites.at(i);
            SDL_Texture* texDessin=textures[sp->getNomSprite()];

            int x=level->conversionPositionXTR(sp->getX());
            int y=level->conversionPositionYTR(sp->getY());
            int dimX=level->conversionDistanceTR(sp->getDimX());
            int dimY=level->conversionDistanceTR(sp->getDimY());


            renderTexture(texDessin, ren, x, y, dimX, dimY);

        }

        SDL_RenderPresent(ren);
        level->passerTemps(10);
        bool pressed=false;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit=true;
            }
            else if(e.type == SDL_KEYDOWN){
                SDL_KeyboardEvent eK= e.key;
                if(eK.keysym.sym == SDLK_x){
                    quit=true;
                }
                else if(eK.keysym.sym == SDLK_LEFT){
                    pressed=true;
                    level->gauchePressed();
                }
                else if(eK.keysym.sym == SDLK_RIGHT){
                    pressed=true;
                    level->droitePressed();
                }
                else if(eK.keysym.sym == SDLK_SPACE){
                    vaisseau->activerCanon();
                }
            }
            else if(e.type == SDL_KEYUP){
                SDL_KeyboardEvent eK= e.key;
                if(eK.keysym.sym == SDLK_x){
                    quit=true;
                }
                else if(eK.keysym.sym == SDLK_LEFT && !pressed){
                    vaisseau->setVitesseX(0);
                }
                else if(eK.keysym.sym == SDLK_RIGHT && !pressed){
                    vaisseau->setVitesseX(0);
                }
                else if(eK.keysym.sym == SDLK_SPACE){
                    vaisseau->desactiverCanon();
                }
            }
        }
        SDL_DestroyTexture(Message);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(tex2);
    SDL_DestroyTexture(textures["Enemi"]);
    SDL_DestroyTexture(textures["rayonVert"]);
    Mix_FreeMusic(music);

    if(perdu){
        jeu.ajouterScore(level->getScore());
        jeu.sauverScores();
        gameOver();
    }
}
