
/* According to my thoughts, I designed my code like this: 
   Label 0 has the highest priority and 4 has the least.
   0 label can be 5 times in a row, 1 and 2 can be 3 times and, 3 and 4 can be 2 times.
   If one of the labels over the limit, my algorithm will make this processes:
   Example1 : 0 0 3 2 2 2 ---> add '2' ---> 0 0 2 3 2 2 2 
   Example2 : 0 1 2 3 2 2 2 ---> add '4' ---> 0 1 2 3 4 2 2 2 
   Example3 : 3 2 --> add '1' ---> 1 3 2 
   Example4 : 1 1 1 2 3 4 0 1 ---> add '0' ---> 0 1 1 1 2 3 4 0 1 
   Example5 : 0 0 0 0 0 2 2 2 3 0 2 , if we add '0' to this sequence, final version will be 0 0 0 0 0 2 2 2 3 0 0 2 
                         because label '0' has reached the limit so we send the new one to next to other '0' labels.
   Example2 : After one process of Example1, seq. will be 0 0 0 0 2 2 2 3 0 2, then if we add '0' final version will be 0 0 0 0 0 2 2 2 3 0 2 
                                                           because label 0 has not reached the limit yet so we send it next to other 0 labels.  
   Example7 : 2 2 3 3 4 4 2 2 4 ---> add '3' ---> 2 2 3 3 4 4 2 2 4 3 , algorithm send new '3' to end of sequence
                                                  because first two '3' labels reached limit so we send it to end
   */

#include <stdio.h>
#include <string.h>
#define N 51

struct Person{
    char name[20];
    int age;
    int label;
};

/*--------------------------FUNCTION DECLERATIONS-----------------------------*/
void add_customer(struct Person seq[N]);
void print_seq(struct Person seq[N]);
void add_label(struct Person seq[N],char name[],int age, int label,int index);
void process_customer(struct Person seq[N]);
int find_priority(struct Person seq[N],int label, int index1, int index);
int calc_seq(struct Person seq[N],int label,int index);
int find_last(struct Person seq[N]);
int find_for_four(struct Person seq[N]);
/*----------------------------------------------------------------------------*/

int main(){

    struct Person seq[N];
    int flag,command,index,i;
    flag = 1;
    
    /*filling sequence with '-1' to make comparing easier*/
    for(i=0;i<N;i++){
        seq[i].label = -1;
        seq[i].age = -1;
        strcpy(seq[i].name,"empty");
    }
    
    /* here we get commands from user until input is 3 */
    while(flag){
        print_seq(seq); /*printing seq*/
        printf("\n1-Add Customer\n2-Process Customer\n3-End Program\n");
        scanf("%d",&command);
        getchar(); /* to prevent wrong inputs */
        switch(command)
        {
            case 1: 
                add_customer(seq);
                break;
            case 2:
                process_customer(seq);
                break;
            case 3:
                flag=0;
                break;
            default:
                 printf("! ! ! Please enter VALID command ! ! !");
        }
    }
    return 0;
}

/* printing sequence from 0 to 50 if label is not -1 */
void print_seq(struct Person seq[N]){ 
    int i = 0;
    printf("\nCURRENT SEQUENCE is <--"); 
    /* sequence is filled with -1, so we print labels that are not -1 */
    for(i=0;i<N;i++){ 
        if(seq[i].label != -1){
            printf("%d ",seq[i].label);
        }
    }
    printf("--> ");
}

/* Here we get data of customers that we want to add */
void add_customer(struct Person seq[N]){
    char name[20];
    int age,label,index,flag;
    flag = 1;
    if(seq[49].label!=-1){
        printf("Sequence is FULL ");
        return;
    }
    else{
        printf("Enter name : ");
        scanf("%s",name); 
        printf("Enter age :");
        scanf("%d",&age);
        while(flag){
           printf("Enter label : ");
           scanf("%d",&label);
           if(label!=0&&label!=1&&label!=2&&label!=3&&label!=4){
           printf("Please enter valid label!\n");
           }
           else{
            flag = 0;
           }
        }
    
    index = calc_seq(seq,label,0); /* calc_seq returns index that we add customer into */
    add_label(seq,name,age,label,index); /* here we doing adding operations */
    }
    
}

