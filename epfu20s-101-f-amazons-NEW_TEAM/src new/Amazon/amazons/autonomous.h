
int add_player(int new_id){
    fprintf(fp,"\n%s %d %d", players_name, new_id, score); //save a line for player data
    return new_id;
}

int get_player_id(){
    char *token;

    fp = fopen(inputboard, "r+");   //open file in read and write mode
    if (fp == NULL)
        exit(EXIT_FAILURE);

    //get m and n from file first line
    getline(&line,&len, fp);
    i++;
    token = strtok(line, " ");
    m=atoi(token);
    token=strtok(NULL, " ");
    n=atoi(token);
    //printf("%d\n",n);

    while ( getline(&line,&len, fp) != -1) {
        i++;
        if(i>=(m+2)){
           token = strtok(line, " ");
            if(strcmp(line, players_name)==0){
                token=strtok(NULL, " ");
                score=atoi(strtok(NULL, " "));
                return atoi(token); //return existing player id

            }
        }
        //printf("%s", line);
    }

    if (line)
        free(line);

    return add_player(i-m); //return new player id
}

//get unoccupied fields or place amazon
int get_unoccupied_fields(){
    char *token;
    int id_occup_count=0;

    fseek(fp, 0, SEEK_SET);  //reset file pointer/cursor to the beginnig
    getline(&line,&len, fp); //skip first row/line
    i=1;

    printf("===Old Board===\n");

    while (i<=m) {
        int j=0;
        getline(&line,&len, fp);   //get a line
        printf(line);

        token = strtok(line, " ");  //get first column
        if(token[2]==(player_id+'0')){
                id_occup_count++;
        }else{
            //if it is like 490 or 240
            if(token[2]=='0')
                z++;
        }

        //get the rest columns
        for(int k=1; k<n; k++){
            j++;
            token=strtok(NULL, " ");

            if(token[2]==(player_id+'0'))
                id_occup_count++;
            else if(token[2]=='0')      //if it is like 490 or 240
                    z++;
        }
        i++;
    }


    fseek(fp, 0, SEEK_SET);  //reset file cursor to the beginnig
    getline(&line,&len, fp); //skip first row/line
    i=1;


    if(id_occup_count>=N)
        return 1;

    if(z==0)
        return 1;



    arr_unocupped=(int*)malloc(z*2*sizeof(int));
    z=0;

    //printf("test%d", z);

    while (i<=m) {
        int j=0;
        getline(&line,&len, fp);   //get a line
        //printf(line);
        token = strtok(line, " ");  //get first column
        if(token[2]=='0')  //if it is like 490 or 240
        {
            *(arr_unocupped+z*2+0)=i-1;
            *(arr_unocupped+z*2+1)=j;
            z++;
        }
        //get the rest columns
        for(int k=1; k<n; k++){
            j++;
            token=strtok(NULL, " ");
             if(token[2]=='0')  //if it is like 490 or 240
            {
                *(arr_unocupped+z*2+0)=i-1;
                *(arr_unocupped+z*2+1)=j;
                z++;
            }
        }
        i++;
    }
    return 0;
}

int place(){
    if(get_unoccupied_fields()==1)
        return 1;

    srand(time(0));
    int my_rand=rand()%z;
    int r,c;  //row column
    char *token;
    // for (int i = 0; i < z; i++)
    //  for (int j = 0; j < 2; j++)
    //      printf("%d\n", *(arr_unocupped + i*2 + j));
    //printf("Random number: %d\n",my_rand);
    r= *(arr_unocupped+my_rand*2+0);
    c= *(arr_unocupped+my_rand*2+1);

    printf("\nPlacing amazon to %d:%d\n", r,c);

    //if outputboard == inputboard
    if(strcmp(inputboard, outputboard)==0){

        fseek(fp, 0, SEEK_SET);  //reset file pointer/cursor to the beginning
        getline(&line,&len, fp); //skip first row/line

        for(int k=0; k<r+1;k++){
            getline(&line,&len, fp);
        }

        char orig_line[strlen(line)];

        strcpy(orig_line, line);
        //printf("size: %d\n", sizeof(orig_line));

        token = strtok(line, " ");  //get first column

        if(c==0){
            token[0]='0';
            token[1]='0';
            token[2]=player_id+'0';  //convert player id to character
        }
        else{
            for(int k=1; k<=c;k++){
                token=strtok(NULL, " ");
            }
            token[0]='0';
            token[1]='0';
            token[2]=player_id+'0'; //convert player id to character
        }

        orig_line[c+c*3]=token[0];
        orig_line[c+c*3+1]=token[1];
        orig_line[c+c*3+2]=token[2];

        //printf("%s\n",token);;
       // printf("%s\n",orig_line);
        //printf("%s\n", line);

        fseek(fp, -(1+3*n+n), SEEK_CUR);  //move fp to previous line
        fprintf(fp,"%s", orig_line);

        fseek(fp, 0, SEEK_SET); //set filepointer to the beginning
        getline(&line,&len, fp); //skip first row/line

        printf("===New board===\n");
        for(int k=0; k<m;k++){
            getline(&line,&len, fp);
            printf(line);
        }
    }
    else{

        fp2 = fopen(outputboard, "w+");   //open in write mode
        fprintf(fp2, "%d %d\n", m, n);

        fseek(fp, 0, SEEK_SET);  //reset file pointer/cursor to the beginnig
        getline(&line,&len, fp); //skip first row/line

        for(int k=0; k<r;k++){
            getline(&line,&len, fp);
            fprintf(fp2, "%s", line);
        }

        getline(&line,&len, fp);
        char orig_line[strlen(line)];

        strcpy(orig_line, line);
        //printf("size: %d\n", sizeof(orig_line));

        token = strtok(line, " ");  //get first column

        if(c==0){
            token[0]='0';
            token[1]='0';
            token[2]=player_id+'0';  //convert player id to character
        }
        else{
            for(int k=1; k<=c;k++){
                token=strtok(NULL, " ");
            }
            token[0]='0';
            token[1]='0';
            token[2]=player_id+'0'; //convert player id to character
        }

        orig_line[c+c*3]=token[0];
        orig_line[c+c*3+1]=token[1];
        orig_line[c+c*3+2]=token[2];

        //printf("%s\n",token);;
        // printf("%s\n",orig_line);
        //printf("%s\n", line);

        fprintf(fp2,"%s", orig_line);

        while ( getline(&line,&len, fp) != -1) {
            fprintf(fp2, "%s", line);
        }


        fseek(fp2, 0, SEEK_SET); //set filepointer to the beginning
        getline(&line,&len, fp2); //skip first row/line

        printf("===New board===\n");
        for(int k=0; k<m;k++){
            getline(&line,&len, fp2);
            printf(line);
        }
    }

    return 0;
}

