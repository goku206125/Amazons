#include "movesUtils.h"


void inputCoordinatesOfArrowOrSpear(char *name, board board1, move *move1, player player1) {
}

void throwArrow(board *board1, move *move1, player player1) {

}

void throwSpear(board *board1, move *move1, player player1) {

}

void findAmazonAndChangeCoordinates(board *board1, int currentPlayer, move move1) {

}

int executeMoveAndUpdate(board *board1, players *players1, int currentPlayer, move *move1) {
    field empty = {0,0,0};
    board1->fields[move1->from.r][move1->from.c] = empty;
    (players1->array[currentPlayer].points)+=board1->fields[move1->to.r][move1->to.c].treasure;
    field new = {0,0,players1->array[currentPlayer].id};
    board1->fields[move1->to.r][move1->to.c] = new;
    findAmazonAndChangeCoordinates(board1,currentPlayer,*move1);
    int horse =0;
    switch(board1->fields[move1->to.r][move1->to.c].artifact){
        case 0:
            showBoard(*board1);
            throwArrow(board1,move1,players1->array[currentPlayer]);
            break;
        case 1:
            horse = 1;
            showBoard(*board1);
            throwArrow(board1,move1,players1->array[currentPlayer]);
            break;
        case 2:
            break;
        case 3:
            showBoard(*board1);
            throwSpear(board1,move1,players1->array[currentPlayer]);
            break;
    }
    return horse;
}

void changeCurrentPlayer(int *currentPlayer, players players1) {
    if (*currentPlayer == players1.amount - 1)
        *currentPlayer=0;
    else
        (*currentPlayer)++;
}

move getMove(board board1, player player1) {

}

void getAllMoves(board *board1, players *players1) {
    move move1;
    int currentPlayer = 0;
    showBoard(*board1);
    while(endOfTheGame(*board1,players1->amount)==0) {
        if(isMovePossible(*board1,currentPlayer)) {
            move1 = getMove(*board1, players1->array[currentPlayer]);
            if (obstacleOnPath(*board1, move1.from, move1.to) == 1) {
                printf("This move is not possible try again\n");
                continue;
            }
            int horse = executeMoveAndUpdate(board1, players1, currentPlayer, &move1);
            if (horse == 0)
                changeCurrentPlayer(&currentPlayer, *players1);
            showBoard(*board1);
        }
        else{
            printf("%s, you have no available moves, moving to next player",players1->array[currentPlayer].name);
            changeCurrentPlayer(&currentPlayer, *players1);
        }
    }
}
