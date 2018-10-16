#include "lista.h"
#include <stdio.h>

tLista *crearLista(){
	tLista* nueva = (tLista *) malloc(sizeof(tLista));
	tNodo* dummy = (tNodo *)malloc(sizeof(tNodo));

	dummy -> sig = NULL;
	dummy -> ant = NULL;
	nueva -> head = dummy;
	nueva -> tail = dummy;
	nueva -> curr = dummy;
	nueva -> listSize = 0;
	nueva -> pos = 0;
	return nueva;
}

void clearL(tLista *l){
	int i;
	tNodo *aux2, *aux;
	aux = l->head->sig;
	for(i =0; i < l->listSize ;i++){
		aux2 = aux->sig;
		// AGREGAR UN FREE PARA EL CONTENIDO
		free((void *)aux);
		aux = aux2;
	}
	free((void *)l->head);
	free((void *)l);
}

int insert(tLista *l, void *item){
	tNodo *aux;

	aux = l->curr->sig;
	l->curr->sig = (tNodo *)malloc(sizeof(tNodo));

	if (l->curr->sig == NULL){
		l->curr->sig = aux;
		return 0; //Retorna 0 si falla.
	}
	l->curr->sig->info = item;
	l->curr->sig->sig = aux;

	if(l->curr == l->tail)
		l->tail = l->curr->sig;

	l->listSize++;
	return 1; //La operacion ocurrio con exito
}

int append(tLista *l, void *item){
	tNodo *temp = (tNodo*)malloc(sizeof(tNodo));
	if (temp==NULL)
		return 0; // si no se pudo generar el nodo, muere
	else{
		temp->info = item;
		temp->sig = NULL;
		l->tail->sig = temp;
		l->tail = temp;
		l->listSize++;
	}
	return 1; // se guardo correctamente
}

void *lremove(tLista *l){
	void *item = l->curr->sig->info;
	tNodo *aux;
	aux = l->curr->sig->sig;
	if (l->curr->sig->sig == NULL){
		l->tail = l->curr;
	}
	free(l->curr->sig);
	l->curr->sig = aux;

	l->pos --;
	l->listSize--;
	return item;
}

//ARREGLAR
void *pop(tLista *l){
	moveToStart(l);
	while (currPos(l) < length(l)-1) {
		next(l);
	}
	return lremove(l);
}

void moveToStart(tLista* l){
	l -> pos = 0;
	l -> curr = l -> head;
}

void next(tLista *l){
	if(l->curr->sig != l->tail){
		l->curr = l->curr->sig;
		l->pos++;
	}
	else{
		l->pos++;
	}
}

long int length(tLista *l){
	return l->listSize;
}

long int currPos(tLista *l){
	return l->pos;
}

void *getValue(tLista *l){
	return l->curr->sig->info;
}

void *getValuen(tLista *l, int pos){
  for (moveToStart(l); currPos(l) < length(l); next(l)){
		if(currPos(l) == pos) return getValue(l);
	}
	return NULL;
}

void change(tLista *l,void *new){
	l->curr->sig->info = new;
}

void printL(tLista *l){ //VA A CAMBIAR
	// printf("{\n" );
	// for (moveToStart(l); currPos(l) < length(l); next(l)) {
	// 	printf("(nombre = %s, ", getValue(l).nombre);
	// 	printf("tipo = %d)\n", getValue(l).tipo);
	// }
	// printf("}\n" );
}
