#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include "funciones/procesos.h"
#include "Players/bot.h"

int main(int argc, char const *argv[]){
	pid_t jugadores[4]; // ID de los procesos hijos
	int padre_hijo[4][2]; // Pipes del Padre(tablero) a los hijos(jugadores)
	int hijo_padre[4][2]; // Pipes de los Hijos al Padre
	int posJugador; // Posicion del Jugador
	char entrada, salida; // variables que almacenan la entrada y salida de datos
    ssize_t nread; // valor entregado por read()
	Juego *tablero;

	/*CREO LOS 4 JUGADORES:*/
	tablero = newTablero();

	for (int i = 0; i < 4; i++) {
		//creo los Pipes para este proceso hijo
		if (pipe(padre_hijo[i]) == -1 || pipe(hijo_padre[i]) == -1) {
			perror("Error al crear los Pipes");
			exit(EXIT_FAILURE);
		}
		//creo los procesos
		if ((jugadores[i] = fork()) < 0) {
			perror("Error al crear un jugador");
			abort();
		// }else if (jugadores[posJugador] == 0) { //por ahora solo usare bots
		// 	closePipes(hijo_padre[i][LEER], padre_hijo[i][ESCRIBIR]);
		// 	printf("%d, %d\n", padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR]);
		// 	if (MainUser(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR], i +1) == -1){
		// 		printf("Error durante la ejecucion del Jugador %d --Proceso %d--\n", i+1, jugadores[i]);
		// 	}
		// 	return 0;
		} else if ( jugadores[i] == 0 ) { //estoy en proceso hijo
			closePipes(hijo_padre[i][LEER], padre_hijo[i][ESCRIBIR]);
			printf("ID YO %d, ID PADRE %d\n", getpid(), getppid());
			// printf("%d, %d\n", padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR]); // DEBUG
			if (MainBot(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR], i +1, tablero) == -1){
				printf("Error durante la ejecucion del Jugador %d --Proceso %d--\n", i+1, jugadores[i]);
				exit(1);
			}
			exit(0);
		} else { //estoy en el padre
			closePipes(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR]); //estando en el padre no se usan
		}
	}

	/*EJECUCION DEL JUEGO*/
	bool termino = false;
	while(!termino){
		salida = 0;
		for (beginIteracion(tablero); !termino && (getMov(tablero) > -1 && getMov(tablero) < 4); nextIteracion(tablero)){
			if (write(padre_hijo[getMov(tablero)][ESCRIBIR], &salida, 1) == -1){
				printf("Error al escribir al hijo %d --Proceso %d--\n", getMov(tablero) +1 , jugadores[getMov(tablero)]);
				return 1;
			}else{ //DEBUG
				printf("Padre escribe %d sobre el hijo %d --Proceso %d--\n", salida, getMov(tablero) +1, jugadores[getMov(tablero)]); 
			}
			if ( (nread = read(hijo_padre[getMov(tablero)][LEER], &entrada, 1)) == -1 ) { // LEE desde el padre
				printf("Error al leer el Pipe del jugador %d --Proceso %d--\n",  getMov(tablero) +1 , jugadores[getMov(tablero)]);
				return -1;
			}
			else if ( nread == 0 ) {
				printf("Pipe cerrado desde el jugador %d --Proceso %d--\n", getMov(tablero) +1, jugadores[getMov(tablero)]);
				termino = true;
			}
			else{
            	printf("Padre recibe del hijo %d, %d --Proceso %d--\n", getMov(tablero)+1, entrada, jugadores[getMov(tablero)]); // DEBUG
				if(entrada == 1){ //GANO
					printf("Felicidades por ganar Jugador %d!!!!\n", getMov(tablero)+1);
					termino = true;
				}
			}
		}
	}

	/*TERMINO LOS PROCESOS (JUGADORES)*/
	salida = -1;
	printf("---PARTE FINAL---\n");
	for(int i = 0; i < 4; i++){
		if ( write(padre_hijo[i][ESCRIBIR], &salida, 1) == -1){
			printf("Error al escribir sobre el jugador %d\n", i + 1);
			return 1;
		}else{ //DEBUG
			printf("Padres escribe %d sobre el hijo %d --Proceso %d--\n",salida, i+1, jugadores[i]); //DEBUG
		}

		waitpid(jugadores[i], NULL, 0); // espero a que termine el hijo
		closePipes(padre_hijo[i][ESCRIBIR], hijo_padre[i][LEER]);
		printf("Salio el Jugador %d --Proceso %d--\n", i+1, jugadores[i]); //DEBUG
	}
	freeTablero(tablero);
	puts("Adios!");
	return 0;
}
