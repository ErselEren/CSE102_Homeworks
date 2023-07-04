#include <stdio.h>
#include <string.h> 
#define N 20
/* decleration of functions */
void fix_spelling_error(char *text);
int find_best_correction(char *non_punc);

int main()
{
    char text[N];
    FILE *fp;
    fp = fopen("text.txt", "r+");
    while (1){ /*reading until EOF and after EOF read one more time for last word */
        fscanf(fp, "%s",text); 
        if(feof(fp)){
            break;
        }
        /*passing word to function and replacing fixed word by using fseek */
        fix_spelling_error(text);  
        fseek(fp, (strlen(text)*(-1)), SEEK_CUR); 
        fprintf(fp, "%s ", text); 
    } 
        /*reading one more time for last word*/
        fscanf(fp, "%s",text); 
        fix_spelling_error(text); 
        fseek(fp, (strlen(text)*(-1)), SEEK_CUR); 
        fprintf(fp, "%s ", text); 


    return 0;
    /*[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[END OF MAIN]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]*/
}

/*----------------------------------------------------------------------------------------*/
void fix_spelling_error(char *text){
    
    /*declaring neccesary variables for different conditions */
    char temp1[N],array2[N],non_punc[N],array3[N];
    int i,j,z,size,counter,flag,index;
    flag = 0;
    
    /* filling array with \0's */
    for(i=0;i<N;i++){ 
        temp1[i]='\0';
        array3[i]='\0';
        non_punc[i]='\0';
        array2[i]='\0';
    }
    
    /*copying text to hold original text */
    strcpy(temp1,text); 
    strcpy(non_punc,text);

    /*here we check situations like "word ,  word" ,  word/word ,  word's */
    for(i=0;i<strlen(text);i++){
        if(strlen(text)>2){ /* checking words with 3 or more letters */
            if(temp1[i]<'a'||temp1[i]>'z') /*  */
            {
                if(i==0){ /* "word */
                   temp1[i]= ' ';
                   for(j=0;j<strlen(temp1);j++){
                   array2[j]=temp1[j+1];
                  }
                   strcpy(non_punc,array2);
                   flag = 1;
                }
                if(i==(strlen(text)-1)){ /* word" */
                   temp1[i]='\0';
                   strcpy(non_punc,temp1);
                   flag = 2;
                }
                if(temp1[i]=='/'){ /* word/word */
                   index = i;
                   flag = 3;
                }
                if(temp1[i+1]=='s'){ /* word's */
                   strncpy(array2,temp1,i);
                   strcpy(non_punc,array2);
                   flag = 2;
                }
            }
        } 
    }
    /*======================== punctuations removed  =======================*/
    
    if(flag==3){ /*special condition for word/word situation */
        int i,j;
        strncpy(array2,temp1,index);
        printf("\narray2 = %s\n",array2);
        find_best_correction(array2);
        printf("\nfixed array2 = %s\n",array2);
        for(j,i=index+1;i<strlen(temp1);i++,j++){
            array3[j]=temp1[i];
        }
        find_best_correction(array3);

        for(i=0;i<strlen(array2);i++){
            text[i]=array2[i];
        }
        for(i=0;i<strlen(array3);i++){
            text[i+1+strlen(array3)]=array3[i];
        }
        printf("\nfixed array3 = %s\n",array3);
    }
    
    /*===============================word is fixed================================*/
        find_best_correction(non_punc);
    /*===============================word is fixed================================*/
    
    
    /* REPLACING WORDS INTO ORIGINAL TEXT */
    if(flag==0){
        strcpy(text,non_punc);
    }
    if(flag==1){
        for(i=0;i<strlen(non_punc);i++){
            text[i+1]=non_punc[i];
        }
    }
    if(flag==2||flag==4){
        for(i=0;i<strlen(non_punc);i++){
            text[i]=non_punc[i];
        }
    }
    /*-------------------------------------*/

}

/*------------------------------------------------------------------------------------------------*/
int find_best_correction(char *non_punc){
    /*declaring neccesary variables like control, counter etc.*/ 
      char dict[N];
      int i,counter,index,flag,ctr;
      counter = 0;
      flag = 1;
      ctr = 1;
    
    /*opening dictionary file*/
    FILE *fp;
    fp = fopen("dictionary.txt", "r+");
    
    /*reading every word in dictionary and matching with non_punc word that we removed punctuations*/
    while (ctr){
        fscanf(fp, "%s",dict);
        if(feof(fp)){
            break;
        }
        if(strlen(non_punc)==strlen(dict)&&(strlen(non_punc)>2)){ /* searching words with 3 or more letter and same lenght */
            for(i=0;i<strlen(non_punc);i++){
               if(non_punc[i]==dict[i]){
                   counter++;
               }
               else{
                   if(non_punc[i]!='a'&&non_punc[i]!='e'&&non_punc[i]!='i'&&non_punc[i]!='o'&&non_punc[i]!='u'){ 
                       if(dict[i]=='a'||dict[i]=='e'||dict[i]=='i'||dict[i]=='o'||dict[i]=='u'){
                          index = i;
                          flag = 0;
                       }
                       else{
                           flag = 1;
                           index = i;
                       }        
                   }
                   else{
                      index = i;
                      flag = 1;
                   }
               }
               
            }
            if(counter==(strlen(non_punc)-1)){ /*if there are 1 missing letter we replace it */
                if(flag==0){
                    non_punc[index]=dict[index];
                    ctr = 0;
                }
                if(flag==1){
                    non_punc[index]=dict[index];
                }          
            }
        }
        counter = 0; 
    }   
}