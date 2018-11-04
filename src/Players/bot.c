#include <stdio.h>
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../funciones/procesos.h"
#include "bot.h"

int movimientoBot(const int num_player, Juego *tablero){
    int dado; // resultado del dado
    int opcion = 1; //
    dado = DadoChoice();
    printf("-----Jugador %d, obtuvo un %d ", num_player, dado);
    tablero->players[num_player-1] += dado;
    printf(", Posicion: %d *** -----\n", tablero->players[num_player-1]);

    switch(tablero ->  mesa[tablero->players[num_player-1]-1]){
        case '1':
            printf("-Caiste en un ?:\n");   
            opcion = Casilla1Choice();
            switch (opcion) {
                case 1:
                    printf("Retrocedes una cuadricula!\n");
                    tablero->players[num_player-1] += -1;
                    break;
                case 2:
                    printf("El resto retrocede una cuadricula!\n");
                    retrocedenPlayers(tablero, num_player);
                    break;
                case 3:
                    printf("Avanzas una cuadricula!\n");
                    tablero->players[num_player-1] += 1;
                    break;
                case 4:
                    printf("El siguiente pierde su turno!\n");
                    pierdeSiguiente(tablero);
                    break;                  
                case 5:
                    printf("Cambia el sentido de los turnos!\n");
                    changeSentido(tablero);
                    break;
                default: // a veces no devuelve nada 
                    break;
            }
            break;
        case '2':
            printf("-Caiste en un \?\?:\n");
            opcion = Casilla2Choice(dado);
            switch (opcion) { // todo se puede hacer con funciones del tablero
                case 1:
                    printf("Todos retroceden 2 cuadriculas!\n");
                    retrocedenAll(tablero);
                    break;
                case 2:
                    printf("El resto avanza hasta su proxima cuadricula blanca!\n");
                    avanzaBlanca(tablero, num_player);
                    break;
                case 3:
                    printf("Cambias con el ultimo!\n");
                    changeMenor(tablero, num_player);
                    break;
                case 4:
                    printf("Cambias con el primero!\n");
                    changeMayor(tablero, num_player);
                    break;
                case 5:
                    printf("Cambia el sentido del tablero!\n");
                    changeLado(tablero);
                    break;                    
                default:
                    break;
            }
            break;
        default:
            break;
    }
    if(tablero->players[num_player-1] >= tablero->largo){ //GANE
        tablero->players[num_player-1] = 29;
        return 1;
    }else{ 
        return 0;
    }
}

int MainBot(const int LPipe, const int EPipe, const int num_player, Juego *tablero) {
    // DEBUG
    // printf("soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
    // printf("Soy el bot %d!\n", num_player);
    bool termino = false; //condicion de termino del ciclo
    ssize_t nread; // valor entregado por read()
    char entrada, salida;
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
            // printf("Hijo %d recibe %d --Proceso %d--\n", num_player, entrada, getpid()); // DEBUG
            switch (entrada) { 
                case -1: // termino el juego
                    termino = true;
                    break;
                case 0: // mi turno
                    salida = movimientoBot(num_player, tablero);
                    if (write(EPipe, &salida, 1) == -1){
                        printf("Error al escribir al padre --Proceso %d--\n", getpid());
                        return -1;
                    }
                    // else{ //DEBUG
                    //     printf("Hijo %d escribe %d sobre el padre --Proceso %d--\n", num_player,salida, getpid()); 
                    // }
                    break;
                //aca iran los efectos
                default: //error en la entrada
                    printf("ERROR EN LA LECTURA DE DATOS!");
                    printf("Hijo %d recibe %d --Proceso %d--\n", num_player, entrada, getpid());
                    return -1;
            }
        }
    }
    // printf("--termino el proceso %d--\n", getpid()); //DEBUG
    closePipes(LPipe, EPipe);
    return 0;
}