/* shifting sequence one step to right side then adding new customer to index */
void add_label(struct Person seq[N],char name[],int age, int label,int index){
    int i;
    struct Person temp_struct,temp_struct2;

    /*here we saving original values of [index+1]. customer*/
    temp_struct = seq[index+1];
    seq[index+1] = seq[index];

    for(i=2;i<N-index;i++){  /*shifting sequence one step to left*/
        temp_struct2 = seq[index+i];
        seq[index+i] = temp_struct;
        temp_struct = temp_struct2;   
    }
    
    /* then adding original values to sequence */
    strcpy(seq[index].name,name);
    seq[index].age = age;
    seq[index].label = label;
}

/*this function is the frame of algorithm. depending on status of sequence, it calls another functions*/
int calc_seq(struct Person seq[N],int label,int index){
        
        int status,i,j,counter,index1,index2,count;
        /* status = 0 if there isn't any 'label' from index to end of sequence 
           status = 1 if there is 'label' from index to end of sequence      */
        
        index1 = index; /* we copy index to use in following steps */ 
        for(i=index;i<N;i++){
            if(seq[i].label!=label){
                 status=0; 
            }
            if(seq[i].label==label){ 
                 status=1;
                 index = i;
                 index2= i;
                 i=N;
            }
         }

        /* if there isn't any 'label' from beginning of sequence to end of sequence  */
        if(status==0&&index==0){   
            int i,flag;
            flag = 0;
            
            /* we have special func for '4' label */
            for(j=index;j<N;j++){
                if(label==4){ /*if label is 4 */
                    return find_for_four(seq);
                }
                else{ /*if label is not 4, we find true index below */
                    if(seq[j].label == label||seq[j].label == label+1||seq[j].label == label+2||seq[j].label == label+3||seq[j].label == label+4){
                        flag=1;
                        return j;  
                    }
                }    
            }
            /* if we can't find, it returns i*/
            if(flag!=1){
                for(i=0;i<N;i++){
                    if(seq[i].label==-1){
                        return i;
                    }
                }
            }
        }
        
        /* if there isn't any 'label' from somewhere in the sequence to end of sequence */
        if(status==0&&index!=0){ 
            /* add it end of the sequence */
            for(i=index;i<N;i++){
                if(seq[i].label==-1){
                    index = i;
                    i=N;
                }
            }
            return index;
        }
        
        /* status=1 means that there is 'label' from 'index' (we found it in for loop at the top) to end of sequence */
        if(status==1){
            /* counter is the value of consecutive 'label' number */
            counter = 0;
            count = 0;
            while(seq[index].label==label){
                counter++;
                index++;
            }

            /*here we check limits of each label */
            /*if it reach the limit, we check left side of sequence again, if we find valid location we return this index
              else we call function again to find new location
            /*if it didn't reach the limit, we return index and add this customer into that index */
            
            if(label==0){ /*checking for '0' label*/
                if(counter>=5){ /* if it reaches limit, we check left side of sequence first*/    
                    for(i=index2-1;i>index1;i--){ 
                        if(seq[i].label>label){
                          for(i=find_priority(seq,label,index1,index2)-1;i>=find_priority(seq,label,index1,index2)-5;i--){
                              if(seq[i].label == label){
                                  count++;
                              }
                              else{
                                  i=-1;
                              }
                          }
                          if(count<5){
                            return find_priority(seq,label,index1,index2);
                          }  
                        }
                    }
                    calc_seq(seq,label,index);
                }
                if(counter<5){ /*if it didn't reach the limit */ 
                    index1 = find_priority(seq,label,index1,index); /*first we find an index, then we check sequence*/
                    counter = 0;
                     /* we check left side of sequence */
                     for(i=index1-1;i>=0;i--){
                         if(seq[i].label==label){
                             counter++;
                         }
                         else if(seq[i].label!=label){
                             i=-1;
                         }
                     }
                     if(counter<5){
                         return index1;
                     }
                     else{
                         return index;
                     }
                }
            }
            if(label==1||label==2){ /*checking for '1' and '2' labels*/
                if(counter>=3){ /* if it reaches limit, we check left side of sequence first*/
                    for(i=index2-1;i>index1;i--){
                        if(seq[i].label>label){
                          for(i=find_priority(seq,label,index1,index2)-1;i>=find_priority(seq,label,index1,index2)-3;i--){
                              if(seq[i].label == label){
                                  count++;
                              }
                              else{
                                  i=-1;
                              }
                          }
                          if(count<3){
                            return find_priority(seq,label,index1,index2);
                          } 
                        }
                    }
                    calc_seq(seq,label,index); 
                }
                if(counter<3){ /*if it didn't reach the limit */ 
                     index1 = find_priority(seq,label,index1,index); /*first we find an index, then we check sequence*/
                     counter = 0;
                     /* we check left side of sequence */
                     for(i=index1-1;i>=0;i--){
                         if(seq[i].label==label){
                             counter++;
                         }
                         if(seq[i].label!=label){
                             i=-1;
                         }
                     }
                     if(counter<3){
                         return index1;
                     }
                     else{
                         return index;
                     }
                }
            }
            if(label==3||label==4){ /*checking for '3' and '4' labels*/
                if(counter>=2){ /* if it reaches limit, we check left side of sequence first*/     
                    for(i=index2-1;i>index1;i--){
                        if(seq[i].label>label){
                          for(i=find_priority(seq,label,index1,index2)-1;i>=find_priority(seq,label,index1,index2)-2;i--){
                              if(seq[i].label == label){
                                  count++;
                              }
                              else{
                                  i=-1;
                              }
                          }
                          if(count<2){
                            return find_priority(seq,label,index1,index2);
                          }   
                        }
                    }
                    calc_seq(seq,label,index);
                }
                if(counter<2){ /*if it didn't reach the limit */ 
                    index1 = find_priority(seq,label,index1,index); /*first we find an index, then we check sequence*/
                    counter = 0;
                     /* we check left side of sequence */
                     for(i=index1-1;i>=0;i--){
                         if(seq[i].label==label){
                             counter++;
                         }
                         if(seq[i].label!=label){
                             i=-1;
                         }
                     }
                     if(counter<2){
                         return index1;
                     }
                     else{
                         return index;
                     }
                }
            }     
        }
}

