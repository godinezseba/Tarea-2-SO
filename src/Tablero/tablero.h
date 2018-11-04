typedef struct Ttablero{
    char *mesa; // tablero
    char signo; // creciente(1) o decreciente(-1)
    int largo; // largo tablero
    int mov; // variable para comenzar la iteracion de los jugadores
    int *players;// agregar jugadores
    int key1, key2, key3; // keys de la memoria compartida
}Juego;

Juego *newTablero();
/******** Funcion: changeLado ********************
Descripcion: cambia de sentido el tablero
Parametros:
tablero: tablero a modificar
Retorno: nada
************************************************/
void changeLado(Juego *tablero);

void printTablero(Juego *tablero);

void freeTablero(Juego *tablero);

void nextIteracion(Juego *tablero);

void beginIteracion(Juego *tablero);

int getMov(Juego *tablero);
/******** Funcion: changeSentido ********************
Descripcion: cambia el sentido del tablero
Parametros:
tablero: tablero a modificar
Retorno: nada
************************************************/
void changeSentido(Juego *tablero);

void retrocedenPlayers(Juego *tablero, int jugador);

void pierdeSiguiente(Juego *);

void retrocedenAll(Juego *);

void avanzaBlanca(Juego *, int);

void changeMenor(Juego *, int);

void changeMayor(Juego *, int);
