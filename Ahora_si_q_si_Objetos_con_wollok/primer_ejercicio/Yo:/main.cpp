#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "./lanzador.h"
#include "./babosas.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


using namespace std;
int main(int argc, char const *argv[])
{
    typedef struct {
        SDL_Renderer *renderer;
        SDL_Window *window;
    } App;
    cout << "+--------------------------------------+" << endl;
    cout << "|                                      |" << endl;
    cout << "|       Welcome to the SlugTerra       |" << endl;
    cout << "|              Shooter                 |" << endl;
    cout << "|                                      |" << endl;
    cout << "+--------------------------------------+" << endl;
    App app;
    SDL_Init(SDL_INIT_EVERYTHING);
    int rendererFlags, windowFlags;
    
    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    app.window = SDL_CreateWindow("SlugTerra Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    app.renderer = SDL_CreateRenderer(app.window, -1, 0);
     
    bool runningProgram = true;
    SDL_Event event;

    while (runningProgram){

        SDL_RenderClear(app.renderer);
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    runningProgram = false;
                    break;
                default:
                    break;
            }
        }

//        SDL_RenderClear(app.renderer);
        for(int i=0;i <= 10; i++){
            int point = i * 10;
            int Ypoint = i * 500;
            SDL_SetRenderDrawColor(app.renderer, 110, 30, 100, 150);
            SDL_RenderDrawLine(app.renderer, point, point, Ypoint, Ypoint );
            SDL_RenderPresent(app.renderer);
        }
    }



    // bool SelectionFinish = false;
    // while (SelectionFinish)
    // {
        
    //     SelectionFinish = true;
    // }
    
    return 0;
}
