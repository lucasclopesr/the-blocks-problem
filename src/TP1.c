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
							for(k = 1; k < sizeOfPile(&(scenario->ground[j])); k++){
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
							for(k = 1; k < sizeOfPile(&(scenario->ground[i])); k++){
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
							for(k = 1; k < sizeOfPile(&(scenario->ground[j])); k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Unpile blocks above a, returning them to original location
							for(k = 1; k < sizeOfPile(&(scenario->ground[i])); k++){
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
	int unpiledIndex;

	Item temporaryUnpiledItem;

	for(i = 0; i < scenario->size; i++){
		if(scenario->ground[i].bottom->content.key == a){
			if(sizeOfPile(&(scenario->ground[i])) == 1){
				//No blocks above a
				for(j = 0; j < scenario->size; j++){
					if(scenario->ground[j].bottom->content.key == b){
						//Move a over b
						pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
						unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
					}
				}
			} else {
				//Some blocks above a
				//Unpile blocks above a, returning them to original location
				for(k = 1; k < sizeOfPile(&(scenario->ground[i])); k++){
					unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
					unpiledIndex = temporaryUnpiledItem.key;
					pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
				}

				//Move a over b
				pile(scenario->ground[i].bottom->content, &(scenario->ground[j]));
				unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
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
							for(k = 0; k < sizeOfPile(&(scenario->ground[i])); k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(temporaryPile));
							}

							//Pile blocks above a in right order onto b
							for(k = 0; k < sizeOfPile(&temporaryPile); k++){
								unpile(&temporaryPile, &temporaryUnpiledItem);
								pile(temporaryUnpiledItem, &(scenario->ground[j]));
							}
						} else {
							//Some blocks above b
							//Unpile blocks above b, returning them to original location
							for(k = 1; k < sizeOfPile(&(scenario->ground[j])); k++){
								unpile(&(scenario->ground[j]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(scenario->ground[unpiledIndex]));
							}

							//Unpile blocks above a
							for(k = 0; k < sizeOfPile(&(scenario->ground[i])); k++){
								unpile(&(scenario->ground[i]), &temporaryUnpiledItem);
								unpiledIndex = temporaryUnpiledItem.key;
								pile(temporaryUnpiledItem, &(temporaryPile));
							}

							//Pile blocks above a in right order onto b
							for(k = 0; k < sizeOfPile(&temporaryPile); k++){
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
	printf("\n");

	Item test;
	for(i = 0; i < scenario->size; i++){
		printf("Pilha %d:\n", i);
		for(j = 0; j <= sizeOfPile(&(scenario->ground[i])); j++){
			unpile(&(scenario->ground[i]), &test);
			printf("Item: %d\n", test.key);
		}
		printf("\n");
	}*/
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
					_moveOnto(scenario, item1, item2);
				}
			}

			if(strcmp(cmd1, "pile") == 0){
				if(strcmp(cmd2, "onto") == 0){
					//Call pileOnto
					_pileOnto(scenario, item1, item2);
				}
				if(strcmp(cmd2, "over") == 0){
					//Call pileOver
				}
			}
		}
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
		}
	} else {
		printf("Numero incorreto de parametros.\n");
	}
}