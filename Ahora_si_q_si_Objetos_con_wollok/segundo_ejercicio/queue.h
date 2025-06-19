#ifndef QUEUE_H
#define QUEUE_H

#include "pepe.h"

#define MAX 20

typedef struct {
    persona* data[MAX];
    int front;
    int rear;
} ColaEspera;

void initialize(ColaEspera *q);
int push(persona *proc, ColaEspera *Queue);
persona* poppet(ColaEspera *Queue, int *index);
void displayQueue(ColaEspera *q);
ColaEspera* HaveThereSomeoneWithPriority(ColaEspera *q);

#endif // QUEUE_H