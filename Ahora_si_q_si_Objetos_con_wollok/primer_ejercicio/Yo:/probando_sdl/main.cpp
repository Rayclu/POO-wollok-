#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <iostream>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
using namespace std;

/*
SDL_Window * window = NULL;

int main(){
    if(SDL_Init(SDL_INIT_VIDEO)){
        printf("SDL could not init.... SDL_Error: %s", SDL_GetError());
        return -1;

    }else
    {
        window = SDL_CreateWindow("Tutorial",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            fprintf(stderr, "window could not be created! SDL_ERROR: %s\n", SDL_GetError());
            return -1;
        }
        
    }
    SDL_Delay(1000000000);
    return 0;
}
*/
typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

void initSDL(App app)
{
    int rendererFlags, windowFlags;
    
    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow("Shooter 01", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void doInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }
    }
}
void prepareScene(App& app)
{
    SDL_SetRenderDrawColor(app.renderer, 96, 128, 255, 255);
    SDL_RenderClear(app.renderer);
}

void presentScene(void(*scene)(App&), App app)
{
   // SDL_RenderPresent();
}

int main(){
    App app;
    initSDL(app);

    while(1){
        doInput();
       // presentScene( void &prepareScene(App &app) );
        SDL_Delay(30);
    }
    return 0;
}




    /*
    DE BASE DE DATOS:
        CREATE TABLE INSCRICIONES(
        ID_INS INT PRIMARY KEY,
        ID_ALUMNO INT,
        ID_CURSO INT,
        FECHA_INSCRIPCION DATE
        );

        INSERT INTO INSCRIPCIONES VALUES 
        (1,101,1,'2025-02-01')
        (2, 102, 2,'2025-02-01');

        2) Parte 2: 
            -- Simular una transaccion;
            -- Simular una transaccion sin cofirmar cambios;
            start TRANSACTION;
            -- Insertar nueva transaccion

            INSET INTO Inscripciones
            (ID_Inscripciones, ID_Alumno, ID_Curso, Fecha_Inscripcion) VALUES (3,103,3,'025-05-20');

            --CONSULTAR SI EL DATO ESTA (AUNQUE NO SE HAYA EJECUTAFO EL COMMIT)

            SELECT * FROM Inscripciones WHERE ID_Inscripcion = 3; 


            3) DECISION
            --SI TODO ESTA CORRECTO 
            COMMIT;
            -- SI HUBO UN ERRROR 
            ROLLBACK;
            */


// int main(int argc, char* argv[]) {
//     // Inicialización de SDL
//     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//         cout << SDL_Init(SDL_INIT_VIDEO) << endl;
//         //std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
//         return 1;
//     }

//     // Creación de una ventana
//     SDL_Window* window = SDL_CreateWindow(
//         "Mi primer SDL",             // título
//         SDL_WINDOWPOS_UNDEFINED,     // posición x
//         SDL_WINDOWPOS_UNDEFINED,     // posición y
//         800,                         // ancho
//         600,                         // alto
//         SDL_WINDOW_SHOWN             // flags
//     );

//     if (!window) {
//         std::cerr << "Error al crear ventana: " << SDL_GetError() << std::endl;
//         SDL_Quit();
//         return 1;
//     }

//     // Creación de un renderer
//     SDL_Renderer* renderer = SDL_CreateRenderer(
//         window,                      // ventana asociada
//         -1,                          // índice del driver
//         SDL_RENDERER_ACCELERATED |   // flags
//         SDL_RENDERER_PRESENTVSYNC
//     );

//     if (!renderer) {
//         std::cerr << "Error al crear renderer: " << SDL_GetError() << std::endl;
//         SDL_DestroyWindow(window);
//         SDL_Quit();
//         return 1;
//     }

//     // Bucle principal del juego
//     bool running = true;
//     SDL_Event event;

//     while (running) {
//         // Manejo de eventos
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//         }

//         // Limpiar pantalla
//         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
//         SDL_RenderClear(renderer);

//         // Dibujar algo (ejemplo: un rectángulo rojo)
//         SDL_Rect rect = {100, 100, 200, 150};
//         SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
//         SDL_RenderFillRect(renderer, &rect);

//         // Actualizar pantalla
//         SDL_RenderPresent(renderer);
//     }

//     // Limpieza
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();

//     return 0;
// }