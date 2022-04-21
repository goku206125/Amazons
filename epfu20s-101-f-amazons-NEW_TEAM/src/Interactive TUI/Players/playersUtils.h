#ifndef SRC_PLAYERSUTILS_H
#define SRC_PLAYERSUTILS_H
#include "../UTILS/structs.h"
#include "../Board/boardUtils.h"
#include "../UTILS/IOUtils.h"

void inputPlayers(players *players1);

void allocatePlayers(players *players1);

void inputAmountOfPlayers(players *player1, board *board1);

void inputAmountOfAmazons(board *board1);

void placeAmazons(board *board1, players *player1);
#endif //SRC_PLAYERSUTILS_H
