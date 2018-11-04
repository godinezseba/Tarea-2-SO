#include "tablero.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
        tablero -> players[i] = 1;
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
    for(i = 0; i < 4; i++) tablero->players[i] = 29 - tablero -> players[i] +1;
}

void printTablero(Juego *tablero){
    int i;
    printf("\n             =========================== Tablero ===========================\n");
    printf("   1   |");
    for(i = 1; i < tablero->largo - 1; i++){
        printf(" %d%s|", i +1, (i+1 > 9 ? " ": "  "));
    }
    printf(" 29\n");
    printf("INICIO |");
    for(i = 1; i < tablero->largo - 1; i++){
        if(tablero ->mesa[i] != '0') printf(" %s |", (tablero->mesa[i] == '1'? "? " : "??"));
        else printf(" %s |", "  ");
    }
    printf(" FINAL\n");
    for(i = 0; i < tablero->largo; i++){
        //player 1
        if(tablero -> players[0] == i +1) printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET, (i == 0 || i == 28)? " 1" : "1");
        else printf("%s", (i == 0)? "  " : " ");
        //player 2
        printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET, (tablero -> players[1] == i +1)? "2" : " ");
        //player 3
        printf(ANSI_COLOR_YELLOW  "%s" ANSI_COLOR_RESET, (tablero -> players[2] == i +1)? "3" : " ");
        //player 4
        if(tablero -> players[3] == i +1){
            if (i == 0) {
                printf(ANSI_COLOR_BLUE "4  " ANSI_COLOR_RESET "|");
            }
            else if(i == 28) {
                printf(ANSI_COLOR_BLUE  "4" ANSI_COLOR_RESET "\n");
            }
            else {
                printf(ANSI_COLOR_BLUE  "4" ANSI_COLOR_RESET "|");
            }
        }
        else{
            if (i == 0) {
                printf("   |");
            }
            else if(i == 28) {
                printf("\n");
            }
            else {
                printf(" |");
            }
            
        } 
    }
    printf("Jugador 1: %d; ", tablero->players[0]);
    printf("Jugador 2: %d; ", tablero->players[1]);
    printf("Jugador 3: %d; ", tablero->players[2]);
    printf("Jugador 4: %d\n", tablero->players[3]);
    printf("             ===============================================================\n");
    printf("\n");
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

void retrocedenPlayers(Juego* tablero, int jugador){
    int i;
    for(i = 0; i < 4; i++){
        if(i != jugador -1)
            tablero->players[i] += (tablero->players[i] == 1 ? 0 : -1);
    }
}

void pierdeSiguiente(Juego *tablero){ //REVISAR
    tablero -> mov = tablero -> mov + tablero -> signo;
    if(getMov(tablero) == -1 || getMov(tablero) == 4){
        if(getMov(tablero) == -1) tablero -> mov = 3;
        else tablero -> mov = 0;
    }
    // printf("!!!!!!DEBUG MOV: %d\n", tablero ->mov); // DEBUG
}

void retrocedenAll(Juego *tablero){
    int i;
    for(i = 0; i < 4; i++){
        tablero->players[i] += -2;
        if (tablero->players[i] < 1)
            tablero->players[i] = 1;
    }
}

int hastaDonde(Juego *tablero, int posicion){
    int i;
    for(i = posicion; i < 28; i++){
        if(tablero -> mesa[i] == '0') return i +1;
    }
    return -1;
}

void avanzaBlanca(Juego *tablero, int jugador){
    int i;
    int avanza; //hasta donde se mueve
    for(i = 0; i < 4; i++){
        if (i != jugador -1) {
            avanza = hastaDonde(tablero, tablero ->players[i]);
            if(avanza != -1){
                tablero ->players[i] = avanza;
            }
        }
    }
}

void changeMenor(Juego *tablero, int jugador){
    int i;
    int menor = 100;
    int jugador2;
    for(i = 0; i < 4; i++){
        if(tablero -> players[i] < menor){
            menor = tablero -> players[i];
            jugador2 = i;
        }
    }
    tablero -> players[jugador2] = tablero -> players[jugador-1];
    tablero -> players[jugador-1] = menor;
}

void changeMayor(Juego *tablero, int jugador){
    int i;
    int max = -1;
    int jugador2;
    for(i = 0; i < 4; i++){
        if(tablero -> players[i] > max){
            max = tablero -> players[i];
            jugador2 = i;
        }
    }
    tablero -> players[jugador2] = tablero -> players[jugador-1];
    tablero -> players[jugador-1] = max;
}
