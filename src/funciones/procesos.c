#include <stdio.h>
#include "procesos.h"
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
void closePipes(const int read, const int write){
    if ( close(read) == -1 || close(write) == -1 ) { 
        perror("No se pudieron cerrar los Pipes\n");
        exit(EXIT_FAILURE);
    }
}

int DadoChoice(){
    return (rand() % 6) + 1 ;
}

int Casilla1Choice(){
    return (rand() % 5) + 1; 
}

int Casilla2Choice(int numero){
    int opcion;
    opcion = ((rand() * numero) % 10) + 1;

    if (1 <= opcion && opcion <= 3) { // todos retroceden 2
        return 1;
    }
    else if(4 <= opcion && opcion <= 5) { // los demas avanzan hasta la proxima blanca
        return 2;
    }
    else if(6 <= opcion && opcion <= 7) { // cambia con el que va ultimo
        return 3;
    }
    else if(8 <= opcion && opcion <= 9) { // cambia con el que va primero
        return 4;
    }
    else {
        return 5;
    }
}