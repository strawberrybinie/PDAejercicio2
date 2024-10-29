
//Biblioteca que define parametros para la pila

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PILA_SIZE 100

typedef struct {
    char pila[PILA_SIZE]; // Tamaño de la pila
    int tope; // Inicio o tope de la pila
} Pila;

void inicioPila(Pila *s) {         //Indica el inicio de nuestra pila, de donde partimos
    s->tope = -1;       //Indice de nuestro tope en la pila
}

int esVacio(Pila *s) {      //Lee si nuestra pila esta vacía
    return s->tope == -1;       //Regresa nuestro indice en la posición anterior (si es que esta no esta vacia)
}