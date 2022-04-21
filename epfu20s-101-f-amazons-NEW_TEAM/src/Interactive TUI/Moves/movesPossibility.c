#include "movesPossibility.h"

int isFieldEmpty(field f1) {

}

int isMovePossible(board board1, int currentPlayer) {
    for (int j = 0; j < board1.amazonsAmount; j++) {
        coordinates c = board1.amazons[currentPlayer][j];
        for (int k = -1; k < 2; k++) {
            for (int l = -1; l < 2; l++) {
                int x = c.r+k;
                int y = c.c+l;
                if(x>=0&&y>=0&&x<board1.length&&y<board1.width) {
                    field cf = board1.fields[x][y];
                    if (isFieldEmpty(cf)) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int endOfTheGame(board board1, int amountOfPlayers) {

}
void exchangeFromTo(int *from, int *to) {

}

void exchangeReverseFromTo(int *from, int *to) {

}

int obstacleOnPath(board board1, coordinates from, coordinates to) {
    if(from.c==to.c){ // move orthogonally right or left
        if(from.r==to.r){
            return 1;
        }
        exchangeFromTo(&(from.r), &(to.r));
        for (int i = from.r; i <= to.r; ++i) {
            printf("%d",i);
            field field1= board1.fields[i][from.c];
            if(!isFieldEmpty(field1)){
                return 1;
            }
        }
        return 0;
    }
    if(from.r == to.r){ // move orthogonally up or down
        exchangeFromTo(&(from.c), &(to.c));
        for (int i = from.c; i <= to.c; i++) {
            field field1= board1.fields[from.r][i];
            if(!isFieldEmpty(field1)){
                return 1;
            }
        }
        return 0;
    }
    if(from.r-to.r==from.c-to.c) {//move diagonally up - left or down - right
        exchangeFromTo(&(from.c), &(to.c));
        exchangeFromTo(&(from.r), &(to.r));
        for (int i = from.r, j = from.c; i <= to.r,j<=to.c; i++,j++) {
            field field1= board1.fields[i][j];
            if(!isFieldEmpty(field1)){
                return 1;
            }
        }
        return 0;
    }
    if(from.r-to.r==-(from.c-to.c)){ //move diagonally up - right or down - left
        exchangeFromTo(&from.r, &to.r);
        exchangeReverseFromTo(&from.c, &to.c);
        for (int i = from.r, j = from.c; i <= to.r,j>=to.c; i++,j--) {
            field field1= board1.fields[i][j];
            if(!isFieldEmpty(field1)){
                return 1;
            }
        }
        return 0;
    }
    return 1;
}

int isTheAmazonPlayers(board board1, move move1, player player1) {

}
