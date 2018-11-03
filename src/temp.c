#include "Tablero/tablero.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    Juego *tablero = newTablero();
    printTablero(tablero);
    changeLado(tablero);
    printTablero(tablero);
    freeTablero(tablero);
    printTablero(tablero);
    return 0;
}
