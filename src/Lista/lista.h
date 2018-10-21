#include <stdlib.h>

// *****************************
// DEFINICION DE LISTAS ENLAZADAS
// *****************************

// Estructura del elemento que almacena el nodo (VA A CAMBIAR)
typedef struct elemento{
    char *nombre;
    int tipo;
} elemento;
// Estructura de los nodos:
typedef struct nodo {
    void * info; // el elemento en sí
    struct nodo *sig; // puntero autoreferencial al proximo nodo
    struct nodo *ant; // puntero referente al proximo nodo
} tNodo;
// Estructura de la lista:
typedef struct Lista{
    tNodo *head; //Primer elemento
    tNodo *tail; //Ultimo elemento
    tNodo *curr; //Elemento actual
    long int listSize; //Tamaño de la lista
    long int pos; // Posición actual en la lista
} tLista;

/******** Funcion: crearLista ********************
Descripcion: Crea una lista
Parametros:
nada
Retorno: puntero a la nueva lista
************************************************/
tLista *crearLista();
/******** Funcion: clearL ********************
Descripcion: elimina la lista y elimina todos sus punteros
Parametros:
l el puntero de una lista
Retorno: nada
************************************************/
void clearL(tLista *l);
/******** Funcion: insert ********************
Descripcion: inserta un elemento en una lista l, en la posicion actual
Parametros:
l el puntero de una lista
item elemento a guardar
Retorno: 1 -> se guardo bien; 0 -> algo salio mal (no se guardo)
************************************************/
int insert(tLista *l, void *item);
/******** Funcion: append ********************
Descripcion: agrega un elemento al final de la lista
Parametros:
l el puntero de una lista
item elemento a guardar
Retorno: 1 -> se guardo bien; 0 -> algo salio mal (no se guardo)
************************************************/
int append(tLista *l, void *item);
/******** Funcion: lremove ********************
Descripcion: elimina el elemento actual de la lista
Parametros:
l el puntero de una lista
Retorno: el elemento que se elimino
************************************************/
void *lremove(tLista *l);

void *pop(tLista *l);
/******** Funcion: moveToStart ********************
Descripcion: mueve el cursor de la lista al inicio
Parametros:
l el puntero de una lista
Retorno: nada
************************************************/
void moveToStart(tLista* l);
/******** Funcion: next ********************
Descripcion: se mueve una posicion adelante
Parametros:
l el puntero de una lista
Retorno: nada
************************************************/
void next(tLista *l);
/******** Funcion: length ********************
Descripcion: entrega el largo de la lista
Parametros:
l el puntero de una lista
Retorno: un numero que representa el largo de la lista
************************************************/
long int length(tLista *l);
/******** Funcion: currPos ********************
Descripcion: entrega la posicion actual de la lista
Parametros:
l el puntero de una lista
Retorno: un numero que representa la posicion actual de la lista
************************************************/
long int currPos(tLista *l);
/******** Funcion: getValue ********************
Descripcion: entrega el elemento actual de la lista
Parametros:
l el puntero de una lista
Retorno: un elemento (el actual)
************************************************/
void *getValue(tLista *l);
/******** Funcion: getValuen *******************
Descripcion: entrega el elemento en la posicion dada
Parametros:
l el puntero de una lista
pos posicion que se quiere obtener el dato
Retorno: un elemento
************************************************/
void *getValuen(tLista *l, int pos);
/******** Funcion: getValue ********************
Descripcion: cambia el valor del elemento del nodo actual
Parametros:
l el puntero de una lista
new un elemento (el nuevo)
Retorno: nada
************************************************/
void change(tLista *l,void *new);
/******** Funcion: getValue ********************
Descripcion: Printea la lista
Parametros:
l el puntero de una lista
Retorno: nada
************************************************/
void printL(tLista *l);
