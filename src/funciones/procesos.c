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