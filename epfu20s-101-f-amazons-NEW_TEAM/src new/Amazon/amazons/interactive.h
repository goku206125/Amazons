void read_boardfile(){

    char *token;

    //get m and n from file first line
    getline(&line,&len, fp);
    token = strtok(line, " ");
    m=atoi(token);
    token=strtok(NULL, " ");
    n=atoi(token);

    matrix=(int *)malloc(m*n*3*sizeof(int));

    i=0;
    while (i<m) {

        getline(&line,&len, fp);   //get a line

        token = strtok(line, " ");  //get first column first row
        *(matrix+i*n*3+0*3+0)=token[0]-'0'; // -'0' to convert char to int
        *(matrix+i*n*3+0*3+1)=token[1]-'0';
        *(matrix+i*n*3+0*3+2)=token[2]-'0';

        //get the rest columns
        for(int k=1; k<n; k++){

            token=strtok(NULL, " ");

            *(matrix+i*n*3+k*3+0)=token[0]-'0'; // -'0' to convert char to int
            *(matrix+i*n*3+k*3+1)=token[1]-'0';
            *(matrix+i*n*3+k*3+2)=token[2]-'0';

        }

        i++;

    }
}


void display_matrix(){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++)
           printf("%d%d%d ", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));
         printf("\n");
    }
}


void placement_phase(){
    i=0;

    while(i<N){


        printf("Player %s enter row, column for amazon %d: ", player1_name, i+1);
        scanf("%d,%d", &r, &c);

        while(place(1, r, c)!=0){   //place from interactive.h

            printf("CANNOT PLACE AT %d,%d\n", r, c);
            printf("Player %s enter row, column for amazon %d: ", player1_name, i+1);
            scanf("%d,%d", &r, &c);

        }

        display_matrix(); //from interactive.h

        printf("Player %s enter row, column for amazon %d: ", player2_name, i+1);
        scanf("%d,%d", &r, &c);


        while(place(2, r, c)!=0){

            printf("CANNOT PLACE AT %d,%d\n", r, c);
            printf("Player %s enter row, column for amazon %d: ", player2_name, i+1);
            scanf("%d,%d", &r, &c);

        }

        display_matrix(); //from interactive.h

        i++;
    }
}


int place(int player_id, int r, int c){

    if(*(matrix + r*n*3 + 3*c+2)==0){

        *(matrix + r*n*3 + 3*c+0)=0;
        *(matrix + r*n*3 + 3*c+1)=0;
        *(matrix + r*n*3 + 3*c+2)=player_id;

        return 0;
    }

    return 1;
}


int movement_phase(){
    int r1,c1;
    int player1_num_possible_moves=0;
    int player2_num_possible_moves=0;


    while(1)
    {
        player1_num_possible_moves=0;
        player2_num_possible_moves=0;

        printf("%s's score: %d\n", player1_name, score1);
        printf("%s's score: %d\n", player2_name, score2);

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){

                if(*(matrix + i*n*3 + 3*j+2)==1)
                    player1_num_possible_moves+=get_or_move_possible_movements_amazon(i, j, -1, 0);

                if(*(matrix + i*n*3 + 3*j+2)==2)
                    player2_num_possible_moves+=get_or_move_possible_movements_amazon(i, j, -1, 0);

            }
        }


        if(player1_num_possible_moves==0){
            printf("%s LOST", player1_name);
            return 1;
        }

        if(player2_num_possible_moves==0){
            printf("%s LOST", player2_name);
            return 1;
        }


        printf("%s choose amazon to move:", player1_name);
        scanf("%d, %d", &r1 ,&c1 );

        //check if amazon belongs to player_id and has possible moves
        while(get_or_move_possible_movements_amazon(r1, c1, -1, 1)==0){

            printf("%s choose amazon to move:", player1_name);
            scanf("%d, %d", &r1 ,&c1 );

        }

        printf("%s choose row, column where to move:", player1_name);
        scanf("%d, %d", &r ,&c);


        while(get_or_move_possible_movements_amazon(r1, c1, 0, 1)==0){

            printf("%s choose row, column where to move:", player1_name);
            scanf("%d, %d", &r ,&c);

        }

        display_matrix();

        player1_num_possible_moves=0;
        player2_num_possible_moves=0;

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){

                if(*(matrix + i*n*3 + 3*j+2)==1)
                    player1_num_possible_moves+=get_or_move_possible_movements_amazon(i, j, -1, 0);

                if(*(matrix + i*n*3 + 3*j+2)==2)
                    player2_num_possible_moves+=get_or_move_possible_movements_amazon(i, j, -1, 0);

            }
        }


        if(player1_num_possible_moves==0){
            printf("%s LOST", player1_name);
            return 1;
        }

        if(player2_num_possible_moves==0){
            printf("%s LOST", player2_name);
            return 1;
        }


        printf("%s choose amazon to move:", player2_name);
        scanf("%d, %d", &r1 ,&c1 );

        //check if amazon belongs to player_id and has possible moves
        while(get_or_move_possible_movements_amazon(r1, c1, -1, 2)==0){

            printf("%s choose amazon to move:", player2_name);
            scanf("%d, %d", &r1 ,&c1 );

        }

        printf("%s choose row, column where to move:", player2_name);
        scanf("%d, %d", &r ,&c);


        while(get_or_move_possible_movements_amazon(r1, c1, 0, 2)==0){

            printf("%s choose row, column where to move:", player2_name);
            scanf("%d, %d", &r ,&c);

        }

        display_matrix();


    }

}


