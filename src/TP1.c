/* *****************************************************
*   Autor: Lucas Caetano Lopes Rodrigues               *
*   Disciplina: AEDS 2                                 * 
*   Curso: Ciência da Computação                       *
*   Where there is ruin there is hope for a treasure.  *
****************************************************** */

#include "Pile.c"
#include "Blocks.c"
#include <string.h>

FILE* _generateScenario(char *input, Blocks *scenario){
	FILE *inputFile = fopen(input, "r");
	int c;

	if(inputFile == NULL){
		//File not found
		printf("Arquivo não encontrado.");
	} else {
		fscanf(inputFile, "%d", &c);
		createScenario(scenario, c);
	}

	return inputFile;
}

void _moveOnto(Blocks *scenario, int a, int b){
	//Iterators
	int i; //Finds pile corresponding to a's index.
	int j; //Finds pile corresponding to b's index.
	int k; //Aux iterator to unpile and pile itens around.
	int unpiledIndex;

	int sizeOfAStack;
	int sizeOfBStack;

	Item temporaryUnpiledItem;

	for(i = 0; i < scenario->size; i++){
		if(scenario->ground[i].bottom->content.key == a){
			if(sizeOfPile(&(scenario->ground[i])) == 1){
				//No blocks above a
				for(j = 0; j < scenario->size; j++){
					if(scenario->ground[j].bottom->content.key == b){
						if(sizeOfPile(&(scenario->ground[j])) == 1){
							//No blocks above b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						} else {
							//Some blocks above b
							//Unpile blocks above b, returning them to original location
							sizeOfBStack = sizeOfPile(&(scenario->ground[j]));
							for(k = 1; k < sizeOfBStack; k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Move a onto b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						}
					}
				}
			} else {
				//Some blocks above a
				for(j = 0; j < scenario->size; j++){
					if(scenario->ground[j].bottom->content.key == b){
						if(sizeOfPile(&(scenario->ground[j])) == 1){
							//No blocks above b
							//Unpile blocks above a, returning them to original location
							sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
							for(k = 1; k < sizeOfAStack; k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Move a onto b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						} else {
							//Some blocks above b
							//Unpile blocks above b, returning them to original location
							sizeOfBStack = sizeOfPile(&(scenario->ground[j]));
							for(k = 1; k < sizeOfBStack; k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Unpile blocks above a, returning them to original location
							sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
							for(k = 1; k < sizeOfAStack; k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Move a onto b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						}
					}
				}
			}
		} else {
			//Element is not on the "ground". Figure out if I have to treat this.
		}
	}

	/*for(i = 0; i < scenario->size; i++){
		printf("Pilha %d: %d\n", i, sizeOfPile(&(scenario->ground[i])));
	}
	printf("\n");*/
}

void _moveOver(Blocks *scenario, int a, int b){
	//Iterators
	int i; //Finds pile corresponding to a's index.
	int j; //Finds pile corresponding to b's index.
	int k; //Aux iterator to unpile and pile itens around.
	int pileOfB;
	int unpiledIndex;

	int sizeOfAStack;
	int sizeOfBStack;

	Item temporaryUnpiledItem;

	for(i = 0; i < scenario->size; i++){
		if(scenario->ground[i].bottom->content.key == a){
			if(sizeOfPile(&(scenario->ground[i])) == 1){
				//No blocks above a
				pileOfB = findBlock(*scenario, b);

				if(pileOfB != -1){
					//Move a over b
					pile(scenario->ground[i].bottom->content, &(scenario->ground[pileOfB]));
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
				}
			} else {
				//Some blocks above a
				//Unpile blocks above a, returning them to original location
				sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
				for(k = 1; k < sizeOfAStack; k++){
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
					unpiledIndex = temporaryUnpiledItem.key;
					pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
				}

				pileOfB = findBlock(*scenario, b);

				if(pileOfB != -1){
					//Move a over b
					pile(scenario->ground[i].bottom->content, &(scenario->ground[pileOfB]));
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
				}
			}
		} else {
			//Element is not on the "ground". Figure out if I have to treat this.
		}
	}

	/*for(i = 0; i < scenario->size; i++){
		printf("Pilha %d: %d\n", i, sizeOfPile(&(scenario->ground[i])));
	}
	printf("\n");*/
}

void _pileOnto(Blocks *scenario, int a, int b){
	//Iterators
	int i; //Finds pile corresponding to a's index.
	int j; //Finds pile corresponding to b's index.
	int k; //Aux iterator to unpile and pile itens around.
	int unpiledIndex;

	int sizeOfAStack;
	int sizeOfBStack;
	int sizeOfTemporaryStack;

	Item temporaryUnpiledItem;
	Pile temporaryPile;

	createEmptyPile(&temporaryPile);

	for(i = 0; i < scenario->size; i++){
		if(scenario->ground[i].bottom->content.key == a){
			if(sizeOfPile(&(scenario->ground[i])) == 1){
				//No blocks above a
				for(j = 0; j < scenario->size; j++){
					if(scenario->ground[j].bottom->content.key == b){
						if(sizeOfPile(&(scenario->ground[j])) == 1){
							//No blocks above b
							//Pile a onto b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						} else {
							//Some blocks above b
							//Unpile blocks above b, returning them to original location
							for(k = 1; k < sizeOfPile(&(scenario->ground[j])); k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Pile a onto b
							pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
							unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
						}
					}
				}
			} else {
				//Some blocks above a
				for(j = 0; j < scenario->size; j++){
					if(scenario->ground[j].bottom->content.key == b){
						if(sizeOfPile(&(scenario->ground[j])) == 1){
							//No blocks above b
							//Unpile blocks above a
							sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
							for(k = 0; k < sizeOfAStack; k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(temporaryPile));
							}

							//Pile blocks above a in right order onto b
							sizeOfTemporaryStack = sizeOfPile(&temporaryPile);
							for(k = 0; k < sizeOfTemporaryStack; k++){
								unpile(&temporaryPile, &temporaryUnpiledItem);
								pile(temporaryUnpiledItem, &(scenario->ground[j]));
							}
						} else {
							//Some blocks above b
							//Unpile blocks above b, returning them to original location
							sizeOfBStack = sizeOfPile(&(scenario->ground[j]));
							for(k = 1; k < sizeOfBStack; k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Unpile blocks above a
							sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
							for(k = 0; k < sizeOfAStack; k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(temporaryPile));
							}

							//Pile blocks above a in right order onto b
							sizeOfTemporaryStack = sizeOfPile(&temporaryPile);
							for(k = 0; k < sizeOfTemporaryStack; k++){
								unpile(&temporaryPile, &temporaryUnpiledItem);
								pile(temporaryUnpiledItem, &(scenario->ground[j]));
							}
						}
					}
				}
			}
		} else {
			//Element is not on the "ground". Figure out if I have to treat this.
		}
	}

	/*for(i = 0; i < scenario->size; i++){
		printf("Pilha %d: %d\n", i, sizeOfPile(&(scenario->ground[i])));
	}
	printf("\n");*/
}

void _pileOver(Blocks *scenario, int a, int b){
	//Iterators
	int i; //Finds pile corresponding to a's index.
	int j; //Finds pile corresponding to b's index.
	int k; //Aux iterator to unpile and pile itens around.
	int unpiledIndex;
	int pileOfB;

	int sizeOfAStack;
	int sizeOfBStack;
	int sizeOfTemporaryStack;

	Item temporaryUnpiledItem;
	Pile temporaryPile;

	createEmptyPile(&temporaryPile);

	for(i = 0; i < scenario->size; i++){
		if(scenario->ground[i].bottom->content.key == a){
			if(sizeOfPile(&(scenario->ground[i])) == 1){
				//No blocks above a
				pileOfB = findBlock(*scenario, b);

				if(pileOfB != -1){
					//Pile a over b
					pile(scenario->ground[i].bottom->content, &(scenario->ground[pileOfB]));
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
				}
			} else {
				//Some blocks above a
				//Unpile blocks above a
				sizeOfAStack = sizeOfPile(&(scenario->ground[i]));
				for(k = 0; k < sizeOfAStack; k++){
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
					unpiledIndex = temporaryUnpiledItem.key;
					pile(temporaryUnpiledItem, &(temporaryPile));
				}

				pileOfB = findBlock(*scenario, b);

				if(pileOfB != -1){
					//Pile blocks above a in right order onto b
					sizeOfTemporaryStack = sizeOfPile(&temporaryPile);
					for(k = 0; k < sizeOfTemporaryStack; k++){
						unpile(&temporaryPile, &temporaryUnpiledItem);
						pile(temporaryUnpiledItem, &(scenario->ground[pileOfB]));
					}
				}
			}
		} else {
			//Element is not on the "ground". Figure out if I have to treat this.
		}
	}

	/*for(i = 0; i < scenario->size; i++){
		printf("Pilha %d: %d\n", i, sizeOfPile(&(scenario->ground[i])));
	}
	printf("\n");*/
}

void _executeCommands(FILE *input, Blocks *scenario){
	char cmd1[5], cmd2[5];
	int item1, item2;
	int scanReturn;

	while(scanReturn != 1){
		scanReturn = fscanf(input, "%s %d %s %d", cmd1, &item1, cmd2, &item2);
		if(strcmp(cmd1, "quit") != 0){
			if(strcmp(cmd1, "move") == 0){
				if(strcmp(cmd2, "onto") == 0){
					//Call moveOnto
					_moveOnto(scenario, item1, item2);
				}
				if(strcmp(cmd2, "over") == 0){
					//Call moveOver
					_moveOver(scenario, item1, item2);
				}
			}

			if(strcmp(cmd1, "pile") == 0){
				if(strcmp(cmd2, "onto") == 0){
					//Call pileOnto
					_pileOnto(scenario, item1, item2);
				}
				if(strcmp(cmd2, "over") == 0){
					//Call pileOver
					_pileOver(scenario, item1, item2);
				}
			}
		}
	}
}

void _writeOutput(Blocks scenario, char *output){
	FILE *outputFile = fopen(output, "w");

	int i;
	int j;
	int k;
	int sizeOfStack;
	int sizeOfTemporaryStack;

	Item temporaryUnpiledItem;
	Pile temporaryPile;

	createEmptyPile(&temporaryPile);

	for(i = 0; i < scenario.size; i++){
		fprintf(outputFile, "%d: ", i);
		sizeOfStack = sizeOfPile(&(scenario.ground[i]));

		for(j = 0; j < sizeOfStack; j++){
			unpile(&(scenario.ground[i]), &temporaryUnpiledItem);
			pile(temporaryUnpiledItem, &(temporaryPile));
		}

		sizeOfTemporaryStack = sizeOfPile(&(temporaryPile));
		for(k = 0; k < sizeOfTemporaryStack; k++){
			unpile(&(temporaryPile), &temporaryUnpiledItem);
			fprintf(outputFile, "%d ", temporaryUnpiledItem);
		}

		fprintf(outputFile, "\n");
	}
}

void main(int argc, char **argv){
	Blocks scenario;
	FILE *input;

	int i;

	if(argc == 3){
		input = _generateScenario(argv[1], &scenario);

		if(input != NULL){
			_executeCommands(input, &scenario);
			_writeOutput(scenario, argv[2]);
		}
	} else {
		printf("Numero incorreto de parametros.\n");
	}
}