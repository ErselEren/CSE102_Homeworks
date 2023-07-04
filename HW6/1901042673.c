#include <stdio.h>
#include <time.h>
#define N 3

typedef enum{notfree,left,right,up,down,stop} directiont;

/*-----------------------------------FUNCTION DEFINITIONS------------------------------------*/
void move_puzzle_left(int array[][N],int* indR,int* indC, int* position);
void move_puzzle_right(int array[][N],int* indR,int* indC, int* position);
void move_puzzle_up(int array[][N],int* indR,int* indC, int* position);
void move_puzzle_down(int array[][N],int* indR,int* indC, int* position);
void print_puzzle(int array[][N]);
directiont check_move(int array[][N], directiont direction, int* indR, int* indC, int* position);
/*----------------------------------------------------------------------------------------------*/

int main(){
    /* srand((unsigned)time(NULL)); */
    directiont choice;
    
    int size,i,j,z,index,counter,game; 
    int change1,change2,change3,change4; /* variables to mix array */
    int puzzle[N][N]; 
    int temp[1][1]; /* temp variable to mix array */
    int row,column;
    counter = 0;
    size = N*N-1;
    
    /* sorting puzzle */
    for(i=0;i<N;i++){
        for(j=0;j<N;j++,size--){
            puzzle[i][j] = size;
        }
    }
    /* mixing numbers */
    for(i=0;i<N*N;i++){
        change1 = rand()%N+0;
        change2 = rand()%N+0;
        change3 = rand()%N+0;
        change4 = rand()%N+0;

        temp[0][0] = puzzle[change1][change2];
        puzzle[change1][change2] = puzzle[change3][change4];
        puzzle[change3][change4] = temp[0][0];
    }

    /*====printing table==========*/
    print_puzzle(puzzle);
    /*============================*/

    game = 1;
    /* if game is 0, game is completed , if game is 1 it continues to get input */
    do{ 
        for(i=0;i<N;i++){ /*checking every square according to i*N +j+1 formula*/
            for(j=0;j<N;j++){
                if(puzzle[i][j]==((i*N)+j+1)){
                    counter++;
                }
            }
        }
        if(counter==(N*N-1)){
            printf("\n**********YOU WON THE GAME***********\n");
            game = 0;
        }
        else counter=0; 
        
        if(game==1){ /* getting move direction */
            printf("\n1-Left  ,  2-Right   ,  3-Up  ,  4-Down  , 5-STOP ===> ");
            scanf("%u",&choice);
        if(choice==stop){ /*getting coordinates until user input stop */
           break;
        }
        printf("\nEnter location for row and column(1 for first line, 2 for second line...)>>> ");
        scanf("%d %d",&row,&column);
        row = row - 1;
        column = column - 1;
        switch (check_move(puzzle,choice,&row,&column,&index)){ /*calling functions here to check move */
          /* if the move is valid, it returns an direction or notfree */
          case left:
             move_puzzle_left(puzzle,&row,&column,&index);
             break;
          case right: 
             move_puzzle_right(puzzle,&row,&column,&index);                       
             break;   
          case up:
             move_puzzle_up(puzzle,&row,&column,&index);
             break;
          case down: 
             move_puzzle_down(puzzle,&row,&column,&index);
             break;
          case notfree: 
             printf("------------------------");
             printf("\n!-!-!-INVALID MOVE-!-!-!\n");
             printf("------------------------\n");
             print_puzzle(puzzle);
             break;
          }
        }
        

    }while(game==1);
    
    return 0;
    /********************************************END OF MAIN***********************************************************/
}

