/*
Alumno: Ocampo Canales Kaory Marlene
Fecha de entrega: 29 de octubre
Fecha de actualización: 29 de octubre, 20:32 hrs
Nombre del archivo: PDAejercicio2
*/

//Biblioteca de funciones del PDA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

// Define nuestros parametros
typedef struct {
    char stack[STACK_SIZE]; // Tamaño de la pila
    int top; // Indice de nuestro inicio
} Stack;

// Funciones para la pila
void inicioStack(Stack *s) {    //Indica el inicio de nuestra pila, de donde partimos
    s->top = -1;        //Indice de nuestro tope en la pila
}

// Función para una pila vacia
int esVacio(Stack *s) {     //Lee si nuestra pila esta vacía
    return s->top == -1;        //Regresa nuestro indice en la posición anterior (si es que esta no esta vacia)
}

//Función de apilar
void push(Stack *s, char item) {
    if (s->top < STACK_SIZE - 1) {
        s->stack[++s->top] = item;
    }
}

//Función para sacar de la pila
char pop(Stack *s) {
    if (!esVacio(s)) {
        return s->stack[s->top--];
    }
    return '\0'; // Retornar un carácter nulo si la pila está vacía
}

// Función para imprimir el proceso de la pila
void printPila(Stack *s) {
    if (esVacio(s)) { // Para imprimir un espacio vacio
        printf("Pila: (vacía)\n");
        return;
    }
    printf("Pila: ");
    for (int i = 0; i <= s->top; i++) { // Imprime es proceso de la Pila
        printf("%c ", s->stack[i]);
    }
    printf("\n");
}

// Función de transición
void transicion(char *estadoActual, char cadena, Stack *stack) {
    printf("Estado actual: %c, Entrada: %c\n", *estadoActual, cadena);
    
    if (*estadoActual == '2') { // Estado q2
        if (cadena == 'a') { // Si la cadena es a, se apila A
            push(stack, 'A');
        } else if (cadena == 'e') { // Si tenemos epsilon, se desapila
            if (!esVacio(stack)) {
                pop(stack);
            }
        }
    } else if (*estadoActual == '1') { // Estado q1
        if (cadena == 'e') { // Si la cadena es e, desapila
            if (!esVacio(stack)) {
                pop(stack); 
            }
        }
    } else if (*estadoActual == '3') { // Estado q3
        if (cadena == 'a') {
            if (!esVacio(stack)) { // Si es vacio, se desapila y se apila B
                pop(stack);
                push(stack, 'B');
            }
        }
    }

    printPila(stack); // Imprimir el estado de la pila después de la transición
}

// Función principal para validar la cadena
int validaCadena(const char *cadena) {
    Stack stack;
    inicioStack(&stack);
    char estadoActual = '2'; // Estado inicial
    char cadenaFinal[101];  // Asegurarse de que hay espacio para el '\0'

    // Concatenar el fin de cadena
    snprintf(cadenaFinal, sizeof(cadenaFinal), "%s#", cadena);

    for (size_t i = 0; i < strlen(cadenaFinal); i++) { // Usamos size_t para seguir un indice
        char c = cadenaFinal[i]; 

        // Uso de transiciones
        transicion(&estadoActual, c, &stack);
        
        // Cambio de estados
        if (esVacio(&stack) && estadoActual == '2') {
            estadoActual = '3'; // Transición a q3 si la pila está vacía
        }
    }

    // Comprobar si el estado final es aceptado
    return estadoActual == '3' && esVacio(&stack);
}

