#include <stdio.h>
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <time.h>
#include "funciones/procesos.h"

int main(int argc, char const *argv[]){
	pid_t jugadores[4]; // ID de los procesos hijos
	int padre_hijo[4][2]; // Pipes del Padre(tablero) a los hijos(jugadores)
	int hijo_padre[4][2]; // Pipes de los Hijos al Padre
	int posJugador; // Posicion del Jugador

	//CREO los 4 jugadores:
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
		// 	char *args[]  = {"./src/Players/user", NULL};
		// 	execvp(args[0], args);
		}else if (jugadores[i] == 0) { //estoy en proceso hijo
			closePipes(hijo_padre[i][LEER], padre_hijo[i][ESCRIBIR]);
			//ejecucion player
			char *args[]  = {"./src/Players/bot", NULL};
			execvp(args[0], args);
		}else { //estoy en el padre
			closePipes(padre_hijo[i][LEER], hijo_padre[i][ESCRIBIR]); //estando en el padre no se usan
		}
	}

	waitpid(jugadores[3], 0, 0);
	puts("Soy el Padre!");
	
	return 0;
}