directiont check_move(int array[][N], directiont direction, int* indR, int* indC, int* position){

    int i,status,index,step_size;
    status = 0;
    /*==============================================================*/
    /*==============================================================*/

    if(direction==left){ /* for left direction */
        step_size = *indC; /*iteration*/

        /* checking if there is a space to left from chosen coordinates */
        for(i=step_size;i>0;i--){
            if(array[*indR][i-1]==0){
              *position = i-1; /*also we return index of space */
              status = 1;
              i = 0;
            }     
            else
              status = 0;  
        }
        /*returning values according to status of puzzle */
        if(status == 0)
           return notfree;
        if(status == 1)
            return left;     
    }
    /*==============================================================*/
      
    if(direction==right){ /* for right direction */
        
        step_size = *indC;
        step_size = N-1-step_size; 
        
        /* checking if there is a space to right from chosen coordinates */
        for(i=1;i<=step_size;i++){
            if(array[*indR][*indC+i]==0){ 
              *position = *indC+i;   /*also we return index of space */     
               status = 1; 
               i = 101;
            }
            else{ 
               status = 0; 
            }
        }
        /*returning values according to status of puzzle */
        if(status == 0)
           return notfree;
        if(status == 1)
           return right;   
    }
    /*==============================================================*/
    
    if(direction==up){
        step_size = *indR;

       /* checking if there is a space to up from chosen coordinates */
        for(i=step_size;i>0;i--){
            if(array[i-1][*indC]==0){
              *position = i-1; /*also we return index of space */ 
              status = 1;
              i = 0;
            }     
            else
              status = 0;  
        }
        /*returning values according to status of puzzle */
        if(status == 0)
           return notfree;
        if(status == 1)
            return up; 
    }
    /*==============================================================*/
    /*==============================================================*/
    
    if(direction==down){
        step_size = *indR;
        step_size = N-1-step_size; /* stepsize, seçilen koordinat ile boşluk arasındaki mesafe */
        
        /* checking if there is a space to down from chosen coordinates */
        for(i=1;i<=step_size;i++){
            if(array[*indR+i][*indC]==0){ 
              *position = *indR+i;    /*also we return index of space */     
               status = 1; 
               i = 101;
            }
            else{ 
               status = 0; 
            }
        }
        /*returning values according to status of puzzle */
        if(status == 0)
           return notfree;
        if(status == 1)
           return down;   
    }
}

void move_puzzle_right(int array[][N],int* indR,int* indC, int* position){
    int count,i;
    count = *position - (*indC); 
    int temp,flag;
    /* find count and iterate loop, change numbers by using temporary variable */
    for(i=0;i<count;i++){
        temp = array[*indR][*position-i-1];
        array[*indR][*position-i]= temp; 
    }
    array[*indR][*indC] = 0; /* then make '0' chosen coordinate */
    print_puzzle(array); /* in the end print puzzle */
}
void move_puzzle_left(int array[][N],int* indR,int* indC, int* position){
    int count,i,temp;
    count = (*indC)-(*position);
    for(i=0;i<count;i++){
        temp = array[*indR][*position+i+1];
        array[*indR][*position+i] = temp;
    }
    array[*indR][*indC] = 0;
    print_puzzle(array);
}
void move_puzzle_up(int array[][N],int* indR,int* indC, int* position){
    int count,i,temp;
    count = (*indR)-(*position);
    for(i=0;i<count;i++){
        temp = array[*position+i+1][*indC];
        array[*position+i][*indC] = temp;
    }
    array[*indR][*indC] = 0;
    print_puzzle(array);

}
void move_puzzle_down(int array[][N],int* indR,int* indC, int* position){
    int count,i;
    count = *position - (*indR);
    int temp,flag;
    for(i=0;i<count;i++){
        temp = array[*position-i-1][*indC];
        array[*position-i][*indC]= temp; 
    }
    array[*indR][*indC] = 0;
    print_puzzle(array);
}
void print_puzzle(int array[][N]){
    int i,j,z;
    /* stars of top */
    for(i=0;i<5*N+1;i++){
        printf("*");
    }
    printf("\n");
    /* from N to N print stars and numbers */
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf("*");
            if(array[i][j]==0){
                printf("    ");
                if(j==N-1)
                printf("*");
            }
            else{
                printf(" %-3d",array[i][j]);
                if(j==N-1)
                printf("*");
            }
        }
        printf("\n");
        
        for(z=0;z<5*N+1;z++) /*stars of bottom*/
        printf("*");
        
        printf("\n");
    }

}