//get number of possible movements for amazon at x,y or move to r,c
// z==-1 get number of possible movements..
// z==0 move to r, c
int get_or_move_possible_movements_amazon(int x, int y, int z, int player_id){
    int counter=0;


    if(z==-1 && player_id>0 && player_id!=*(matrix+x*n*3+y*3+2)){
        printf("Choose amazon with player_id %d\n", player_id);
        return 0;
    }


    // (x; y) right
    for(int i=y+1; i<n; i++){
        if(*(matrix+x*n*3+i*3+2)!=0)
            break;
        counter++;
        if(z==0 && x==r && i==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+x*n*3+i*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+x*n*3+i*3+0);
            if(player_id==2)
                score2+=*(matrix+x*n*3+i*3+0);

            *(matrix+x*n*3+i*3+0)=0;
            printf("Moving to %d:%d\n", x, i);
            return 1;
        }
    }

    // (x; y) left
    for(int i=y-1; i>=0; i--){
        if(*(matrix+x*n*3+i*3+2)!=0)
            break;
        counter++;
        if(z==0 && x==r && i==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+x*n*3+i*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+x*n*3+i*3+0);
            if(player_id==2)
                score2+=*(matrix+x*n*3+i*3+0);
            *(matrix+x*n*3+i*3+0)=0;
            printf("Moving to %d:%d\n", x, i);
            return 1;
        }
    }

    // (x; y) down
    for(int i=x+1; i<m; i++){
        if(*(matrix+i*n*3+y*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+y*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+y*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+y*3+0);
            *(matrix+i*n*3+y*3+0)=0;
            printf("Moving to %d:%d\n", i, y);
            return 1;

        }
    }

    // (x; y) up
    for(int i=x-1; i>=0; i--){
        if(*(matrix+i*n*3+y*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+y*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+y*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+y*3+0);
            *(matrix+i*n*3+y*3+0)=0;
            printf("Moving to %d:%d\n", i, y);
            return 1;

        }
    }

    // (x; y) up-right diagonal
    for(int i=x-1; i>=0; i--){
        if(y+x-i>=n)
            break;
        if(*(matrix+i*n*3+(y+x-i)*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y+x-i==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y+x-i)*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+(y+x-i)*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+(y+x-i)*3+0);
            *(matrix+i*n*3+(y+x-i)*3+0)=0;
            printf("Moving to %d:%d\n", i, y+x-i);
            return 1;

        }

    }

    // (x; y) up-left diagonal
    for(int i=x-1; i>=0; i--){
        if(y-(x-i)<0)
            break;
        if(*(matrix+i*n*3+(y-(x-i))*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y-(x-i)==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y-(x-i))*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+(y-(x-i))*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+(y-(x-i))*3+0);
            *(matrix+i*n*3+(y-(x-i))*3+0)=0;
            printf("Moving to %d:%d\n", i, y-(x-i));
            return 1;

        }
    }

    // (x; y) down-right diagonal
    for(int i=x+1; i<m; i++){
        if(y+i-x>=n)
            break;
        if(*(matrix+i*n*3+(y+i-x)*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y+i-x==c){
            *(matrix+x*n*3+y*3+2)=0;
           *(matrix+i*n*3+(y+i-x)*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+(y+i-x)*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+(y+i-x)*3+0);
            *(matrix+i*n*3+(y+i-x)*3+0)=0;
            printf("Moving to %d:%d\n", i, y+i-x);
            return 1;

        }
    }

    // (x; y) down-left diagonal
    for(int i=x+1; i<m; i++){
        if(y-(i-x)<0)
            break;
        if(*(matrix+i*n*3+(y-(i-x))*3+2)!=0)
            break;
        counter++;
        if(z==0 && i==r && y-(i-x)==c){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y-(i-x))*3+2)=player_id;
            if(player_id==1)
                score1+=*(matrix+i*n*3+(y-(i-x))*3+0);
            if(player_id==2)
                score2+=*(matrix+i*n*3+(y-(i-x))*3+0);
            *(matrix+i*n*3+(y-(i-x))*3+0)=0;
            printf("Moving to %d:%d\n", i, y-(i-x));
            return 1;
        }
    }



    if(z==0){
        return 0;
    }

    return counter;
}
