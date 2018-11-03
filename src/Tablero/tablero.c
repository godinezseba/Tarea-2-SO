#include "tablero.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

Juego* newTablero(){
    int i;
    char temp[] = {'0', '0', '1', '0', '1', '0', '1', '0', '0', '0', '0',
                    '0', '1', '0', '1', '0', '2', '0', '0', '0', '0', '1',
                    '2', '1', '2', '1', '2', '1', '0'};
    Juego *tablero;
    int shm_id, shm_id2, shm_id3; // para la memoria compartida
    key_t mem_key, mem_key2, mem_key3;

    mem_key = ftok(".", 'a');
    mem_key2 = ftok(".", 'b');
    mem_key3 = ftok(".", 'c');
    //para la estructura
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
    // valores de la estructura
    tablero -> largo = 29;
    tablero -> signo = 1;
    // para el tablero
    shm_id2 = shmget(mem_key2, sizeof(char)*29, IPC_CREAT|0666);
    if(shm_id2 < 0){
        printf("Error al crear el tablero! (dynamic memory key, array tablero)\n");
        exit(1);
    }
    tablero -> mesa = (char *)shmat(shm_id2, (void *)0, 0);
    if(tablero->mesa == (char *)-1){
        printf("Error al crear el tablero! (array tablero)\n");
        exit(1);
    }
    for(i = 0; i < 29; i++){
        tablero -> mesa[i] = temp[i];
    }
    // para los jugadores
    shm_id3 = shmget(mem_key3, sizeof(int)*4, IPC_CREAT|0666);
    if(shm_id3 < 0){
        printf("Error al crear el tablero! (dynamic memory key, array jugadores)\n");
        exit(1);
    }
    tablero -> players = (int *)shmat(shm_id3, (void *)0, 0);
    if(tablero -> players == (int *)-1){
        printf("Error al crear el tablero! (array jugadores)\n");
        exit(1);
    }
    for(i = 0; i < 4; i++){
        tablero -> players[i] = 0;
    }
    tablero->key1 = shm_id;
    tablero->key2 = shm_id2;
    tablero->key3 = shm_id3;
    return tablero;
}

void changeLado(Juego *tablero){
    int i;
    char temp;
    for(i = 0; i < tablero->largo/2 ; i++){
        temp = tablero->mesa[i];
        tablero->mesa[i] = tablero->mesa[tablero->largo-i-1];
        tablero->mesa[tablero->largo-i-1] = temp;
        if(tablero->mesa[i] != '0') tablero->mesa[i] = (tablero->mesa[i] == '1' ? '2' : '1');
        if(tablero->mesa[tablero->largo-i-1] != '0') tablero->mesa[tablero->largo-i-1] = (tablero->mesa[tablero->largo-i-1] == '1' ? '2' : '1');
    }
    if(tablero->mesa[i] != '0') tablero->mesa[i] = (tablero->mesa[i] == '1' ? '2' : '1'); // para el de al medio
    // aqui cambio lo de los jugadores
}

void printTablero(Juego *tablero){
    int i;
    printf("INICIO |");
    for(i = 1; i < tablero->largo - 1; i++){
        if(tablero ->mesa[i] != 0) printf(" %s |", (tablero->mesa[i] == '1'? "?" : "??"));
        else printf(" %c |", '0');
    }
    printf(" FINAL");
    printf("\n");
    // AGREGAR A LOS JUGADORES
}

void freeTablero(Juego *tablero){
    // shmdt(tablero->mesa);
    // shmdt(tablero->players);
    // shmdt(tablero);
    shmctl(tablero->key3, IPC_RMID, NULL);
    shmctl(tablero->key2, IPC_RMID, NULL);
    shmctl(tablero->key1, IPC_RMID, NULL);
}

void nextIteracion(Juego *tablero){
    tablero -> mov = tablero -> mov + tablero -> signo;
}

void beginIteracion(Juego *tablero){
    if(tablero -> signo == 1){
        tablero -> mov = 0;
    }
    else{
        tablero -> mov = 3;
    }
    
}

int getMov(Juego *tablero){
    return tablero -> mov;
}

void changeSentido(Juego *tablero){
    tablero -> signo = tablero -> signo * -1;
}
