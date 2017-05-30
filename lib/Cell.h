#ifndef CELL_H
#define CELL_H

typedef struct Cell_str *Pointer;

typedef struct Cell_str{
	Item content;
	Pointer next;
} Cell;

#endif