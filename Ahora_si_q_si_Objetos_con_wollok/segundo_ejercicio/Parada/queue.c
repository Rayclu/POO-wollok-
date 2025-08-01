#include "../queue.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void initialize(ColaEspera *q) {
    q->front = -1;
    q->rear = -1;
}

int push(persona *proc, ColaEspera *Queue) {
    if (Queue == NULL || proc == NULL) {
        printf("Error: Cola o persona inválida\n");
        return -1;
    }
    if (Queue->rear == MAX - 1) {
        printf("Error: Cola llena\n");
        return -1;
    }
    if (Queue->front == -1) Queue->front = 0;
    
    Queue->rear++;
    Queue->data[Queue->rear] = proc;
    proc->id = Queue->rear;
    printf("Persona agregada - ID: %d, Prioridad: %d\n", proc->id, proc->priority);
    return 0;
}

persona* poppet(ColaEspera *Queue, int *index) {
    if (index == NULL || Queue->front == -1 || Queue->front > Queue->rear) {
        return NULL; // Verificar si el índice es válido y la cola no está vacía
    }

    ColaEspera beforeIndex;
    ColaEspera afterIndex;
    initialize(&beforeIndex);
    initialize(&afterIndex);

    // Separar los procesos en dos colas
    for (int i = Queue->front; i <= Queue->rear; i++) {
        if (i < *index) {
            push(Queue->data[i], &beforeIndex); // Procesos antes del índice
        } else if (i > *index) {
            push(Queue->data[i], &afterIndex); // Procesos después del índice
        }
    }
    
    // Reiniciar la cola original
    Queue->front = 0;
    Queue->rear = -1;

    // Agregar procesos de beforeIndex a la cola original
    for (int i = beforeIndex.front; i <= beforeIndex.rear; i++) {
        push(beforeIndex.data[i], Queue);
    }

    // Agregar procesos de afterIndex a la cola original
    for (int i = afterIndex.front; i <= afterIndex.rear; i++) {
        push(afterIndex.data[i], Queue);
    }

    // Retornar el proceso que estaba en el índice especificado
    persona *proc = Queue->data[*index];

    // Mover el índice frontal hacia adelante
    Queue->front++;

    // Verificar si la cola está vacía después de la operación
    if (Queue->front > Queue->rear) {
        Queue->front = Queue->rear = -1; // Reiniciar la cola si está vacía
    }
    
    return proc; // Retornar el proceso extraído
}

void display(ColaEspera *q) {
    if (q->front == -1) {
        printf("Queue is empty.\n");
    } else {
        printf("Processes in queue:\n");
        for (int i = q->front; i <= q->rear; i++) {
            printf(
            "Persona %d: Prioridad %d\n", 
                   q->data[i]->id, 
                   q->data[i]->priority
            );
        }
    }
}

ColaEspera* HaveThereSomeoneWithPriority(ColaEspera *q) { // Filterr by priority
    ColaEspera* AdminQueue =  (ColaEspera*) malloc(sizeof(ColaEspera));
    if (AdminQueue == NULL) {
        return NULL; // Manejo de error en la asignación de memoria
    }
    initialize(AdminQueue);

    // Usar un índice separado para iterar sobre la cola
    for (int i = q->front; i <= q->rear; i++) {
        persona *proc = q->data[i];
        if (proc->priority == 1) {
            push(proc, AdminQueue); // Agregar a la cola de administradores
            // Eliminar el proceso de la cola original
            // Aquí se debe usar pop para eliminar el proceso de la cola original
            poppet(q, &i); // Esto eliminará el proceso de la cola original
            i--; // Decrementar el índice para evitar saltar el siguiente proceso
        }
    }

    // Verificar si hay procesos en la cola de administradores
    if (AdminQueue->front != -1) {
        return AdminQueue;
    } else {
        free(AdminQueue); // Liberar memoria si no hay procesos
        return NULL;
    }
}
