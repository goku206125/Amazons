#ifndef SRC_IOUTILS_H
#define SRC_IOUTILS_H
#include "structs.h"

void omitSpacesTabsAndEnters(char *c, FILE *f);
//Functions ending the game - score
void showScore(players players1);
coordinates getCoordinates(board board1);
#endif //SRC_IOUTILS_H
