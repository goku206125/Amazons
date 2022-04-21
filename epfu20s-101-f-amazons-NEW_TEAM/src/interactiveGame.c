#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

typedef struct {
    int treasure;
    int artifact;
    int occupation;
} field;

typedef struct {
    int width;
    int length;
    field fields[width][length];
} board;

typedef struct {
    char[15] name;
    int id;
    int points;
} player;

void loadBoard(board *board1) {

}
void loadSizeOfTheBoard(board *board1){

}
void loadPlayers(player players[]){
    //if no players
    //inputPlayers(player players[]);
}
void inputPlayers(player players[]){

}
void showBoard(board board1) {

}
void getMoveExecuteAndShowBoard(board *board1){

}
int endOftheGame(board *board1){
    int end = 0;
    // check whether the move is possible
    if(end){
        return 1;
    }
    return 0;
}
void placeAmazons(){

}
void getAllMoves(board *board1){
    while(endOfTheGame==0) {
        getMoveExecuteAndShowBoard(board1);
    }
}

int main() {
    board board1;
    players player[2];
    loadSizeOfTheBoard(&board1);
    loadBoard(&board1);
    loadPlayers(players);
    placeAmazons();
    getAllMoves();
    showBoard(&board1);
    return 0;
}