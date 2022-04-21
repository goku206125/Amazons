#include "IOUtils.h"

void omitSpacesTabsAndEnters(char *c, FILE *f) {
    while((int)*c == SPACE || (int)*c == TAB|| (int)*c == ENTER ||(int)*c==CR){
        *c = fgetc(f);
    }
}

void showScore(players players) {

}

coordinates getCoordinates(board board1) {
    coordinates input;
    char c = getchar();
    omitSpacesTabsAndEnters(&c,stdin);
    if(c>Z){
        input.c = (int)c-a;
    }
    else{
        input.c = (int)c-A;
    }
    c = getchar();
    omitSpacesTabsAndEnters(&c,stdin);
    input.r = board1.length-((int)c-ZERO);
    if(input.r>=board1.length||input.c>=board1.width){
        printf("These coordinates are out of the range of the board. Enter different ones!!! (form: 'A1','B2')\n");
        return getCoordinates(board1);
    }
    return input;
}