#include "pepe.h"
#include "queue.h"
#include <stdio.h>
#include <iostream>

int main() {
    ColaEspera cola;
    initialize(&cola);
    bool WantExit = false;
    int WhichOption;
    do
    {
        persona* NewPerson = nullptr;
        printf("\nMenu de opciones:\n");
        printf("0 - Agregar una persona a la cola\n");
        printf("1 - Salir del programa\n");
        printf("Ingrese su opción: ");
        
        if(!(std::cin >> WhichOption)) {
            std::cin.clear(); // clear error flags
            std::cin.ignore(10000, '\n'); // ignore bad input
            printf("Entrada inválida. Por favor ingrese un número.\n");
            continue;
        }

        switch (WhichOption)
        {
            case 0:
                /*
                printf("¿Esta persona necesita prioridad? (0 = No, 1 = Si): ");
                int prioridad;
                std::cin >> prioridad;
                printf("Se ha ingresado al bloque de codigo que crea a la persona.");
                NewPerson = crear(prioridad ? 1 : 0);
                push( NewPerson, &cola );
                displayQueue(&cola);
                break;
                */
               printf("¿Esta persona necesita prioridad? (0 = No, 1 = Si): ");
                int prioridad;
                if(std::cin >> prioridad) {
                    if(prioridad != 0 && prioridad != 1) {
                        printf("Valor de prioridad inválido. Debe ser 0 o 1.\n");
                        break;
                    }
                    printf("Creando nueva persona...\n");
                    NewPerson = crear(prioridad);
                    if(NewPerson != nullptr) {
                        push(NewPerson, &cola);
                        printf("Persona agregada exitosamente.\n");
                        displayQueue(&cola);
                    } else {
                        printf("Error al crear la persona.\n");
                    }
                } else {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    printf("Entrada inválida para prioridad.\n");
                }
                break;
            case 1: 
                WantExit = true;
                break;
            default:
                printf("Opción inválida.\n");
                break;
        }
    } while (!WantExit);

    // push(p1, &cola);
    // push(p2, &cola);

    // std::cout << "Persona1: " << p1->priority << std::endl;
    // std::cout << "Persona2: " << p2->priority << std::endl;
    // std::cout << "La cola para esperar el bondi se conforma por: " << std::endl;
    //printf("Front: %d, Rear: %d\n", cola.front, cola.rear);

    // persona *eliminado = poppet(&cola, &cola.front);

    // if (eliminado) {
    //     std::cout << eliminado->priority << std::endl;
    //     printf("Persona con prioridad: %d\n", eliminado->priority);
    //     quitar_de_la_cola(eliminado);
    // }

    // displayQueue(&cola);

    // // Liberar la memoria de la persona restante
    // if (cola.front != -1 && cola.front <= cola.rear) {
    //     quitar_de_la_cola(cola.data[cola.front]);
    // }

    return 0;
}

