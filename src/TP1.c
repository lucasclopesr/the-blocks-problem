/* *****************************************************
*   Autor: Lucas Caetano Lopes Rodrigues               *
*   Disciplina: AEDS 2                                 * 
*   Curso: Ciência da Computação                       *
*   Where there is ruin there is hope for a treasure.  *
****************************************************** */

#include "Pile.c"
#include "Blocks.c"

void _generateScenario(char *input){
	Blocks scenario;
	FILE *inputFile = fopen(input, "r");
	int c;

	if(inputFile == NULL){
		//File not found
		printf("Arquivo não encontrado.");
	} else {
		fscanf(inputFile, "%d", &c);
		createScenario(&scenario, c);
	}
}

void main(int argc, char **argv){
	if(argc == 3){
		_generateScenario(argv[1]);
	} else {
		printf("Numero incorreto de parametros.\n");
	}
}