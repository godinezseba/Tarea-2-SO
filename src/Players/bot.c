#include <stdio.h>
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../funciones/procesos.h"
#include "bot.h"

int movimientoBot(){
    
}

int MainBot(const int LPipe, const int EPipe, const int num_player, Juego *tablero) {
    // DEBUG
    // printf("soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
    // printf("Soy el bot %d!\n", num_player);
    int posicion = 0; // posicion de mi personaje en el tablero
    bool termino = false; //condicion de termino del ciclo
    ssize_t nread; // valor entregado por read()
    char entrada, salida;
    int dado; // resultado del dado
	time_t t;
    srand( (unsigned) (((unsigned) (time(&t)) % (num_player + EPipe)) * (LPipe - getpid())) ); //genero la base para los numeros aleatorios

    while (!termino) {
        if ( (nread = read(LPipe, &entrada, 1)) == -1 ) { // LEE desde el padre
            printf("Error al leer el Pipe en el jugador %d --Proceso %d--\n", num_player, getpid());
            return -1;
        }
        else if ( nread == 0 ) {
            printf("Pipe cerrado desde el Padre al jugador %d --Proceso %d--\n", num_player, getpid());
            termino = true;
        }
        else { // Decido a partir de la entrada
            printf("Hijo %d recibe %d --Proceso %d--\n", num_player, entrada, getpid()); // DEBUG
            switch (entrada) { 
                case -1: // termino el juego
                    termino = true;
                    break;
                case 0: // mi turno
                    dado = DadoChoice();
                    printf("***Jugador %d, obtuvo %d\n", num_player, dado); //DEBUG
                    posicion += dado;
                    printf("***Posicion: %d\n", posicion);
                    if(posicion >= tablero->largo - 1){ //GANE
                        salida = 1;
                    }else{ // por ahora otro caso
                        salida = 0;
                    }
                    if (write(EPipe, &salida, 1) == -1){
                        printf("Error al escribir al padre --Proceso %d--\n", getpid());
                        return -1;
                    }else{ //DEBUG
                        printf("Hijo %d escribe %d sobre el padre --Proceso %d--\n", num_player,salida, getpid()); 
                    }
                    break;
                //aca iran los efectos
                default: //error en la entrada
                    printf("ERROR EN LA LECTURA DE DATOS!");
                    printf("Hijo %d recibe %d --Proceso %d--\n", num_player, entrada, getpid());
                    return -1;
            }
        }
    }
    printf("--termino el proceso %d--\n", getpid()); //DEBUG
    closePipes(LPipe, EPipe);
    return 0;
}
