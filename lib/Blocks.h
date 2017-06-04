#ifndef BLOCKS_H
#define BLOCKS_H

typedef struct{
	Pile *ground;
} Blocks;

void createScenario(Blocks*, int);

#endif