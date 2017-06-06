#include "../lib/Item.h"
#include "../lib/Blocks.h"
#include "../lib/Pile.h"

void createScenario(Blocks *scenario, int n){
	int i;
	Item deafultItem;

	scenario->ground = (Pile *) malloc(n*sizeof(Pile));

	for(i = 0; i < n; i++){
		createEmptyPile(&(scenario->ground[i]));
		deafultItem.key = i;

		pile(deafultItem, &(scenario->ground[i]));
	}

	scenario->size = n;
	
	//Loop to check if scenario was created correctly.
	/*for(i = 0; i < n; i++){
		printf("Bottom: %d\n", scenario->ground[i].bottom->content.key);
		printf("Top: %d\n\n", scenario->ground[i].top->content.key);
	}*/
}

int findBlock(Blocks scenario, int key){
	int i, j;
	Pointer temporaryItem;

	
	for(i = 0; i < scenario.size; i++){
		if(isPileEmpty(&(scenario.ground[i])) == 0){
			temporaryItem = scenario.ground[i].top->next;
			for(j = 1; j < sizeOfPile(&(scenario.ground[i])); j++){
				if(temporaryItem->content.key == key){
					return i;
				}
				temporaryItem = temporaryItem->next;
			}
		}
	}

	return -1;
}