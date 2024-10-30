/*
Alumno: Ocampo Canales Kaory Marlene
Fecha de entrega: 29 de octubre
Fecha de actualización: 29 de octubre, 20:32 hrs
Nombre del archivo: PDAejercicio2
*/

//Biblioteca de funciones del PDA

#include <stdio.h>
#include "parametrosPila.h"


// Una función de recorrido que usa el valor de pila en s y los simbolos
void recorrido (Pila *s, char simbolo){
    if (s->tope < PILA_SIZE - 1) {      //Si s apuntando al tope es menor al tamaño de la pila entonces
        s->pila[++s->tope] = simbolo;       //s que apunta a la pila va a subir una posición más donde
    }                                       //estara el simbolo
}


//Función para desapilar, usa el valor de la Pila en s
char despila(Pila *s) {
    if (!esVacio(s)) {      //Si la pila es distinta de vacío en la posición s, entonces
        return s->pila[s->tope--];      //Regresar la posición de s en la pila menos el
    }                                   //simbolo que este en el tope
    return '\0';        // Retornar un carácter nulo si la pila está vacía
}


//Función para imprimir el proceso de pila
void printPila(Pila *s) {
    if (esVacio(s)) { // Para imprimir un espacio vacio
        printf("Pila: (vacía)\n");
        return;
    }
    printf("Pila: ");
    for (int i = 0; i <= s->tope; i++) {        //Imprime el proceso de la Pila
        printf("%c ", s->pila[i]);
    }
    printf("\n");
}


void transicion(char *estadoActual, char cadena, Pila *pila) {
    printf("Estado actual: %c, Entrada: %c\n", *estadoActual, cadena);
    
    if (*estadoActual == '2') {     //En caso de estado q2
        if (cadena == 'a') {        //Si la cadena es a
            if (pila == 'A')        //Y tenemos A en la pila entonces apilamos A y seguimos en q2
            {
                recorrido(pila, 'A');
                *estadoActual == '2';
            } else if (pila == 'B')     //Si tenemos B en la pila se aplica epsilon, por lo que se desapila y q1
            {
                despila(pila);
                *estadoActual == '1';
            }
        } else if (cadena == 'e') {     // Si tenemos e en la cadena y la cadena es vacia, se desapila
            if (!esVacio(pila)) {
                despila(pila);
            }else if (pila == '#')      //pero si nos topamos con el fondo agregamos una B y pasamos a q3
            {
                recorrido(pila, 'B');
                *estadoActual == '3';
            }
            
        }
    } else if (*estadoActual == '1') {      //Estado q1
        if (cadena == 'e') {        //Si la cadena es e desapila y pasamos a q2
            if (!esVacio(pila)) {
                despila(pila);
                *estadoActual == '2';
            }
        }else if (cadena == 'a')        //Si la cadena es a
        {
            if (pila == 'B')        //Y tenemos B en la pila, apilamos A y pasamos a q2
            {
                recorrido(pila, 'A');
                *estadoActual == '2';
            }else if (pila == 'A')      //Pero si tenemos A desapila y pasamos a q3
            {
                despila(pila);
                *estadoActual == '3';
            }
        }
        
    } else if (*estadoActual == '3') {      //Estado q3
        if (cadena == 'a') {        //Si en la cadena hay a y tiene B entonces se apila A y pasamos a q1
            if (pila == 'B') {
                recorrido(pila, 'A');
                *estadoActual == '1';
            }
        }else if (cadena == 'e')        //Pero si es e y tenemos B, se apila otra B y asamos a q1
        {
            if (pila == 'B')
            {
                recorrido(pila, 'B');
                *estadoActual == '1';
            }
            
        }
        
    }

    printPila(pila);        //Imprimir el estado de la pila después de la transición
}


int validaCadena(const char *cadena) {
    Pila pila;
    inicioStack(&pila);
    char estadoActual = '2';        //Estado inicial
    char cadenaFinal[101];      //Asegurarse de que hay espacio para el '\0'

    // Concatenar el fin de cadena
    snprintf(cadenaFinal, sizeof(cadenaFinal), "%s#", cadena);

    for (size_t i = 0; i < strlen(cadenaFinal); i++) {      //Usamos size_t para seguir un indice
        char c = cadenaFinal[i]; 

        // Uso de transiciones
        transicion(&estadoActual, c, &pila);
        
        // Cambio de estados
        if (esVacio(&pila) && estadoActual == '2') {
            estadoActual = '3'; // Transición a q3 si la pila está vacía
        }
    }

    // Comprobar si el estado final es aceptado
    return estadoActual == '3' && esVacio(&pila);
}
