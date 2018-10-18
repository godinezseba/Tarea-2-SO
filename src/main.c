#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 

int main(int argc, char const *argv[]){
	pid_t pids[4];
	int i;
	//CREO los 4 jugadores:
	for(i = 0; i < 4; i++){
		if ((pids[i] = fork()) < 0) {
			perror("Error al crear un jugador");
			abort();
		// }else if (pids[1] == 0) { //por ahora solo usare bots
		// 	char *args[]  = {"./src/user", NULL};
		// 	execvp(args[0], args);
		// 	exit(0);
		}else if (pids[i] == 0) {
			char *args[]  = {"./src/bot", NULL};
			execvp(args[0], args);
			// exit(0);
		}
	}
	wait(NULL);
	puts("Soy el Padre!");
	
	return 0;
}
