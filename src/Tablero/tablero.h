#include <stdlib.h>

typedef struct Ttablero{
    char *mesa; // tablero
    char signo; // creciente(1) o decreciente(-1)
    int largo; // largo tablero
    // agregar jugadores
}Juego;

Juego *newTablero();
void changeLado(Juego *tablero);
void printTablero(Juego *tablero);
void freeTablero(Juego *tablero);
