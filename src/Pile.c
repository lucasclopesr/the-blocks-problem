#include "../lib/Item.h"
#include "../lib/Cell.h"
#include "../lib/Pile.h"
#include <stdlib.h>
#include <stdio.h>

void createEmptyPile(Pile *p){
	p->top = (Pointer) malloc(sizeof(Cell));
	p->bottom = p->top;
	p->top->next = NULL;
	p->size = 0;
}

int isPileEmpty(const Pile *p){
	return (p->top == p->bottom);
}

void pile(Item i, Pile *p){
	Pointer aux;
	aux = (Pointer) malloc(sizeof(Cell));

	p->top->content = i;
	aux->next = p->top;
	p->top = aux;
	p->size++;
}

int unpile(Pile *p, Item *i){
	Pointer aux;

	if(isPileEmpty(p)){
		return -1;
	}

	aux = p->top;
	p->top = aux->next;
	free(aux);

	p->size--;
	*i = p->top->content; 
	return 0;
}

int sizeOfPile(const Pile *p){
	return p->size;
}