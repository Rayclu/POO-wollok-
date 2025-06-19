#ifndef PERSONA_H
#define PERSONA_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct {
    int priority;
    int id;
} persona;

persona* crear(int priority);
void quitar_de_la_cola(persona *process);

#endif