#include "UTILS/structs.h"
#include "Board/boardUtils.h"
#include "Moves/movesUtils.h"
#include "Players/playersUtils.h"
int main() {
    players players1;
    board board1 = createTheBoard();
    inputAmountOfAmazons(&board1);
    inputAmountOfPlayers(&players1, &board1);
    inputPlayers(&players1);
    placeAmazons(&board1, &players1);
    getAllMoves(&board1, &players1);
    showScore(players1);
    destroyBoardAndPlayers(&board1, &players1);
    return 0;
}