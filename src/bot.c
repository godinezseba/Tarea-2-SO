#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h>

int main(int argc, char const *argv[]){
    printf("soy el proceso de PID %d y mi padre tiene %d de PID.\n", getpid(), getppid());
    puts("Soy un bot!");
    return 0;
}
