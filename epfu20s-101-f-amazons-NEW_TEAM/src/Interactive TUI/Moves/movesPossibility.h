
#ifndef SRC_MOVESPOSSIBILITY_H
#define SRC_MOVESPOSSIBILITY_H

#include "../UTILS/structs.h"

//Functions used to check whether the move is possible
int isFieldEmpty(field f1);

int isMovePossible(board board1, int currentPlayer);

int endOfTheGame(board board1, int amountOfPlayers);
void exchangeFromTo(int *from, int *to);
void exchangeReverseFromTo(int *from, int *to);
int obstacleOnPath(board board1, coordinates from, coordinates to);
int isTheAmazonPlayers(board board1, move move1,player player1);

#endif //SRC_MOVESPOSSIBILITY_H
