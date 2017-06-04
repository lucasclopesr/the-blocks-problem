#ifndef BLOCKS_H
#define BLOCKS_H

typedef struct{
	Pile *ground;
	int size;
} Blocks;

void createScenario(Blocks*, int);

#endif