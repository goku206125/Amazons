#include "playersUtils.h"

void allocatePlayers(players *players1) {
    players1->array = malloc(sizeof(player) * players1->amount);
}

void allocateAmazons(board* board1) {
	board1->amazons = malloc(board1->playersAmount * sizeof(coordinates*));
	for (int i = 0; i < board1->playersAmount; i++) {
		board1->amazons[i] = malloc(board1->amazonsAmount * sizeof(coordinates));
	}
}

void inputAmountOfAmazons(board *board1) {
    printf("Input amount of amazons that each player has\n");
    scanf("%d", &(board1->amazonsAmount));
    allocateAmazons(board1);
}

//Function used to place amazons
void inputAmountOfPlayers(players *players1, board *board1) {
    printf("Input amount of players\n");
    scanf("%d", &(players1->amount));
    board1->playersAmount = players1->amount;
}
void inputPlayers(players *players1) {
    allocatePlayers(players1);
    for (int i = 0; i < players1->amount; i++) {
        printf("Input %d. player name\n",i+1);
        scanf("%s",&(players1->array[i].name));
        players1->array[i].id = i+1;
        players1->array[i].points =0;
    }
}
//Function used to place amazons
void placeAmazons(board *board1, players *players1) {
    int exception=0;
    for (int i = 0; i <board1->amazonsAmount ; i++) {
        for (int j = 0; j <board1->playersAmount ; j++) {
            showBoard(*board1);
            if(exception){
                printf("These coordinates are already occupied. Enter different ones!!! (form: 'A1','B2')\n");
                exception=0;
            }
            else{
                printf("%s's (ID:%d) turn\n",players1->array[j].name,players1->array[j].id);
                printf("Enter coordinates for your amazon in the form 'A0''B1' etc.\n");
            }
            coordinates amazon = getCoordinates(*board1);
            if(board1->fields[amazon.r][amazon.c].occupation !=0){
                j--;
                exception=1;
                continue;
            }
            field f1 = {0,0,players1->array[j].id};
            board1->fields[amazon.r][amazon.c]=f1;
            board1->amazons[j][i]=amazon;
        }
    }
}