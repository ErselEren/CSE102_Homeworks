/*
  I assume that, in Movies.txt file , line 736 is deleted. Because that line,
  has not any year value. If you get seg. fault you can delete line 736.
  
  Also my program find an order at the beginning,
  so order doesn't have to be like budget,genre,name,score,year, it can be whatever you want.  
  
  Then, I creating nodes according to year and budget(in year equality), 
  so after reading file, list is ordered in descending for year.

  When you enter value in listing, for example if you enter 1999 for start, 2004 for end, program prints 1999's and 2004's movies as well.
  Excluding and including boundaries is just a matter of " <= / < " sign in loop. So, I preferred including boundary values.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWNUMBER 5
#define MAX 100

/*------declaring structs------*/
struct Movie_Budget{
    int budget;
    int year;
    char *name;
    struct Movie_Budget *link;
};

struct Movie_Name{
    double score;
    char *genre;
    char *name;
    struct Movie_Name *link;
};

typedef struct {
    int budget;
    char *genre;
    char *name;
    double score;
    int year;
}bufferMovie;

struct Genre{
    char *genre;
    int counter;
    struct Genre *link;
};
/*-----------------------------*/

/*---------------------------FUNCTION DECLARATIONS----------------------------*/
bufferMovie decompose(char *p1, int *order);
void print_menu();
void order_row(char *p1,int *order);
void movie_function(char *filename);
void check_genre(int *tgenreCounter, char*** t_genre, char* genre);
void get_lines(char *filename, struct Movie_Budget **headBudget,struct Movie_Name **headName);
void find_average_imdb(struct Movie_Name **headName);
void frequence_genre(struct Movie_Name **headName);
void all_info(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void print_sorted_year(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void print_sorted_score(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void print_sorted_budget(struct Movie_Name ***headName, struct Movie_Budget ***headBudget);
void print_sorted_name_genre(struct Movie_Name ***headName, struct Movie_Budget ***headBudget);
void print_sorted_year2(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void print_sorted_score2(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void list_through_years(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void list_through_budget(struct Movie_Name ***headName, struct Movie_Budget ***headBudget);
void list_through_genre(struct Movie_Name ***headName, struct Movie_Budget ***headBudget);
void list_through_name(struct Movie_Name ***headName, struct Movie_Budget ***headBudget);
void list_sorted_data(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void list_through_score(struct Movie_Name **headName, struct Movie_Budget **headBudget);
void delete_node(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName);
void sorted_insert(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName);
void list_genres(struct Movie_Name **headName);
void swap_movies(struct Movie_Budget *ptrBudget,struct Movie_Name *ptrName,struct Movie_Budget *tempBudget,struct Movie_Name *tempName);
void free_list(struct Movie_Name **headName, struct Movie_Budget **headBudget);
int check_name(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName);
/*----------------------------------------------------------------------------*/

int main(){
    char *filename = "Movies.txt";
    movie_function(filename);
    return 0;
}

/*this function calls get_lines and then get menu inputs*/
void movie_function(char *filename){
    /*--declaring variables--*/
      int flag,command;
      char x;
    /*---------------declaring pointers for each linked list-----------------*/
    struct Movie_Budget *headBudget = calloc(1,sizeof(struct Movie_Budget));
    struct Movie_Name *headName = calloc(1,sizeof(struct Movie_Name));
    struct Movie_Budget *ptrBudget;
    struct Movie_Name *ptrName;
    /*--------------------filling first node of list-----------------------*/
     headBudget->name = calloc(sizeof(char),MAX);
     headName->name = calloc(sizeof(char),MAX);
     headName->genre = calloc(sizeof(char),MAX);
     headBudget->budget = 3333333333;
     headBudget->year = 9999;
     headName->score = -1;
     headBudget->link = NULL;
     headName->link = NULL;
     strcpy(headBudget->name,"budgetMoviename");
     strcpy(headName->name,"nameMoviename");
     strcpy(headName->genre,"genreMoviename");
    /*--------------------creating list line by line-------------------------*/
      get_lines(filename,&headBudget,&headName);
      headBudget->budget = -1;
      headBudget->year = -1;
    /*----------------------------------MENU---------------------------------*/
     while(flag){
        print_menu();
        scanf("%d",&command);
        x = getchar();
        switch(command)
        {
            case 1:
              list_sorted_data(&headName,&headBudget);
              break;
            case 2:
              list_genres(&headName);
              break;
            case 3:
              list_through_years(&headName,&headBudget);
              print_sorted_year(&headName,&headBudget);
              break;
            case 4:
              list_through_score(&headName, &headBudget);
              print_sorted_score(&headName,&headBudget);
              break;
            case 5:
              all_info(&headName,&headBudget);
              break;
            case 6:
              find_average_imdb(&headName);
              break;
            case 7:
              frequence_genre(&headName);
              break;   
            case 8:
                printf("\nProgram Has Terminated\n");
                flag = 0;          
                /*freeing list before terminate*/
                free_list(&headName,&headBudget);
                break;
            default:
                printf("\n ! Please Enter Valid Command ! ");
                break;                       
        }
    }
    /*------------------------------------------------------------*/
}

/*freeing list*/
void free_list(struct Movie_Name **headName, struct Movie_Budget **headBudget){  
    /*creating temp pointer to free list*/
    struct Movie_Budget *freeBudget;
    struct Movie_Name *freeName;
    /*shifting head pointer and freeing previous one*/
     while((*headBudget)!=NULL){
                  freeBudget = (*headBudget);
                  freeName = (*headName);
                  (*headBudget) = (*headBudget)->link;
                  (*headName) = (*headName)->link;
                  free(freeBudget->name);
                  free(freeName->name);
                  free(freeName->genre);
                  free(freeBudget);
                  free(freeName);     
     }
}

/*this function handles getting lines, decomposing and adding them to list*/
void get_lines(char *filename, struct Movie_Budget **headBudget,struct Movie_Name **headName){
    /*-----------------Declarations-----------------*/
       char c;
       char *p1, *p2=NULL;
       int length,i,j,flag,row,genreFlag,nameFlag;
       int movieCounter=0;
       int *order;
       bufferMovie buffer;
       flag = 1; length = 0;  row = 0;
       order = calloc(ROWNUMBER*sizeof(int),1);
    /*----------------------------------------------*/
    
    /*error message if file couldn't open*/
        FILE *fp = fopen(filename,"r");
        if(fp == NULL){
           printf("File couldn't open ");
        }
    /*-----------------------------------*/
    
    /*----------------------------reading char by char----------------------------*/
    while(flag==1){  
          c = fgetc(fp);
          length++;
          
          /*EOF control*/
          if(c==EOF) flag = 0;
          
          /*when it reads new line, decompose it*/
          if(c=='\n'){
             /*finding order of text at first line*/
             if(row==0) order_row(p1,order); 

             /*------------decomposing and adding to list------------------------*/
             else{ 
                buffer = decompose(p1,order); /*decomposing line into buffer*/
                
                /*-------------------checking name-----------------------*/
                nameFlag = check_name(buffer,headBudget,headName);
                
                /*there isn't any movie with this name*/
                /*adding new movie according to year and budget*/
                if(nameFlag == -1) sorted_insert(buffer,headBudget,headName);
            
                /*this name is in the list, it'll be updated*/
                if(nameFlag == -2){
                    /*first we delete that node*/
                    delete_node(buffer,headBudget,headName);
                    /*then adding new movie according to year and budget*/
                    sorted_insert(buffer,headBudget,headName);
                }
                /*--------------------END OF LINE------------------------*/  
             }
             length=0; row++;
          }
          /*reading and allocating memory for each character that we read*/
           if(c!=EOF&&c!='\n'&&c!='\r'){ 
             p1 = calloc(length+1,sizeof(char));
             for(i=0;i<length-1;i++) p1[i] = p2[i];
             
             p1[length-1] = c;
             
             if(p2!=NULL) free(p2);
             
             p2 = p1;  
           }
    }
    fclose(fp);
    /*--------------------------End Of While--------------------------------------*/
}

/*creating an order array according to first line*/
void order_row(char *p1, int *order){
    int flag,i,j,k;
    char *buffer;
    /*iterate 5 times and decide order*/
    for(i=0;i<5;i++){   
        buffer = calloc(10,sizeof(char));
        for(j=0;j<10;j++){
            if(p1[j]==','||p1[j]=='\0'||p1[j]=='\n'){
                strncpy(buffer,p1,j);
                p1 = p1 + j+1;
                break;
            }
        }
        
        if(strcmp(buffer,"budget")==0)
            order[i]=1;  
        if(strcmp(buffer,"genre")==0)
            order[i]=2;  
        if(strcmp(buffer,"name")==0)
            order[i]=3;
        if(strcmp(buffer,"score")==0)
            order[i]=4;
        if(strcmp(buffer,"year")==0)
            order[i]=5;
           
        free(buffer);
    }
}

/*decompose line according to order of informations*/
bufferMovie decompose(char *p1,int *order){
     bufferMovie buffer;
     int i,j;
     float n1,n2;
     
    for(j=0;j<5;j++){
        if(order[j]==1){ /*decomposing for budget*/
           if(p1[0]!='u'){
           buffer.budget = strtod(p1,&p1);
           if(j!=4) 
              p1 = p1 +1;
           }else{
           buffer.budget = -1;   
           if(j!=4) 
              p1 = p1 + 8;  
           
           }
        }
        if(order[j]==2){ /*decomposing for genre*/
            i = 0;
            while(1){
                if(p1[i]==','||p1[i]=='\n'||p1[i]=='\0'){
                  buffer.genre = (char*)calloc(i+1,1);
                  strncpy(buffer.genre,p1,i);
                  break;
                }
                i++;
            }
            if(j!=4) 
               p1 += i+1;
        
        }
        if(order[j]==3){ /*decomposing for name*/
            i = 0;
            while(1){
                if(p1[i]==','||p1[i]=='\n'||p1[i]=='\0'){
                   buffer.name = (char*)calloc(i+1,1);
                   strncpy(buffer.name,p1,i);
                   break;
                }
                i++;
            }
            if(j!=4) 
               p1 = p1 + i +1;
        }
        if(order[j]==4){ /*decomposing for score*/
           n1 = p1[0]-48;
           n2 = p1[2]-48;
           buffer.score = (n1*10+n2)/10;
           if(j!=4) 
              p1 = p1 + 4;
        }
        if(order[j]==5){ /*decomposing for year*/
            buffer.year = (p1[0]-48)*1000 + (p1[1]-48)*100 + (p1[2]-48)*10 + (p1[3]-48);
            if(j!=4) 
               p1 = p1 + 5;
        }
    }
    return buffer; /*after decompose, we return buffer*/
}

/*we use this function for every movie to insert according to year and budget*/
void sorted_insert(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName){
    /*-----------------allocating memory for new movie--------------------*/
     struct Movie_Budget *stBudget = calloc(1,sizeof(struct Movie_Budget));
     struct Movie_Name *stName = calloc(1,sizeof(struct Movie_Name));
    /*I arbitrary give a MAX size for name and genre according to second page first sentence in PDF*/
     stBudget->name = calloc(1, MAX);
     stName->name = calloc(1, MAX);
     stName->genre = calloc(1, 25);
    /*---------------copying values to node from buffer-------------------*/
    stBudget->budget = buffer.budget;
    stBudget->year = buffer.year;
    stName->score = buffer.score;
    stBudget->link = NULL;
    stName->link = NULL;
    strcpy(stBudget->name,buffer.name);
    strcpy(stName->name,buffer.name);
    strcpy(stName->genre,buffer.genre);
    /*--------------inserting according to year and budget---------------*/
     /*we use 2 pointer to insert new node between two node*/
     struct Movie_Budget *ptrBudget;
     struct Movie_Name *ptrName;
     struct Movie_Budget *tempBudget;
     struct Movie_Name *tempName;
     tempBudget = NULL; tempName = NULL; ptrBudget = NULL; ptrName = NULL;
     tempBudget = *headBudget;
     tempName = *headName;
     int flag = 1;
     
     
     /*if there is only head pointer*/
     if(tempBudget->link == NULL){
        tempBudget->link = stBudget;
        tempName->link = stName;
        flag = 0;
     }
     /*else we start checking from next node*/
     else{
        ptrName = tempName->link;
        ptrBudget = tempBudget->link;
     }
     /*here we start searching for true position*/
     while(flag){ 
        if(ptrBudget->year>buffer.year){ /*if current index's year is bigger than new movie's year*/
            if(ptrBudget->link == NULL){ /*checking NULL situations*/
                ptrBudget->link = stBudget;
                ptrName->link = stName;
                break;
            }
            else{ /*skipping this node*/
            ptrBudget = ptrBudget->link;
            ptrName = ptrName->link;
            tempName = tempName->link;
            tempBudget = tempBudget->link;
            }
        }
        if(ptrBudget->year == buffer.year){ /*if current index's year is equal to new movie's year*/
            while(1){ /*here we are sorting according to budgets*/
              if(ptrBudget->budget>buffer.budget){
                if(ptrBudget->link==NULL){
                    ptrBudget->link = stBudget;
                    ptrName->link = stName;
                    break;
                }
                if(ptrBudget->link!=NULL){/*checking NULL situations*/
                    tempBudget = tempBudget->link;
                    tempName = tempName->link;
                    ptrBudget = ptrBudget->link;
                    ptrName = ptrName->link;
                    if(ptrBudget->year != buffer.year){
                        tempBudget->link = stBudget;
                        tempName->link = stName;
                        stBudget->link = ptrBudget;
                        stName->link = ptrName;
                        break;
                    }
                }
              }
              if(ptrBudget->budget<=buffer.budget){/*if current index's budget is less than new movie's budget*/
                tempBudget->link = stBudget;
                tempName->link = stName;
                stBudget->link = ptrBudget;
                stName->link = ptrName;
                break;
              }
            }
            break;
        }
        if(ptrBudget->year<buffer.year){ /*if current index's year is less than new movie's year*/
            tempBudget->link = stBudget;
            tempName->link = stName;
            stBudget->link = ptrBudget;
            stName->link = ptrName;
            break;
        }
    }
}

/*we use this function when there is a movie with same name*/
void delete_node(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName){
    /*----------------declaring pointers to make operations----------------*/
     struct Movie_Budget *ptrBudget;
     struct Movie_Name *ptrName;
     struct Movie_Budget *tempBudget;
     struct Movie_Name *tempName;
     tempBudget = NULL; tempName = NULL; ptrBudget = NULL; ptrName = NULL;
     tempBudget = *headBudget;
     ptrBudget = tempBudget->link;
     tempName = *headName;
     ptrName = tempName->link;
    /*---------------------------------------------------------------------*/
    while(1){/*iterate until we find a match*/
        if(strcmp(ptrBudget->name,buffer.name)==0){
            break;
        }
        ptrName = ptrName->link;
        ptrBudget = ptrBudget->link;
        tempName = tempName->link;
        tempBudget = tempBudget->link;
    }
    tempBudget->link = ptrBudget->link;
    tempName->link = ptrName->link;

}

/*checking whether movie with that name is in list or not*/
int check_name(bufferMovie buffer,struct Movie_Budget **headBudget,struct Movie_Name **headName){
    struct Movie_Budget *ptrBudget;
    struct Movie_Name *ptrName;
    ptrBudget = NULL;
    ptrBudget = *headBudget;
    while(1){
         if(strcmp(ptrBudget->name,buffer.name)==0){
            return -2;/*return -2 when we find*/
         }
         if(ptrBudget->link == NULL){
            return -1; /*it returns -1 when we came to end of list*/
         }   
         ptrBudget = ptrBudget->link;
    }
}

/*printing main menu*/
void print_menu(){
    printf("\n----------------------------------------");
    printf("\n 1-List of the Sorted Data\n 2-List of the Genres\n 3-List of the Movie Through the Years\n 4-List of the Movie Through the Scores");
    printf("\n 5-All Informations of a Single Movie\n 6-Average of the IMDB Scores\n 7-Frequence of the Genres \n 8-EXIT\n");
    printf("----------------------------------INPUT: ");
}

/*it calculates average imdb scores*/
void find_average_imdb(struct Movie_Name **headName){
    /*----variable declarations----*/
     struct Movie_Name *ptr = NULL;
     double sum = 0;
     int counter = 0;
     ptr = *headName;
    /*-----------------------------*/
    /*adding scores to sum until NULL*/
      while(1){
         if(ptr->link == NULL){
            sum += ptr->score;
            counter++;
            break;
         }
         else{
            counter++;
            sum += ptr->score;
         }
         ptr = ptr->link;
      }
      printf("\n Average of IMDB Scores ==> %f",(sum+1)/counter);
    /*======================END OF FUNCTION===================== */ 
}

/*printing all genres*/
void list_genres(struct Movie_Name **headName){
    /*---------variable declarationgs----------*/
     char *genre,**t_genre = NULL,**temp = NULL;
     int genreFlag,tgenreCounter,flag,j,i=0;
     struct Movie_Name *ptr = NULL;
    /*-----------------------------------------*/
    
    /*arbitrary length for genre*/
    genre = calloc(sizeof(char),20);
    ptr = *headName;
    tgenreCounter = 0;
    
    /*------checking every genre of list--------*/
    while(1){  
        i=0; flag = 0;
       /*----checking genre in t_genre array----*/
        while(i<tgenreCounter){
          if(strcmp(ptr->genre,t_genre[i])==0){
              flag = 1;
              break;
          }
          i++; 
        }
       /*-----if genre is not in array we expand array----*/
       if(flag==0){
           temp = t_genre;
           tgenreCounter++;
           t_genre = calloc(tgenreCounter,(sizeof(char*)));
           j=0;
           while(j<tgenreCounter-1){
              t_genre[j] = temp[j]; 
              j++;
           }
           free(temp);
           t_genre[j] = calloc(20,sizeof(char));
           strcpy(t_genre[j],ptr->genre);
       }
       /*--------------------------------------------------*/
       /*then go to next node*/
         if(ptr->link==NULL){
           break;
         }
         ptr = ptr->link;
    }
    
    /*-----------printing genres----------*/
      for(i=1;i<tgenreCounter;i++)
         printf("\n-----> %s ",t_genre[i]);
      
    /*-------freeing t_genre memory-------*/
      for(i=0;i<tgenreCounter;i++){
        free(t_genre[i]);
      }
      free(t_genre);
    /*============END OF FUNCTION==========*/  
}

/*prints all informations of a chosen movie*/
void all_info(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    /*--------declaring variables---------*/
     char *name = calloc(MAX,sizeof(char));
     int flag = 1;
     struct Movie_Name *ptrName = NULL;
     struct Movie_Budget *ptrBudget = NULL;
     ptrName = *headName;
     ptrBudget = *headBudget;
    /*------------------------------------*/
    
    /*getting input until we find a name from list*/
     while(flag){
        printf("\n Enter a movie name : ");
        scanf(" %[^\n]",name);
       
       /*-------search the name in list-------*/
        while(1){
            if(strcmp(name,ptrName->name)==0){
                if(ptrBudget->budget == -1) printf("\n Budget = Unknown");
                else printf("\n Budget = %d ",ptrBudget->budget);
                printf("\n Name : %s \n Score : %.2f ",ptrName->name,ptrName->score);
                printf("\n Year : %d \n Genre : %s",ptrBudget->year,ptrName->genre);
                flag = 0;
                break;
            }
            if(ptrName->link == NULL)
                break;
        
            ptrBudget = ptrBudget->link;
            ptrName = ptrName->link;

        }
        if(flag==1) printf("\n !-!-There is no movie with this name-!-! ");  
     }
    /*=========================END OF FUNCTION===========================*/
}

/*sorting years in ascending order*/
void list_through_years(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    /*-------declaring necessary variables-------*/
     struct Movie_Name *ptrName = NULL;
     struct Movie_Budget *ptrBudget = NULL;
     struct Movie_Budget *tempBudget = NULL;
     struct Movie_Name *tempName = NULL;
    /*-------------------------------------------*/
     ptrName = *headName;
     ptrBudget = *headBudget;
     
     /*sorting list for year*/
     while(ptrBudget!=NULL){
        tempBudget = ptrBudget->link;
        tempName = ptrName->link;
        while(tempBudget != NULL){
            if(ptrBudget->year > tempBudget->year) swap_movies(ptrBudget,ptrName,tempBudget,tempName);
            tempBudget = tempBudget->link;
            tempName = tempName->link;
        }
        ptrBudget = ptrBudget->link;
        ptrName = ptrName->link;
     }
}

/*sorting score in ascending order*/
void list_through_score(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    /*-------declaring necessary variables-------*/
     struct Movie_Name *ptrName = NULL;
     struct Movie_Budget *ptrBudget = NULL;
     struct Movie_Budget *tempBudget = NULL;
     struct Movie_Name *tempName = NULL;
    /*-------------------------------------------*/
    ptrName = *headName;
    ptrBudget = *headBudget;
    
    /*sorting for score*/
    while(ptrBudget!=NULL){
        tempBudget = ptrBudget->link;
        tempName = ptrName->link;
        while(tempBudget != NULL){
            if(ptrName->score > tempName->score) swap_movies(ptrBudget,ptrName,tempBudget,tempName);
            tempBudget = tempBudget->link;
            tempName = tempName->link;
        }
        ptrBudget = ptrBudget->link;
        ptrName = ptrName->link;
    }
    ptrName = *headName;
}

/*swapping datas of two node*/
void swap_movies(struct Movie_Budget *ptrBudget,struct Movie_Name *ptrName,struct Movie_Budget *tempBudget,struct Movie_Name *tempName){
    char *bufferName, *bufferGenre;
    int bufferYear, bufferBudget;
    double bufferScore;
    bufferName = calloc(sizeof(char),MAX);
    bufferGenre = calloc(sizeof(char),20);
    /*------------for ptrBudget-------------*/
    bufferYear = ptrBudget->year;
    bufferBudget = ptrBudget->budget;
    strcpy(bufferName,ptrBudget->name);
    ptrBudget->year = tempBudget->year;
    ptrBudget->budget = tempBudget->budget;
    strcpy(ptrBudget->name,tempBudget->name);
    tempBudget->budget = bufferBudget;
    tempBudget->year = bufferYear;
    strcpy(tempBudget->name,bufferName);
    /*------------for ptrName---------------*/
    bufferScore = ptrName->score;
    strcpy(bufferGenre,ptrName->genre);
    strcpy(bufferName,ptrName->name);
    ptrName->score = tempName->score;
    strcpy(ptrName->genre,tempName->genre);
    strcpy(ptrName->name,tempName->name);
    tempName->score = bufferScore;
    strcpy(tempName->genre,bufferGenre);
    strcpy(tempName->name,bufferName);
    /*--------------------------------------*/
}

/*printing frequences of genres*/
void frequence_genre(struct Movie_Name **headName){
    /*----------------declaring variables---------------*/
     int flag1 = 1,flag2 = 1;
     struct Movie_Name *ptrName = NULL;
     struct Genre *ptrGenre = NULL;
     struct Genre *Genre = calloc(1,sizeof(struct Genre));
    /*--------------------------------------------------*/
     ptrName = *headName;
     ptrGenre = Genre;
     Genre->genre = calloc(20,sizeof(char));
     strcpy(Genre->genre,"Genres");
    
    /*we are checking genres by using Genre list*/
    while(flag1){
        while(1){
            if(strcmp(ptrName->genre,ptrGenre->genre)==0){
                ptrGenre->counter++;
                ptrGenre = Genre;
                break;
            }
            if(ptrGenre->link == NULL){
                struct Genre *newNode = calloc(1,sizeof(struct Genre));
                newNode->genre = calloc(20,sizeof(char));
                newNode->link = NULL;
                strcpy(newNode->genre,ptrName->genre);
                ptrGenre->link = newNode;
                ptrGenre = Genre;
                break;
            }
            ptrGenre = ptrGenre->link;
        }
        
        
        if(ptrName->link == NULL){
            flag1 = 0;
        }
        ptrName = ptrName->link;
    }
    
    /*----------------------------printing our results------------------------------*/
    ptrGenre = Genre;
    ptrGenre = ptrGenre->link->link;
    while(ptrGenre->link != NULL){
        printf("\n ----> %s ---------> %d ",ptrGenre->genre,(ptrGenre->counter)+1);
        ptrGenre = ptrGenre->link;
    }
    printf("\n ----> %s ---------> %d ",ptrGenre->genre,(ptrGenre->counter)+1);
}

/*-------------------------------------submenu----------------------------------------*/
void list_sorted_data(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    int command,flag;
    flag = 1;

    /*here we call helper functions*/
    while(flag){ 
        printf("\n 1-Budget\n 2-Genre\n 3-Name\n 4-Score\n 5-Year \n----> ");
        scanf("%d",&command);
        switch (command)
        {
            case 1:
               list_through_budget(&headName,&headBudget);
               print_sorted_budget(&headName,&headBudget);
               flag=0;
               break;
            case 2:
               list_through_genre(&headName,&headBudget);
               print_sorted_name_genre(&headName,&headBudget);
               flag=0; 
               break;
            case 3:
               list_through_name(&headName,&headBudget); 
               print_sorted_name_genre(&headName,&headBudget);
               flag=0;           
               break;
            case 4:
               list_through_score(headName,headBudget);
               print_sorted_score2(headName,headBudget);
               flag=0;
               break;
            case 5:
               list_through_years(headName,headBudget);
               print_sorted_year2(headName,headBudget);
               flag=0;
               break;
            default:
               printf("\n Please Enter Valid Command "); 
               break;
        }
    }    
    
}

/*printing list after sorting*/
void print_sorted_year(struct Movie_Name **headName, struct Movie_Budget **headBudget){

    struct Movie_Budget *ptrBudget;
    int year,untilsince,i,flag = 1;
    
    /*getting year and until/since input*/
    while(1){
        printf("\n Enter a year : ");
        scanf("%d",&year);
        if(year<1900||year>2021){/*error message*/
            printf("\n !- INVALID YEAR -!");
        }
        else{
            while(1){
                /*getting until/since input*/
                printf("\n Until(0) or Since(1)  %d : ",year);
                scanf("%d",&untilsince);
                ptrBudget = *headBudget;
                if(untilsince==0){  
                    while(1){
                        ptrBudget = ptrBudget->link;
                        if(ptrBudget->year < year){
                            printf("\n %s ",ptrBudget->name);
                            flag = 0;
                        }
                        if(ptrBudget->link==NULL){
                            break;
                        }
                    }
                    break;
                }
                else if(untilsince==1){
                    while(1){
                        ptrBudget = ptrBudget->link;
                        if(ptrBudget->year > year){
                            printf("\n %s ",ptrBudget->name);
                            flag = 0;
                        }
                        if(ptrBudget->link==NULL){
                            break;
                        }
                    }
                    break;
                }
                else printf("\n !- Please Enter 0 or 1 -!");
            }
            if(flag==1){
                printf("\n There is no movie in this range");  
            }
            if(flag==0){
                 break;
            }
           
        }
    }
}

/*printing between exact values*/
void print_sorted_year2(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    /*------declaring variables------*/
     struct Movie_Name *ptrName;
     struct Movie_Budget *ptrBudget;
     int start,end,selection,i,flag=1;
    /*-------------------------------*/ 
     ptrName = *headName;
     ptrBudget = *headBudget;
     
    while(1){
        ptrName = *headName;
        ptrBudget = *headBudget;
        ptrName = ptrName->link;
        ptrBudget = ptrBudget->link;
        printf("\n 1-Single Selection \n 2-Multiple Selection\n----> ");
        scanf("%d",&selection);
        if(selection==1){
            /*getting an index value*/
            printf("\n Enter a value : ");
            scanf("%d",&start);
            for(i=1;i<start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
            else printf("\nBudget : %-12d",ptrBudget->budget);
            printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
            return;
        }
        else if(selection==2){ 
            ptrName = *headName;
            ptrBudget = *headBudget;
            /*getting exact values*/
            printf("\nEnter 'start' value : ");
            scanf("%d",&start);
            printf("\nEnter 'end' value : ");
            scanf("%d",&end);
            while(1){
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
                if(ptrBudget->year>=start&&ptrBudget->year<=end){
                    if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
                    else printf("\nBudget : %-12d",ptrBudget->budget);
                    printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
                    flag = 0;
                }
                if(ptrBudget->link==NULL){
                    break;
                }
            }
            if(flag==1){
                printf("\nThere isn't any movie in this range.");
            }
            if(flag==0){
                return;
            }
        }
        else{ /*error message*/
            printf("\n!-!- Enter 1 or 2 -!-!");
        }

    }
}

/*printing scores after sorting*/
void print_sorted_score(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    /*--------declaring variables-------*/
     double score;
     int lessgreat,flag=1;
     struct Movie_Name *ptrName;
    /*----------------------------------*/
    
    while(1){ /*getting a score value*/
        printf("\n Enter a score : ");
        scanf("%lf",&score);
        if(score<0||score>10){ /*error message*/
            printf("\n !- Score must be between 0-10 -!");
        }
        else{
            while(1){
                printf("\n Less(0) or Greater(1)  %.1f : ",score);
                scanf("%d",&lessgreat);
                ptrName = *headName;
                if(lessgreat==0){  
                    while(1){
                        ptrName = ptrName->link;
                        if(ptrName->score < score){
                            printf("\n %s ",ptrName->name);
                            flag = 0;
                        }
                        if(ptrName->link==NULL){
                            break;
                        }
                    }
                    break;
                }
                else if(lessgreat==1){ 
                    while(1){
                        ptrName = ptrName->link;
                        if(ptrName->score > score){
                            printf("\n %s ",ptrName->name);
                            flag = 0;
                        }
                        if(ptrName->link==NULL){
                            break;
                        }
                    }
                    break;
                }
                else printf("\n !- Please Enter 0 or 1 -!");
            }
            if(flag==1){
                printf("\n There is no movie in this range");  
            }
            if(flag==0){
                 break;
            }
        }
    }

}

/*printing between exact values*/
void print_sorted_score2(struct Movie_Name **headName, struct Movie_Budget **headBudget){
    struct Movie_Name *ptrName;
    struct Movie_Budget *ptrBudget;
    ptrName = *headName;
    ptrBudget = *headBudget;
    double start,end;
    int selection,i,flag=1;
    while(1){
        ptrName = *headName;
        ptrBudget = *headBudget;
        ptrName = ptrName->link;
        ptrBudget = ptrBudget->link;
        printf("\n 1-Single Selection \n 2-Multiple Selection\n----> ");
        scanf("%d",&selection);
        if(selection==1){
            printf("\n Enter a value : ");
            scanf("%lf",&start);
            for(i=1;i<start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
            else printf("\nBudget : %-12d",ptrBudget->budget);
            printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
            return;
        }
        else if(selection==2){
            ptrName = *headName;
            ptrBudget = *headBudget;
            printf("\nEnter 'start' value : ");
            scanf("%lf",&start);
            printf("\nEnter 'end' value : ");
            scanf("%lf",&end);
            while(1){
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
                if(ptrName->score>=start&&ptrName->score<=end){
                    if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
                    else printf("\nBudget : %-12d",ptrBudget->budget);
                    printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
                    flag = 0;
                }
                if(ptrBudget->link==NULL){
                    break;
                }
            }
            if(flag==1){
                printf("\nThere isn't any movie in this range.");
            }
            if(flag==0){
                return;
            }
            
        }
        else{
            printf("\n!-!- Enter 1 or 2 -!-!");
        }

    }
}

/*sorting for budget*/
void list_through_budget(struct Movie_Name ***headName, struct Movie_Budget ***headBudget){
    /*---------declaring pointers----------*/
    struct Movie_Name *ptrName = NULL;
    struct Movie_Budget *ptrBudget = NULL;
    struct Movie_Budget *tempBudget = NULL;
    struct Movie_Name *tempName = NULL;
    /*-------------------------------------*/
    ptrName = **headName;
    ptrBudget = **headBudget;
    /*sorting and calling swap function*/
    while(ptrBudget!=NULL){
        tempBudget = ptrBudget->link;
        tempName = ptrName->link;
        while(tempBudget != NULL){
            if(ptrBudget->budget > tempBudget->budget) swap_movies(ptrBudget,ptrName,tempBudget,tempName);
            tempBudget = tempBudget->link;
            tempName = tempName->link;
        }
        ptrBudget = ptrBudget->link;
        ptrName = ptrName->link;
    }
}

/*printing budgets after sorting*/
void print_sorted_budget(struct Movie_Name ***headName, struct Movie_Budget ***headBudget){
    /*-------declaring variables--------*/
      struct Movie_Name *ptrName;
      struct Movie_Budget *ptrBudget;
      int start,end,selection,i;
    /*----------------------------------*/  
      ptrName = **headName;
      ptrBudget = **headBudget;
    
    while(1){
        ptrName = **headName;
        ptrBudget = **headBudget;
        printf("\n 1-Single Selection \n 2-Multiple Selection\n----> ");
        scanf("%d",&selection);
        if(selection==1){
            printf("\n Enter a value : ");
            scanf("%d",&start);
            while(1){
                /*shifting pointer to end of the unknowns*/
                 ptrBudget = ptrBudget->link;
                 ptrName = ptrName->link;
                 if(ptrBudget->budget != -1){
                    break;
                 }
            }
            for(i=1;i<start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
            else printf("\nBudget : %-12d",ptrBudget->budget);
            printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
            return;
        }
        else if(selection==2){
            ptrName = **headName;
            ptrBudget = **headBudget;
            printf("\nEnter 'start' value : ");
            scanf("%d",&start);
            printf("\nEnter 'end' value : ");
            scanf("%d",&end);
            while(1){
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
                if(ptrBudget->budget>=start&&ptrBudget->budget<=end){
                    if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
                    else printf("\nBudget : %-12d",ptrBudget->budget);
                    printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
                }
                if(ptrBudget->link==NULL){
                    break;
                }
            }
            return;
        }
        else{
            printf("\n!-!- Enter 1 or 2 -!-!");
        }

    }
}

void list_through_genre(struct Movie_Name ***headName, struct Movie_Budget ***headBudget){
    /*-----------declaring pointers---------*/
    struct Movie_Name *ptrName = NULL;
    struct Movie_Budget *ptrBudget = NULL;
    struct Movie_Budget *tempBudget = NULL;
    struct Movie_Name *tempName = NULL;
    /*--------------------------------------*/
    ptrName = **headName;
    ptrBudget = **headBudget;
    ptrBudget = ptrBudget->link;
    ptrName = ptrName->link;
    /*sorting according to genres and swapping*/
    while(ptrBudget!=NULL){
        tempBudget = ptrBudget->link;
        tempName = ptrName->link;
        while(tempName != NULL){
            if(strcmp(ptrName->genre,tempName->genre)>0) swap_movies(ptrBudget,ptrName,tempBudget,tempName);
            tempBudget = tempBudget->link;
            tempName = tempName->link;
        }
        ptrBudget = ptrBudget->link;
        ptrName = ptrName->link;
    }
}

/*sorting list for names*/
void list_through_name(struct Movie_Name ***headName, struct Movie_Budget ***headBudget){
    /*----------declaring pointers-----------*/
     struct Movie_Name *ptrName = NULL;
     struct Movie_Budget *ptrBudget = NULL;
     struct Movie_Budget *tempBudget = NULL;
     struct Movie_Name *tempName = NULL;
    /*---------------------------------------*/
    ptrName = **headName;
    ptrBudget = **headBudget;
    ptrBudget = ptrBudget->link;
    ptrName = ptrName->link;
    /*sorting and swapping datas*/
    while(ptrBudget!=NULL){
        tempBudget = ptrBudget->link;
        tempName = ptrName->link;
        while(tempName != NULL){
            if(strcmp(ptrName->name,tempName->name)>0) swap_movies(ptrBudget,ptrName,tempBudget,tempName);
            tempBudget = tempBudget->link;
            tempName = tempName->link;
        }
        ptrBudget = ptrBudget->link;
        ptrName = ptrName->link;
    }

}

/*printing name or genre after sorting*/
void print_sorted_name_genre(struct Movie_Name ***headName, struct Movie_Budget ***headBudget){
    /*-------declaring pointers------*/
    struct Movie_Name *ptrName;
    struct Movie_Budget *ptrBudget;
    int start,end,selection,i;
    /*-------------------------------*/
    ptrName = **headName;
    ptrBudget = **headBudget;
    while(1){
        ptrName = **headName;
        ptrBudget = **headBudget;
        printf("\n 1-Single Selection \n 2-Multiple Selection\n----> ");
        scanf("%d",&selection);
        if(selection==1){
            printf("\n Enter a value : ");
            scanf("%d",&start);
            for(i=0;i<start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
            else printf("\nBudget : %-12d",ptrBudget->budget);
            printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
            return;
        }
        else if(selection==2){
            ptrName = **headName;
            ptrBudget = **headBudget;
            ptrBudget = ptrBudget->link;
            ptrName = ptrName->link;
            printf("\nEnter 'start' value : ");
            scanf("%d",&start);
            printf("\nEnter 'end' value : ");
            scanf("%d",&end);
            for(i=1;i<start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            for(i=0;i<end-start;i++){
                if(ptrBudget->link==NULL){
                    printf("\n ------------YOU EXCEEDED LIST---------");
                    break;
                }
                if(ptrBudget->budget==-1) printf("\nBudget : Unknown     ");
                else printf("\nBudget : %-12d",ptrBudget->budget);
                printf(" | Name : %-90s | Genre : %-10s | Score : %.1f | Year : %d ",ptrBudget->name,ptrName->genre,ptrName->score,ptrBudget->year);
                ptrBudget = ptrBudget->link;
                ptrName = ptrName->link;
            }
            return;
        }
        else{
            printf("\n!-!- Enter 1 or 2 -!-!");
        }

    }
}

