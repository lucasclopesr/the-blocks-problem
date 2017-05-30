#ifndef PILE_H
#define PILE_H

typedef struct {
	Pointer bottom, top;
	int size;
} Pile;

void createEmptyPile(Pile *p);
void isPileEmpty(const Pile *p);
void pile(Item i, Pile *p);
Item unpile(Pile *p);
int size(const Pile *p);

#endif