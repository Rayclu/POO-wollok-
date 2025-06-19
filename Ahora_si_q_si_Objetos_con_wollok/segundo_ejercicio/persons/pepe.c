#include "../pepe.h"
#include <stdlib.h>
#include <stdio.h>

// Función para crear una nueva persona
persona* crear( int priority ) {
    printf("Bienvenido a crear persona\n");
    persona *Person = (persona*) malloc(sizeof(persona)); // Asignar memoria para el proceso
    if (!Person) {
        printf("Error: No se pudo asignar memoria para la persona\n");
        return NULL; // Verificar si la asignación fue exitosa
    }
    printf("Memoria asignada correctamente\n");

    Person->priority = priority;
    Person->id = -1; // Inicializamos el ID como -1, se actualizará en push
    printf("Prioridad asignada: %d\n", Person->priority);
    // if (priority == 1) {
    //     Person->priority = 1;
    // }else {
    //     Person->priority = 0;
    // }
    return Person; // Retornar el proceso creado
}

// Función para liberar la memoria de un proceso
void quitar_de_la_cola(persona *process) {
    if (process) { // Liberar memoria del puntero
        free(process); // Liberar memoria del proceso
    }
}

