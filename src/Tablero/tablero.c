#include "tablero.h"
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include <stdio.h>

Juego* newTablero(){
    int i;
    char temp[] = {'0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0',
                    '0', '1', '0', '1', '0', '2', '0', '0', '0', '0', '1',
                    '2', '1', '2', '1', '2', '1', '0'};
    Juego *tablero;
    int shm_id; // para la memoria compartida
    int shm_id2;
    key_t mem_key;
    key_t mem_key2;

    mem_key = ftok(".", 'a');
    mem_key2 = ftok(".", 'b');
    
    shm_id = shmget(mem_key, sizeof(Juego), IPC_CREAT|0666);
    if(shm_id < 0){
        printf("Error al crear el tablero! (dynamic memory key)\n");
        exit(1);
    }
    tablero = (Juego *)shmat(shm_id, (void *)0, 0);
    if(tablero == (Juego *)-1){
        printf("Error al crear el tablero!\n");
        exit(1);
    }
    tablero -> largo = 29;
    tablero -> signo = 1;
    // para el tablero
    shm_id2 = shmget(mem_key2, sizeof(char)*29, IPC_CREAT|0666);
    if(shm_id2 < 0){
        printf("Error al crear el tablero! (dynamic memory key, array)\n");
        exit(1);
    }
    tablero -> mesa = (char *)shmat(shm_id2, (void *)0, 0);
    if(tablero->mesa == (char *)-1){
        printf("Error al crear el tablero! (array)\n");
        exit(1);
    }
    
    for(i = 0; i < 29; i++){
        tablero -> mesa[i] = temp[i];
    }
    // AQUI CREO A LOS JUGADORES
    return tablero;
}

void changeLado(Juego *tablero){
    int i;
    char temp;
    for(i = 0; i < tablero->largo/2; i++){
        temp = tablero->mesa[i];
        tablero->mesa[i] = tablero->mesa[tablero->largo-i-1];
        tablero->mesa[tablero->largo-i-1] = temp;
    }
    // aqui cambio lo de los jugadores
}

void printTablero(Juego *tablero){
    int i;
    printf("INICIO |");
    for(i = 1; i < tablero->largo - 1; i++){
        printf(" %c |", tablero->mesa[i]);
    }
    printf(" FINAL");
    printf("\n");
}

void freeTablero(Juego *tablero){
    shmdt(tablero->mesa);
    shmdt(tablero);
}