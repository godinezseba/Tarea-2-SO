#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  

#define LEER 0
#define ESCRIBIR 1
#define LARGO_TABLERO 29
static short int tablero[] = {0,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0,2,0,0,0,0,1,2,1,2,1,2,1,0};

/******** Funcion: closePipes ********************
Descripcion: Cerrar un par de Pipes ingresados
Parametros:
const int read - Pipe de Lectura que se cierra
const int write - Pipe de Escritura que se cierra
Retorno: nada
************************************************/
void closePipes(const int read, const int write);

/******** Funcion: DadoChoice ********************
Descripcion: Cerrar un par de Pipes ingresados
Parametros:
const int read - Pipe de Lectura que se cierra
const int write - Pipe de Escritura que se cierra
Retorno: nada
************************************************/
int DadoChoice();