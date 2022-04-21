#ifndef SRC_STRUCTS_H
#define SRC_STRUCTS_H
#include "constants.h"

typedef struct {
    int r;
    int c;
} coordinates;
typedef struct {
    int treasure;
    int artifact;
    int occupation;
} field;
typedef struct {
    int width;
    int length;
    int amazonsAmount;
    int playersAmount;
    coordinates **amazons;
    field **fields;
} board;
typedef struct {
    char name[15];
    int id;
    int points;
} player;
typedef struct {
    int amount;
    player *array;
} players;
typedef struct{
    coordinates from;
    coordinates to;
    coordinates arrow;
}move;
#endif //SRC_STRUCTS_H