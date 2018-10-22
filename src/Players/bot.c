#include "../funciones/procesos.h"
#include "bot.h"
#include <stdbool.h>


int MainBot(const int LPipe, const int EPipe, const int num_player) {
    // DEBUG
    // printf("soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
    // printf("Soy el bot %d!\n", num_player);
    int posicion = 0; // posicion de mi personaje en el tablero
    bool termino = false; //condicion de termino del ciclo
    ssize_t nread; // valor entregado por read()
    char entrada, salida;
    int dado; // resultado del dado

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
                    posicion += dado;
                    if(posicion == LARGO_TABLERO -1){ //GANE
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
