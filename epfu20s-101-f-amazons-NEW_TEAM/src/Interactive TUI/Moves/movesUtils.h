#ifndef SRC_MOVESUTILS_H
#define SRC_MOVESUTILS_H
#include "../UTILS/structs.h"
#include "movesPossibility.h"
#include "../UTILS/IOUtils.h"
#include "../Board/boardUtils.h"
//Functions used to get and execute moves
void inputCoordinatesOfArrowOrSpear(char *name, board board1, move *move1, player player1);

void throwArrow(board *board1, move *move1, player player1);
void throwSpear(board *board1, move *move1,player player1);
void findAmazonAndChangeCoordinates(board *board1, int currentPlayer,move move1);

int executeMoveAndUpdate(board *board1, players *players1, int currentPlayer, move *move1);

void changeCurrentPlayer(int *currentPlayer, players players1);
move getMove(board board1,player player1);

void getAllMoves(board *board1, players *players1);

#endif //SRC_MOVESUTILS_H
