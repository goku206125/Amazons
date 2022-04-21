#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> //for random function
#include <time.h>  //for random funtion
#include "getline.h" //just for getline() function to work

//#define INTERACTIVE

//these variables are used for both autonomous and interactive modes
int N;  //number of amazons
int m,n;
int *matrix;
int r,c;   // row, column
FILE * fp, *fp2;    //usually fp-intputboard, fp2-outputboard

size_t len = 0;   //just as parameter for getline()
char * line = NULL; //parameter for getline()

int i=0;  //simple variable i for counting in some loops

#if !defined(INTERACTIVE)

//these variables are used only for autonomous mode
char *players_name="Alex"; //player's name
int player_id;
int score;

char *inputboard;
char *outputboard;
int *arr_unocupped;     //keeps unoccupied cells coordinates as row, column
int z=0; //z - unoccupied counter

#include "autonomous.h"


int main(int argc, char *argv[]) {


    //phase=placement amazons=3 inputboard.txt outpuboard.txt
    if(strcmp(argv[1], "phase=placement")==0){
           printf("===AUTONOMOUS MODE===\n\n");
           //argv[2]="amazons=N"
           char *token = strtok(argv[2], "="); //get "amazons"
           token=strtok(NULL, "=");             //get "N"
           N=atoi(token);                       //convert string "N" to int

           inputboard=argv[3];           //get "inputboard.txt"
           outputboard=argv[4];          //get "outputboard.txt"

           player_id=get_player_id();   //get player's existing id else add_player
            printf("Player id %d\n\n", player_id);

           if(place()==1){
               printf("\nSorry, all amazons are set already\n");
               return 1;
           }
           printf("\nSuccess\n");
    }
    else{
        //phase=movement board.txt board.txt
        if(strcmp(argv[1], "phase=movement")==0){
            printf("===AUTONOMOUS MODE===\n\n");
            inputboard=argv[2];           //get "board.txt"
            outputboard=argv[3];           //get "board.txt"
            player_id=get_player_id();   //get player's existing id else add_player
            printf("Player id %d\n\n", player_id);
            if(move()==1){
                printf("\nSorry, matrix is full or your amazons have no possible move\n");
                return 1;
            }
            printf("Success\n");
        }
        //name
        else{
            if(strcmp(argv[1], "name")==0){
                printf("%s\n", players_name);  //diplay player's name
            }
            else{
                printf("Incorrect command line parameters\n");
            }
        }
    }
    return 0;
}
#else

//these variables are used only for interactive mode
char *player1_name[25];
char *player2_name[25];

int player1_score;
int player2_score;

char *boardfile[25];

int score1;
int score2;

#include "interactive.h"


int main(){

    printf("===INTERACTIVE MODE===\n\n");

    printf("Player 1 name : ");
    scanf("%s", player1_name);
    printf("Player 2 name : ");
    scanf("%s", player2_name);

    printf("Boardfile : ");
    scanf("%s", boardfile);

    fp=fopen(boardfile, "r"); //open file in read mode

    if (fp == NULL){
        printf("Error, could not open file");
        exit(EXIT_FAILURE);
    }


    printf("Number of amazons : ");
    scanf("%d", &N);

    read_boardfile(); //from interactive.h


    printf("\n===CURRENT BOARD===\n\n");
    display_matrix();  //from interactive.h


    printf("\n===PLACEMENT PHASE===\n\n");

    placement_phase();

    printf("\n===MOVEMENT PHASE===\n\n");

    movement_phase();




}
#endif