//get number of possible moves for amazon at (x,y) coordinate or move to z th possible
int get_or_move_possible_movements_amazon(int x, int y, int z){
    int counter=0;

    // (x; y) right
    for(int i=y+1; i<n; i++){
        if(*(matrix+x*n*3+i*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+x*n*3+i*3+2)=player_id;
            score+=*(matrix+x*n*3+i*3+0);
            printf("Moving to %d:%d\n", x, i);
        }
    }

    // (x; y) left
    for(int i=y-1; i>=0; i--){
        if(*(matrix+x*n*3+i*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+x*n*3+i*3+2)=player_id;
            score+=*(matrix+x*n*3+i*3+0);
            printf("Moving to %d:%d\n", x, i);
        }
    }

    // (x; y) down
    for(int i=x+1; i<m; i++){
        if(*(matrix+i*n*3+y*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+y*3+2)=player_id;
            score+=*(matrix+i*n*3+y*3+0);
            printf("Moving to %d:%d\n", i, y);

        }
    }

    // (x; y) up
    for(int i=x-1; i>=0; i--){
        if(*(matrix+i*n*3+y*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+y*3+2)=player_id;
            score+=*(matrix+i*n*3+y*3+0);
            printf("Moving to %d:%d\n", i, y);

        }
    }

    // (x; y) up-right diagonal
    for(int i=x-1; i>=0; i--){
        if(y+x-i>=n)
            break;
        if(*(matrix+i*n*3+(y+x-i)*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y+x-i)*3+2)=player_id;
            score+=*(matrix+i*n*3+(y+x-i)*3+0);
            printf("Moving to %d:%d\n", i, y+x-i);

        }

    }

    // (x; y) up-left diagonal
    for(int i=x-1; i>=0; i--){
        if(y-(x-i)<0)
            break;
        if(*(matrix+i*n*3+(y-(x-i))*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y-(x-i))*3+2)=player_id;
            score+=*(matrix+i*n*3+(y-(x-i))*3+0);
            printf("Moving to %d:%d\n", i, y-(x-i));

        }
    }

    // (x; y) down-right diagonal
    for(int i=x+1; i<m; i++){
        if(y+i-x>=n)
            break;
        if(*(matrix+i*n*3+(y+i-x)*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
           *(matrix+i*n*3+(y+i-x)*3+2)=player_id;
            score+=*(matrix+i*n*3+(y+i-x)*3+0);
            printf("Moving to %d:%d\n", i, y+i-x);

        }
    }

    // (x; y) down-left diagonal
    for(int i=x+1; i<m; i++){
        if(y-(i-x)<0)
            break;
        if(*(matrix+i*n*3+(y-(i-x))*3+2)!=0)
            break;
        counter++;
        if(z==counter-1){
            *(matrix+x*n*3+y*3+2)=0;
            *(matrix+i*n*3+(y-(i-x))*3+2)=player_id;
            score+=*(matrix+i*n*3+(y-(i-x))*3+0);
            printf("Moving to %d:%d\n", i, y-(i-x));
        }
    }


    for (int i = 0; i < m; i++)
    {    for (int j = 0; j < n; j++)
          printf("%d%d%d ", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));
        printf("\n");
    }
    printf("\n");
    if(z>=0){
        return 0;
    }
    return counter;
}

