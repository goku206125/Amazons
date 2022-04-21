#ifndef SRC_BOARDUTILS_H
#define SRC_BOARDUTILS_H
#include "../UTILS/structs.h"
#include "../UTILS/IOUtils.h"
//Functions used to load and show the board

void generateBoard(board *board1);

void loadSizeOfTheBoard(board *board1);

board createTheBoard();
void showBoard(board board1);
//Garbage collection
void destroyBoardAndPlayers(board *board1, players *players1);
#endif //SRC_BOARDUTILS_H
