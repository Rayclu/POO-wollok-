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
SDL_Point generatePoints(){
    SDL_Point finalPoint = {
        rand()%SCREEN_WIDTH, // x
        rand()%SCREEN_HEIGHT // y
    };
    return finalPoint;
}
void OutLimits(int * ejeX, int * ejeY, bool reverse){
    cout << reverse << endl;
    int switchCondition = reverse ? 0 : 1;
    if(reverse){
        if(*ejeX <= 0){
            *ejeX = SCREEN_WIDTH;
        }
        if(*ejeY <= 0){
            *ejeY = SCREEN_HEIGHT;
        }
    }else{

        if(*ejeX <= SCREEN_WIDTH){
            printf("The X is %d", *ejeX);
            *ejeX = 0;
        }
        if(*ejeY <= SCREEN_HEIGHT){
            printf("The Y is %d", *ejeY);

            *ejeY = 0;
        }
    }
   /* if(*nocParaQueVoy_a_UsarEstoY > SCREEN_HEIGHT || *nocParaQueVoy_a_UsarEstoY < 0){
        if(reverse){
            cout << reverse << endl;
            cout << *nocParaQueVoy_a_UsarEstoY << endl;
             *nocParaQueVoy_a_UsarEstoY = 8;
            };
        *nocParaQueVoy_a_UsarEstoY = 0;
    }

    if(*nocParaQueVoy_a_UsarEstoX > SCREEN_WIDTH || *nocParaQueVoy_a_UsarEstoX < 0){
        if(!reverse) *nocParaQueVoy_a_UsarEstoX = 8;
        *nocParaQueVoy_a_UsarEstoX = SCREEN_WIDTH;
    }
    */
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

    app.window = SDL_CreateWindow("SlugTerra Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
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

        SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255);

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
