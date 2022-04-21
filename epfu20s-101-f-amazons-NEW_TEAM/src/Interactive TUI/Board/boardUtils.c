#include "boardUtils.h"

int randomTreasure() {
    int arr[] = {0,0,0,0,0,
                 0,0,0,0,0,
                 0,1,1,1,1,
                 1,1,2,2,2,
                 2,2,3,3,3,
                 3,4,4,4,5,
                 5};
    return arr[rand()%31];
}

int randomArtifact() {
    int arr[] = {0,0,0,0,0,0,0,0,1,1,2,2,3};
    return arr[rand()%13];
}

void generateBoard(board *board1) {
    for (int i = 0; i < board1->length; i++) {
        for (int j = 0; j < board1->width; j++) {
            field f1 = {randomTreasure(), randomArtifact(), 0};
            board1->fields[i][j] = f1;
        }
    }
}

void loadSizeOfTheBoard(board *board1) {
    printf("Input length of the board\n");
    scanf("%d", &(board1->length));
    getchar();
    printf("Input width of the board\n");
    scanf("%d", &(board1->width));
    getchar();
}

board createTheBoard() {
    board board1;
    loadSizeOfTheBoard(&board1);
    board1.fields =  malloc(board1.length * sizeof(field*));
    for(int i=0;i<board1.length;i++){
        board1.fields[i] = malloc(board1.width * sizeof(field));
    }
    generateBoard(&board1);
    return board1;
}

void showBoard(board board1) {
    system("cls");
    printf("    ");
    for(int i=0;i<board1.width;i++){
        printf("%c   ",(char)i+A);
    }
    printf("\n");
    for (int i = 0; i < board1.length; i++) {
        printf("%c: ",(char)board1.length-i+ZERO);
        for (int j = 0; j < board1.width; j++) {
            printf("%d", board1.fields[i][j].treasure);
            printf("%d", board1.fields[i][j].artifact);
            printf("%d ",board1.fields[i][j].occupation);
        }
        printf(":%c ",(char)board1.length-i+ZERO);
        printf("\n");
    }
    printf("    ");
    for(int i=0;i<board1.width;i++){
        printf("%c   ",(char)i+A);
    }
    printf("\n");
}

void destroyBoardAndPlayers(board *board1, players *players1) {
    for(int i=0;i<board1->length;i++){
        free(board1->fields[i]);
        free(board1->amazons[i]);
    }
    free(board1->fields);
    free(board1->amazons);
    free(players1->array);
}
