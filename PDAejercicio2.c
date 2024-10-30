/*
Alumno: Ocampo Canales Kaory Marlene
Fecha de entrega: 29 de octubre
Fecha de actualización: 29 de octubre, 21:17 hrs
Nombre del archivo: PDAejercicio2
*/

#include <stdio.h>
#include "FuncionesPDA.h"

// main que ejecute el programa
int main() {
    char cadena[100];

    printf("Ingresa una cadena (solo 'a' y 'e'): ");
    scanf("%99s", cadena);      //Limitar la entrada para evitar desbordamiento

    if (validaCadena(cadena)) {
        printf("La cadena es válida.\n");
    } else {
        printf("La cadena no es válida.\n");
    }

    return 0;
}



/*
NOTA IMPORTANTE: La logica estaba planeada para ser a partir de dos bibliotecas que fueran llamadas al principal
pero al momento de llamar las librerias, al ser independientes una de la otra no definia ni el valor ni el tipo
de parametro que era nuestra Pila/Stack, lo que afectaba por efecto domino, al resto del codigo, hubo un cambio en
el nombre de los parametros pensando (erroneamente) que ese podía ser el problema del codigo, pero al releer los
errores que saltaban note que los parametros se perdian entre las bibliotecas, así que la solución fue poner tanto
funciones como parametros en una sola biblioteca que es llamada a nuestro main, todo por motivos de limpieza y
lectura eficaz del codigo.
*/