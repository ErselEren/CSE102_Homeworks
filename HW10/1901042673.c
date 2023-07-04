#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROWNUMBER 5
#define MAX 100

typedef struct {
    double budget;
    int genre;
    char *name;
    double score;
    int year;
}Movie;

typedef struct {
    double budget;
    char *genre;
    char *name;
    double score;
    int year;
    int t_genre;
}bufferMovie;

bufferMovie buffer;
int *order;
int tgenreCounter;
char **t_genre;

void list_genres();
void movie_through_years(Movie *movies, int movieCtr);
void movie_through_scores(Movie *movies, int movieCtr);
void single_movie_info();
void imdb_average();
void genre_frequence();
void list_sorted_data(Movie *movies, int movieCtr);
void movie_function(char *file_name);
Movie* get_lines(char *filename,Movie *movies, int *moviectr);
void order_row(char *p1,int *order);
void decompose(char *p1);
int check_genre();
int check_name(Movie *movies, int movieCounter);
void expand_t_Genre();
Movie* expand_struct(Movie *movies, int moviecounter);
void print_menu();

int main(){
    int i;
    char *filename = "Movies.txt"; /*filename*/
    movie_function(filename); 
    /*free'ing heap*/
    for(i=0;i<tgenreCounter;i++){
        free(t_genre[i]);
    }
    free(t_genre);
    printf("\n------------------------END OF PROGRAM--------------------------");
    return 0;
}

void movie_function(char *filename){
        /*---------declaring variables---------*/
        Movie *movies;
        int moviectr,command,flag,i,j,flag2,sum1;
        char x;
        char *name = calloc(MAX,sizeof(char));
        double sum;
        flag = 1;
        /*-------allocation for first element of struct array-------*/
        movies = calloc(sizeof(Movie),1);
        movies[0].name = (char *)malloc(50);
        strcpy(movies[0].name,"FILMADI");
        /*calling func. that we get lines and store in struct array*/
        movies = get_lines(filename,movies,&moviectr);
        printf("\n");
        /*--------getting input and listing-------------------------*/
        while(flag){
            print_menu();
            scanf("%d",&command);
            x = getchar();
            sum = 0;
            flag2 = 1;
            
            switch (command)
            {
              case 1:
                  list_sorted_data(movies,moviectr);
                  break;
              case 2:
                  /*listing genres*/
                  for(i=0;i<tgenreCounter;i++)
                    printf("\n ===> %s <===",t_genre[i]);
                  break;
              case 3:            
                  movie_through_years(movies,moviectr);
                  break;
              case 4:
                  movie_through_scores(movies,moviectr);
                  break;
              case 5:
                  /*getting input until we find a name from list*/
                  while(flag2){ 
                     printf("\n Enter a movie name : ");
                     scanf(" %[^\n]",name);
                     /*searching from beginning to end of struct array*/
                     for(i=0;i<moviectr;i++){
                        /*print info's and exit loop if we find exact match*/
                        if(strcmp(name,movies[i].name)==0){ 
                            if(movies[i].budget==-1) printf("\nBudget : Unknown");
                            else printf("\nBudget : %.0lf",movies[i].budget);
                            printf("\nGenre : %s ",t_genre[movies[i].genre]);
                            printf("\nName : %s \nScore : %.1lf\nYear : %d ",movies[i].name,movies[i].score,movies[i].year);
                            flag2 = 0;
                            break;
                        }
                     }   
                      if(flag2==1){ /*error message for invalid input*/
                        printf("\n !-!- There is no movie with this name -!-! ");
                      }
                   }
                   break;
              case 6:
                  /*calculating imdb summation for each movie*/
                  for(i=0;i<moviectr;i++){
                      sum = sum + movies[i].score;
                  }
                  printf("\nAverage IMDB score is = %f",sum/moviectr);
                  break;
              case 7:
                  /*increasing sum1 for each type of genre*/
                  sum1 = 0;
                  for(i=0;i<tgenreCounter;i++,sum1=0){
                      for(j=0;j<=moviectr+1;j++){
                          if(i == movies[j].genre){
                              sum1++;
                          }
                      }
                      printf("\n %-15s  %4d",t_genre[i],sum1);
                  }
                  break;
              case 8:
                  printf("\nProgram Has Terminated\n");
                  flag = 0;
                  break;
              default:
                  printf("\n ! Please Enter Valid Command ! ");
                  break;
            }
        }
        /*--------getting input and listing-------------------------*/
    /*freeing allocations*/
    for(i=0;i<moviectr;i++){
        free(movies[i].name);
    }   
    free(movies);
    /*==================================END OF FUNC===================================*/
}