int fill_matrix(){
    int f=0;
    char *token;
    matrix=(int*)malloc(m*n*3*sizeof(int));

    fseek(fp, 0, SEEK_SET);  //reset file cursor to the beginning
    getline(&line,&len, fp); //skip first row/line

    i=0;

    printf("===Old Board===\n");

    while (i<m) {

        getline(&line,&len, fp);   //get a line
        printf(line);
        token = strtok(line, " ");  //get first column first row

        *(matrix+i*n*3+0*3+0)=token[0]-'0'; // -'0' to convert char to int
        *(matrix+i*n*3+0*3+1)=token[1]-'0';
        *(matrix+i*n*3+0*3+2)=token[2]-'0';

        if(token[2]=='0')  //if it is like 490 or 240
            f++;
        else if(token[2]==player_id+'0')
            N++;

        //get the rest columns
        for(int k=1; k<n; k++)
        {
            token=strtok(NULL, " ");

            *(matrix+i*n*3+k*3+0)=token[0]-'0'; // -'0' to convert char to int
            *(matrix+i*n*3+k*3+1)=token[1]-'0';
            *(matrix+i*n*3+k*3+2)=token[2]-'0';

             if(token[2]=='0')  //if it is like 490 or 240
                f++;
            else if(token[2]==player_id+'0')
                N++;
        }
        i++;
    }
    printf("\n");
    // for (int i = 0; i < m; i++)
    // {    for (int j = 0; j < n; j++)
    //       printf("%d%d%d ", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));
    //     printf("\n");
    // }

    if(f==0)
        return 1;

    return 0;
}

int move(){
    //if no free cells
    if(fill_matrix()==1)
        return 1;

label1:
    //choose random amazon
    srand(time(0));
    int my_rand=rand()%N;
    //printf("%d\n", my_rand);

    int q=0;
    int x,y;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(*(matrix + i*n*3 + j*3+2)==player_id){
                if(q==my_rand){
                    x=i;
                    y=j;
                }
                q++;
            }
        }
    }

    printf("Moving amazon from  %d: %d\n", x, y);


    int i=get_or_move_possible_movements_amazon(x,y,-1); //-1 means get number of possible movement coordinates for amazon (x;y)
    if (i==0) goto label1;
    srand(time(0));
    int my_rand2=rand()%i;

    //move a possible my_rand2 th move
    if(get_or_move_possible_movements_amazon(x,y, my_rand2)==0)
    {
        //write to outputboard file
            //if inputboard and outputboard are not the same files
        if(strcmp(inputboard, outputboard)!=0){

            fp2 = fopen(outputboard, "w");   //open in write mode
            fprintf(fp2, "%d %d\n", m, n);

            for (int i = 0; i < m; i++)
            {
                for (int j = 0; j < n-1; j++)
                    fprintf(fp2, "%d%d%d ", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));

                int j=n-1;
                fprintf(fp2, "%d%d%d", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));

                fprintf(fp2, "\n");

            }
            //fprintf(fp2, "\n");

            fseek(fp, 0, SEEK_SET);  //reset file pointer/cursor to the beginnig
            i=0;
            while ( getline(&line,&len, fp) != -1) {
                i++;
                if(i>=(m+2)){
                    char orig_line[strlen(line)];
                    strcpy(orig_line, line);

                    char *name = strtok(line, " ");

                    if(strcmp(name, players_name)!=0){
                        fprintf(fp2, "%s", orig_line);
                    }
                    else{
                            //convert score to str
                            char score_str[12];
                            sprintf(score_str, "%d", score);

                            char* id=strtok(NULL, " ");
                            memcpy(orig_line+strlen(name)+1+strlen(id)+1,score_str, strlen(score_str));
                            fprintf(fp2, "%s",orig_line);
                    }
                }
            }

        }else{
            fseek(fp, 0, SEEK_SET);  //reset file pointer/cursor to the beginning

            getline(&line,&len, fp);  //skip first row


            for (int i = 0; i < m; i++)
            {

                for (int j = 0; j < n-1; j++){
                    fprintf(fp, "%d%d%d ", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));
                }

                int j=n-1;
                fprintf(fp, "%d%d%d", *(matrix + i*n*3 + 3*j+0), *(matrix + i*n*3 + 3*j+1), *(matrix + i*n*3 + 3*j+2));

                fprintf(fp, "\n");
            }


            while (getline(&line,&len, fp) != -1)
            {
                char orig_line[strlen(line)];
                strcpy(orig_line, line);

                char *name = strtok(line, " ");

                if(strcmp(name, players_name)==0){
                    fseek(fp, -(strlen(orig_line)), SEEK_CUR);
                    char* id=strtok(NULL, " ");
                    fprintf(fp, "%s %s %d", name, id, score);
                }
            }

        }

    }
}
