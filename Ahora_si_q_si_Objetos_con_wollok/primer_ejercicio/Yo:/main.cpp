#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <chrono>
#include <thread>
#include "./lanzador.h"
#include "./babosas.h"

#define SCREEN_WIDTH 1279
#define SCREEN_HEIGHT 720


using namespace std;
struct WindowLimits
{
    int xInit, xEnd;
    int yInit, yEnd;
};

SDL_Point generatePoints(){
    SDL_Point finalPoint = {
        rand()%SCREEN_WIDTH, // x
        rand()%SCREEN_HEIGHT // y
    };
    return finalPoint;
}
void OutLimits(int * ejeX, int * ejeY, bool reverse){

    int switchCondition = reverse ? 0 : 1;
    if(*ejeY > SCREEN_HEIGHT || *ejeY < 0){
        reverse ? 
            *ejeY = SCREEN_HEIGHT
            :
            *ejeY = 0;
    }

    if(*ejeX > SCREEN_WIDTH || *ejeX < 0){
        reverse ? 
            *ejeX = SCREEN_WIDTH
            :
            *ejeX = 0;
    }
    
}
void* getPoints(int* currX, int* currY, int* currY2, int* currX2){
    SDL_Point Points[] = {
        {*currX, *currY},{*currX, *currY2}, {*currX2, *currY}, {*currX2, *currY2}
    };
    return &Points;
}
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
    WindowLimits lims = {
        0, SCREEN_WIDTH,
        0, SCREEN_HEIGHT
    };

    app.window = SDL_CreateWindow("SlugTerra Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, lims.xEnd, lims.yEnd, windowFlags);
    app.renderer = SDL_CreateRenderer(app.window, -1, 0);

    bool runningProgram = true;
    SDL_Event event;

    int currX = 0; 
    int currY = 0;
    int currX2 = SCREEN_WIDTH;
    int currY2 = SCREEN_HEIGHT;
    while (runningProgram){

        SDL_SetRenderDrawColor(app.renderer, 0, 0,0, 255);

        SDL_RenderClear(app.renderer);
        SDL_SetRenderDrawColor(app.renderer, 255, 255, 0, 255);

        // SDL_Point Points[] = {
        //     {currX, currY},{currX, currY2}, {currX2, currY}, {currX2, currY2}
        // };

        

        SDL_RenderDrawPoints(app.renderer,  *getPoints(&currX, &currY, &currY2, &currX), 100);

        SDL_SetRenderDrawColor(app.renderer, 100, 200, 200, 100);
        SDL_RenderDrawLine(
            app.renderer, 
            0, // x inicial
            currY,
            SCREEN_WIDTH, // x final
            currY
        );

        SDL_RenderDrawLine(
            app.renderer, 
            currX,
            0,
            currX,
            SCREEN_HEIGHT
        );
        currX += 8; // sentido normal
        currY += 8; // sentido normal
        OutLimits(&currX, &currY, false); // Recolocar lineas en sentido horario
        SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);
        // Linea en reversa
        SDL_RenderDrawLine(
            app.renderer, 
            currX2, // x inicial
            0,
            currX2, // x final
            SCREEN_HEIGHT
        );
        SDL_RenderDrawLine(
            app.renderer, 
            0, // x inicial
            currY2,
            SCREEN_WIDTH, // x final
            currY2
        );
        //cout << currX2 << "\n" << endl;
        currX2 -= 8; // x reversa
        currY2 -= 8; //y reversa
        OutLimits(&currX2, &currY2, true); // Recolocar lineas en sentido anti-horario


        SDL_RenderPresent(app.renderer);
        while (SDL_PollEvent(&event)){
            switch (event.type){
                case SDL_QUIT:
                    runningProgram = false;
                    break;
                default:
                    break;
            }
        }
        usleep(125000);
    }
    return 0;
}
