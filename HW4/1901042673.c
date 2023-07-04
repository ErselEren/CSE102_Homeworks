#include <stdio.h>

void check_armstrong_palindrome(){
    int num,temp,temp2,factor,digit,sum; /* variables for armstrong */
    int control,flag_arm,flag_pal; /* variables for checking armstrong and palindrome */
    int reversed,remainder,temp3,temp4; /* variables for palindrome */
  /*======================================================================== */
  /*===============================ARMSTRONG================================ */
   factor = 1;
    sum = 0;
     do{  /* in loop we check negative-positive condition */ 
       printf("Enter a positive number: " );
       scanf("%d",&num); 
       if(num<=0)
         printf("You didn't enter positive integer!\n");      
       else
         control = 1;

     }while(control!=1);
    
       temp=num;                   /*use temp and temp2 to not lose original value*/
        temp2=num;
         temp3=num;
          temp4=num;
  
  /*--------calculating according to armstrong method-------*/       
          while(temp){      
             temp=temp/10;
              factor = factor*10;
          }  
          while(factor>1){
             factor = factor/10;
              digit = num/factor;
               sum = sum+(digit*digit*digit);
                num = num%factor;
          }
  /*-------------------calculation done---------------------*/
   
   /* assignin values to flag variable */
          if(sum==temp2) 
              flag_arm=1;
          else
              flag_arm=0;
   /*======================================================================== */
   /*======================================================================== */
   /*=============================PALINDROME================================= */
      reversed = 0;
        do{
          remainder = temp3%10;
          reversed = (reversed * 10) + remainder;
          temp3 = temp3/10;
        }while(temp3!=0);

     /* assignin values to flag variable */
         if(temp4 == reversed)
            flag_pal = 1; 
         else
            flag_pal = 0;
     /*======================================================================== */
     /*=================================RESULT================================= */
     /* printing results according to flags of armstrong and palindrome */
     if(flag_pal==1&&flag_arm==1)
       printf("This number is both Palindrome and Armstrong number.");
     if(flag_pal==0&&flag_arm==1)
       printf("This number is only Armstrong number.");
     if(flag_pal==1&&flag_arm==0)
       printf("This number is only Palindrome number.");
     if(flag_pal==0&&flag_arm==0)
       printf("This number does not satisfy any special cases.");
     /*======================================================================== */
}

void write_polynomial(){
    float num; /*coefficients*/
    int N; /* degree of polynomial */
    int i;
    int control; /* control variable to avoid 1.0x, 2.0x^4 etc.*/
    printf("Enter your polynomial : ");
    scanf("%d",&N);
    
    /*===we print the polynomial in for loop===*/
    for(i=N;i>=0;i--){
      scanf("%f",&num);         
      if(i==N){  /* printing the coef of biggest degree */
          if(N==1){  /* printing if degree is 1 */
              if(num>0&&num!=1){ /* condition for numbers which is larger than 0 but not equal to 1 */
                  /* here we check whether num is integer or not */ 
                  control = num; /* we casting our 'num' to 'control' */
                  if(control==num)
                    printf("%dx",control);
                  else
                    printf("%.1fx",num);               
              }     
              if(num!=-1&&num<0){ /* condition for numbers which is larger than 0 but not equal to -1 */
                  control = num;
                  if(control==num)
                    printf("%dx",control);
                  else
                    printf("%.1fx",num); 
              }
              if(num==1){ /* printing conditions if number is 1*/
                printf("x"); 
              }
              if(num==-1){ /* printing conditions if number is -1*/
                printf("-x");
              }   
          }
          else if(N==0){  /* printing conditions if degree is 0*/
              if(num>1){
                  control = num;
                  if(control==num)
                   printf("%dx",control);
                  else
                   printf("%.1fx",num); 
              }
              if(num<-1){
                  control = num;
                  if(control==num)
                   printf("%dx",control);
                  else
                   printf("%.1fx",num);               
              }
              if(num==-1){
                printf("-1");
              }
              if(num==1){
                printf("+1");
              }
              i=-1;
          }
          else{ /* printing conditions if degree is larger than 1 */
            if(num>0&&num!=1){
              control = num;
              if(control==num)
                printf("%dx^%d",control,i);         
              else
                printf("%.1fx^%d",num,i);
            }
            if(num!=-1&&num<0){
              control = num;
              if(control==num)
                printf("%dx^%d",control,i);
              else
                printf("%.1fx^%d",num,i); 
            } 
            if(num==1){
              printf("x^%d",i); 
            }
            if(num==-1){
              printf("-x^%d",i);
            }  
          }
      }
      else if(i==1){  /*printing the coef of degree of 1 */
        if(num>1){
           control = num;
           if(control==num)
            printf("+%dx",control);
           else
            printf("+%.1fx",num);
        }
        if(num<-1){
           control = num;
           if(control==num)
            printf("%dx",control);
           else
            printf("%.1fx",num);
        }  
        if(num==1){
          printf("+x"); 
        }
        if(num==-1){
          printf("-x");
        }   
      }
      else if(i==0){  /*printing the coef of degree of 0 */    
        if(num>1){
           control = num;
           if(control==num)
            printf("+%d",control);
           else
            printf("+%.1f",num);
        }
        if(num<-1){
           control = num;
           if(control==num)
            printf("%d",control);
           else
            printf("%.1f",num);
        }
        if(num==-1){
          printf("-1");
        }
        if(num==1){
          printf("+1"); 
        }           
      }
      else if(i!=-1){ /*printing the coef of between first and last degrees */
        if(num>1){
           control = num;
           if(control==num)
            printf("+%dx^%d",control,i);
           else
            printf("+%.1fx^%d",num,i);
        }
        if(num<-1){
           control = num;
           if(control==num)
            printf("%dx^%d",control,i);
           else
            printf("%.1fx^%d",num,i);
        } 
        if(num==1){
          printf("+x^%d",i);
        }
        if(num==-1){
          printf("-x^%d",i);
        }
      }                              
    }
}

void find_primes(){
  int num1,num2,i,j,flag,sum,control; /* creating needed variables for function */
  flag = 0; /* flag for indicate prime number */
  sum = 0; /* sum for store our prime numbers */
  control = 0; /* control for loop that we check correct input */
  
  do{ /* here we check valid input*/
    printf("Enter two positive integer: ");
    scanf("%d %d",&num1,&num2);
    if(num1<=0||num2<=0){
      printf("You entered negative number!\n");
    }
    else
      control = 1;

  }while(control!=1);
    
  /* here we calculate prime numbers */  
  for(i=num1+1;i<num2;i++){
     for(j=2;j<=i/2;j++)
     {
          if(i%j==0){
            flag=1;
            break;
          } 
     }
        if(flag==0){
          sum = sum + i;
        }
        flag=0;         
  }
   printf("\nSum of prime numbers betweeen %d and %d is %d",num1,num2,sum);
}
int main(){
    /*===================================================*/
    printf("/*============PART1-POLYNOMIAL============*/\n");
    write_polynomial();
    printf("\n");
    printf("\n");
    /*==================================================*/
    printf("/*============PART2-ARMSTRONG============*/\n");
    check_armstrong_palindrome();
    printf("\n");
    printf("\n");
    /*===================================================*/
    printf("/*==============PART3-PRIME===============*/\n");
    find_primes();
    printf("\n");
    printf("\n");
    printf("/*===========END OF THE PROGRAM============*/\n");
    printf("/*=========================================*/\n");
}