/*here we print first customer of sequence then shifting sequence one step to left*/
void process_customer(struct Person seq[N]){
    int i,lastIndex;
    
    if(seq[0].label==-1){ /*if sequence is empty, print error message*/
        printf("\n>>>THERE IS NO CUSTOMER IN SEQUENCE<<<\n");
        return;
    }
    
    for(i=0;i<N;i++){ /* lastIndex is the index of the last valid label */
        if(seq[i].label==-1){
            lastIndex = i;
        }
    }
    printf("\nProceed customer is %s , %d years old ",seq[0].name,seq[0].age);

    for(i=0;i<lastIndex;i++) /* shifting sequence one step to left */
        seq[i] = seq[i+1];
    
}

/*find last customer's index*/
int find_last(struct Person seq[N]){
    int i;
    for(i=0;i<N;i++){
        if(seq[i].label==-1){
            return i;
        }
    }
}

/* in this function we find priority of customers to another one */
int find_priority(struct Person seq[N],int label, int index1, int index){
    int i,j,flag;
    flag = 0;
        /*here we check from index1 to index to find 'label' or less priority labels */
        for(j=index1;j<=index;j++){
            if(seq[j].label == label+1||seq[j].label == label+2||seq[j].label == label+3||seq[j].label == label+4){
                    flag=1;
                    return j;   
            }
            if(seq[j].label == label){ /* this loop is to find last index of 'label' */
                    if(seq[j+1].label!=label){
                        flag=1;
                        return j+1; 
                    }
                      
            }
        }
        
        if(flag!=1){
            for(i=0;i<N;i++){
                if(seq[i].label==-1){
                   return i;
                }
            }
        }   
}

/* this function find true index for '4' label */
int find_for_four(struct Person seq[N]){
    int i,j;
    /* it search from 3 to 0 label */
    for(i=3;i>=0;i--){
        for(j=0;j<N;j++){
            if(seq[j].label==i){
                if(seq[j+1].label!=i){
                    return j+1; /*when it finds return j+1 index*/
                }
            }
        }
    }
    return 0; /*if it cant find, return 0 index */
}