#ifndef PILE_H
#define PILE_H

typedef struct {
	Pointer bottom, top;
	int size;
} Pile;

void createEmptyPile(Pile*);
int isPileEmpty(const Pile*);
void pile(Item, Pile*);
int unpile(Pile*, Item*);
int size(const Pile*);

#endif