void list_sorted_data(Movie *movies, int movieCtr){
    /*----------------------Declaring variables---------------------*/
    Movie temp;
    int i,j,flag,command,selection,start,end,count=0,min=0,lastindex;
    char x;
    flag = 1;
    /*--------------------------SUBMENU-----------------------------*/
        while(1){
            printf("\n 1-Budget\n 2-Genre\n 3-Name\n 4-Score\n 5-Year \n--->");
            scanf("%d",&command);
            x = getchar();
            if(command==1||command==2||command==3||command==4||command==5){
                break;
            }
            else{
                printf("\n ! Please Enter Valid Command ! ");
            }
        }  
        /*----------------------------sort movies array-------------------------*/
            /*sorting for budget*/
            if(command==1){ 
                /*selection sort algorithm by using temp struct */
                for(i=0;i<movieCtr-1;i++){
                    min = i;
                    for(j=i+1;j<movieCtr;j++){
                        if(movies[j].budget <=movies[min].budget) min = j;
                    }
                    temp = movies[min];
                    movies[min] = movies[i];
                    movies[i] = temp;
                }
                /*we find last index of movie which has unknown budget*/
                for(i=0;i<movieCtr;i++){
                    if(movies[i].budget == -1 && movies[i+1].budget!=-1){
                        lastindex = i;
                        break;
                    }
                }
            }
            
            /*sorting for genre*/
            if(command==2){ 
                /*sorting by using temp and global t_genre array which we store name of genres*/
                for(i=0;i<movieCtr;i++){
                    for(j=i+1;j<movieCtr;j++){
                        if(strcmp(t_genre[movies[i].genre],t_genre[movies[j].genre])>0){
                            temp = movies[i];
                            movies[i]= movies[j];
                            movies[j]= temp;
                        }
                    }
                }
            }
            
            /*sorting for name*/
            if(command==3){ 
                /*sorting names by using temp struct*/
                for(i=0;i<movieCtr;i++){
                    for(j=i+1;j<movieCtr;j++){
                        if(strcmp(movies[i].name,movies[j].name)>0){
                            temp = movies[i];
                            movies[i]= movies[j];
                            movies[j]= temp;
                        }
                    }
                }
            }   
            
            /*sorting for score*/
            if(command==4){ 
                /*sorting by using selection sort algorithm*/
                for(i=0;i<movieCtr-1;i++){
                    min = i;
                    for(j=i+1;j<movieCtr;j++){
                        if(movies[j].score <=movies[min].score) min = j;
                    }
                    temp = movies[min];
                    movies[min] = movies[i];
                    movies[i] = temp;
                }
            }
            
            /*sorting for year*/
            if(command==5){ 
                /*sorting by using selection sort algorithm*/
                for(i=0;i<movieCtr-1;i++){
                    min = i;
                    for(j=i+1;j<movieCtr;j++){
                        if(movies[j].year <=movies[min].year) min = j;
                    }
                    temp = movies[min];
                    movies[min] = movies[i];
                    movies[i] = temp;
                }
            }
                  
        /*--------------------------2nd Submenu---------------------------------*/
        while(1){/*getting input until valid input*/
            printf("\n 1-Single Selection\n 2-Multiple Selection\n-->Selection : ");
            scanf("%d",&selection);
            if(selection==1||selection==2){
                break;
            }
            else{ /*error message for invalid input*/
                printf("\n ! Please Enter Valid Command ! ");
            }
        }  
        /*----------------------------------------------------------------------*/
        if(selection==1){/*single selection*/
            while(1){ /*getting input until valid input*/
                printf("\n Enter value : ");
                scanf("%d",&start); 
                /*error message for invalid input*/
                if(start<0||start>movieCtr){ 
                   printf("\nINVALID INPUT");
                }
                else{/*printing single movie*/
                    if(movies[start].budget == -1){
                        printf("Unknown\t");
                    }
                    else{
                        printf("%-12.0f  ", movies[start].budget);
                    } 
                    printf("%-10s   %-90s   %-.1f  %-5d\n", t_genre[movies[start].genre], movies[start].name, movies[start].score, movies[start].year);
                    break;
                }   
            }
                  
        }
        if(selection==2){ /*multiple selection*/
            /*getting index values of list which we print*/
            printf("\nEnter start value : ");
            scanf("%d",&start);
            printf("\nEnter end value : ");
            scanf("%d",&end);
                /*if we sort for budget, we print unknown for -1*/
                if(command==1){ 
                    for(i=start+lastindex;i<=end+lastindex;i++){
                       if(movies[i].budget == -1){
                        printf("Unknown \t");
                       }
                       else{
                        printf("%-14.0f  ", movies[i].budget);
                       } 
                       printf("%-10s   %-90s   %-.1f  %-5d\n", t_genre[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
                    }
                }
                else{
                    for(i=start;i<=end;i++){
                       if(movies[i].budget == -1){
                        printf("Unknown \t");
                       }
                       else{
                        printf("%-14.0f  ", movies[i].budget);
                       } 
                       printf("%-10s   %-90s   %-.1f  %-5d\n", t_genre[movies[i].genre], movies[i].name, movies[i].score, movies[i].year);
                    }
                }         
        }
}

void movie_through_years(Movie *movies, int movieCtr){
    /*--------Declaring variables-------*/
    int year,flag,flag1,choice,i;
    char ch;
    flag = 1; flag1 = 1;
    /*----------------------------------*/
   
    while(flag){ /*getting input until valid input*/
        printf("\n Enter a year : ");
        scanf("%d",&year);
        ch = getchar();
        if(year>2021||year<1950){ /*error message*/
            printf("\nINVALID YEAR\nTRY AGAIN");
        }
        else{
            while(flag1){ /*getting input until valid input*/
               printf("\nUntil (0) or Since (1) %d : ",year);
               scanf("%d",&choice);
               ch = getchar();
               /*sorting from year to now */
               if(choice == 1){
                   for(i=0;i<movieCtr;i++){
                       if(movies[i].year>=year){
                           printf("\n ===> %s ",movies[i].name);
                       }
                   }
                    flag1 = 0; 
               }
               /*sorting from beggining to year */
               else if(choice == 0){
                   for(i=0;i<movieCtr;i++){
                       if(movies[i].year<=year){
                           printf("\n ===> %s ",movies[i].name);
                       }
                   }
                    flag1 = 0;
               }
               else{
                   printf("\nINVALID YEAR\nTRY AGAIN");
               }
              
            }
            flag = 0;
        }
    }
}

void movie_through_scores(Movie *movies, int movieCtr){
    /*--------Declaring variables-------*/
    double score;
    int flag = 1,flag1 =1,choice,i;
    char ch;
    /*----------------------------------*/
    while(flag){/*getting input until valid input*/
        printf("\nEnter a score : ");
        scanf("%lf",&score);
        ch = getchar();
        if(score<0||score>10.0){
            printf("\nINVALID YEAR\nTRY AGAIN");
        }
        else{
            while(flag1){ /*error message*/
               printf("\nLess (0) or Greater (1) %.1lf : ",score);
               scanf("%d",&choice);
               ch = getchar();
               /*sorting from score to 10 */
               if(choice == 1){
                   for(i=0;i<movieCtr;i++){
                       if(movies[i].score>=score){
                           printf("\n ===> %s ",movies[i].name);
                       }
                   }
                    flag1 = 0; 
               }
                /*sorting from score to 0 */
               else if(choice == 0){
                   for(i=0;i<movieCtr;i++){
                       if(movies[i].score<=score){
                           printf("\n ===> %s ",movies[i].name);
                       }
                   }
                    flag1 = 0;
               }
               else{
                   printf("\nINVALID YEAR\nTRY AGAIN");
               }
              
            }
            flag = 0;
        }
    }
}

void print_menu(){
    printf("\n----------------------------------------");
    printf("\n 1-List of the Sorted Data\n 2-List of the Genres\n 3-List of the Movie Through the Years\n 4-List of the Movie Through the Scores");
    printf("\n 5-All Informations of a Single Movie\n 6-Average of the IMDB Scores\n 7-Frequence of the Genres \n 8-EXIT\n");
    printf("----------------------------------INPUT: ");
}

Movie* get_lines(char *filename,Movie *movies, int *moviectr){
    /*-----------------Declarations-----------------*/
       char c;
       char *p1, *p2=NULL;
       int length,i,j,flag,row,genreFlag,nameFlag;
       flag = 1; length = 0;  row = 0;
       int movieCounter=0;
       
    /*----------------------------------------------*/

    /*-------------------allocation for genre and order array-------------------*/
        tgenreCounter=0;
        
        order = calloc(ROWNUMBER*sizeof(int),1);
    /*--------------------------------------------------------------------------*/

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
          if(c==EOF){ 
            flag = 0;
          }
          if(c=='\n'){
             if(row==0){ /*ilk line'da order belirlenir*/
                order_row(p1,order); 
             }
             else{ /*lines after first line*/
                decompose(p1); /*decomposing line*/
                genreFlag = check_genre(); /*checking genre*/
                
                if(genreFlag==-1){ /*if that genre is not in list */
                    tgenreCounter++;
                    expand_t_Genre(); /*yeni genre eklemek için genre listesi genişletiliyor*/
                    t_genre[tgenreCounter-1] = calloc(strlen(buffer.genre)+1,1);
                    strncpy(t_genre[tgenreCounter-1],buffer.genre,strlen(buffer.genre)); /*yeni index'e yeni genre ekleniyor*/
                    buffer.t_genre = tgenreCounter-1; /*daha sonra bu line'ın genre'sinin numarası bu index oluyor*/
                }
                else{ /*if that genre is in list*/
                    buffer.t_genre = genreFlag; /*check_genre'nin geri döndürdüğü değer bu line'ın genresinin numarası olacak*/
                }  
                /*buradan sonra buffer'da tüm gerekli bilgiler olmuş olacak. sırada name kontrolü yapmak var*/
                nameFlag = check_name(movies,movieCounter);
                /*--------------burada struct array'e yazdırma işlemleri olacak--------------*/
                if(nameFlag == -1){ /*listede buffer.name yok, struct array'in size'ı arttırılıp buffer structı eklenecek*/
                   movies = expand_struct(movies,movieCounter);
                   movies[movieCounter].budget = buffer.budget;
                   movies[movieCounter].year = buffer.year;
                   movies[movieCounter].genre = buffer.t_genre;
                   movies[movieCounter].score = buffer.score;
                   movies[movieCounter].name = (char*)calloc(strlen(buffer.name)+1,1);
                   strncpy(movies[movieCounter].name,buffer.name,strlen(buffer.name));
                   movieCounter++;
                }
                else{ /*flag -1 değilse, bu isimle film vardır ve nameFlag bize indexi döndürür. Burada overwrite işlemleri yapılacak*/
                    movies[nameFlag].budget = buffer.budget;
                    movies[nameFlag].genre = buffer.t_genre;
                    movies[nameFlag].score = buffer.score;
                    movies[nameFlag].year = buffer.year;
                }  
                  
             }
             length = 0;
             row++;
          }
          if(c!=EOF&&c!='\n'&&c!='\r'){
              /*p1 malloc*/
             p1 = calloc(length+1,sizeof(char));
             for(i=0;i<length-1;i++)
                p1[i] = p2[i];
             
             p1[length-1] = c;

             if(p2!=NULL)
                free(p2);

             p2 = p1;  
             
          }
    }
    /*--------------------------End Of While--------------------------------------*/
    free(order);
    free(p1);
    fclose(fp);
    *moviectr = movieCounter;
    return movies;
    /*||||||||| END OF get_lines ||||||||||*/
}

/*creating an order array according to first line*/
void order_row(char *p1, int *order){
    int flag,i,j,k;
    char *buffer;
    
  
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
void decompose(char *p1){
     int i,j;
     float n1,n2;
     
    for(j=0;j<5;j++){
        if(order[j]==1){
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
        if(order[j]==2){
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
        if(order[j]==3){
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
        if(order[j]==4){
           n1 = p1[0]-48;
           n2 = p1[2]-48;
           buffer.score = (n1*10+n2)/10;
           if(j!=4) 
              p1 = p1 + 4;
        }
        if(order[j]==5){
            buffer.year = (p1[0]-48)*1000 + (p1[1]-48)*100 + (p1[2]-48)*10 + (p1[3]-48);
            if(j!=4) 
               p1 = p1 + 5;
        }
    }
}

/*checks if genre is new or not, if it match returns index, else -1*/
int check_genre(){   
   int i=0;
   while(i<tgenreCounter){
       if(strcmp(t_genre[i],buffer.genre)==0){
           return i;
       }  
       i++;
   }
   return -1;
}

/*expanding t_genre by using temp array and freeing previously allocated memory*/
void expand_t_Genre(){
    int i;
    char** temp = NULL;
    
    temp = t_genre;
    t_genre = calloc(tgenreCounter,(sizeof(char*)));
    i=0;
    while(i<tgenreCounter-1){
        t_genre[i] = temp[i]; 
        i++;
    }
    free(temp);
    
    t_genre[i] = NULL;
}

/*expanding struct by using temp struct array and freeing previously allocated memory*/
Movie* expand_struct(Movie *movies, int movieCounter){
    int i;
    
    Movie *temp;
    temp = movies;

    movies = (Movie*)malloc((movieCounter+1)*sizeof(Movie));
    for(i=0;i<movieCounter;i++){
        movies[i] = temp[i];
    }
    free(temp);
   
    movies[movieCounter].name = NULL;
    return movies;
}

/*checks if name is new or not, if it match returns index, else -1*/
int check_name(Movie *movies, int movieCounter){
    int i;
    for(i=0;i<movieCounter;i++){
        if(strcmp(movies[i].name,buffer.name)==0){
            return i;
        }
    }
    return -1;
}