#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  

#define LEER 0
#define ESCRIBIR 1

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