#include <stdio.h>
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <time.h>
#include "../funciones/procesos.h"

int main(int argc, char const *argv[]){
    printf("soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
    puts("Soy un bot!");
    return 0;
}
