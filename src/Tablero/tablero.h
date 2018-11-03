typedef struct Ttablero{
    char *mesa; // tablero
    char signo; // creciente(1) o decreciente(-1)
    int largo; // largo tablero
    int mov; // variable para comenzar la iteracion de los jugadores
    // agregar jugadores
}Juego;

Juego *newTablero();

void changeLado(Juego *tablero);

void printTablero(Juego *tablero);

void freeTablero(Juego *tablero);

void nextIteracion(Juego *tablero);

void beginIteracion(Juego *tablero);

int getMov(Juego *tablero);

void changeSentido(Juego *tablero);