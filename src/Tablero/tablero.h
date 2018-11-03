typedef struct Ttablero{
    char *mesa; // tablero
    char signo; // creciente(1) o decreciente(-1)
    int largo; // largo tablero
    int mov; // variable para comenzar la iteracion de los jugadores
    int *players;// agregar jugadores
    int key1, key2, key3; // keys de la memoria compartida
}Juego;

Juego *newTablero();

void changeLado(Juego *tablero);

void printTablero(Juego *tablero);

void freeTablero(Juego *tablero);

void nextIteracion(Juego *tablero);

void beginIteracion(Juego *tablero);

int getMov(Juego *tablero);

void changeSentido(Juego *tablero);