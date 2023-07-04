#include <stdio.h>
#include <stdlib.h>

	void fibonacci(int input){
	    
		int i,term1,term2,term3; /* needed variables for fibonacci function */
		
		term1 = 0;
	    term2 = 1;
		for(i=1;i<=input+1;++i){
			if(term1>0){ /* we dont want to print '0' */
			 printf("%d\n",term1);  /* then we printf every term1 value */
		}
			term3=term1+term2;
			 term1=term2;
			  term2=term3;
		}
		printf("--------------------------*/\\*------------------------\n");
    }
    /*=============================================================*/
	void check_Harmonic(int number){
        /* neccessary variables for function */
		int i,reminder,check;
		float control,sum;
		sum = 0;
		
		for(i=1;i<number;i++){   /* calculating divisors of number and adding to "sum" variable */
			reminder = number%i;
			  if(reminder==0)
			    sum =sum + (number/i);											    
	    }     
    	  sum+=1;  
		  control=sum/number; /* typecasting for check harmonic divisor number */
	      check=control;      /* so that we can find whether it is integer or not */
			
			if(check==control) /* printing the condition of number */
	           printf("\n%d is Harmonic Divisor Number.\n\n",number);
	        else
			   printf("\n%d is NOT Harmonic Divisor Number.\n\n",number);	
	return;
	} 
	/*=============================================================*/ 
    int check_Perfect(int number){
    	int i,reminder,sum;  /* needed variables for function */
		sum = 0;
		
		for(i=1;i<number;i++){   /*finding whether number perfect number or not */
			reminder = number%i;
			 if(reminder==0)
			  sum +=i;											    
	    }     
		if(sum==number) /* printing condition of input here */
			printf("\n%d is a Perfect number\n",number);								
		else
			printf("\n%d is not a Perfect number\n",number);

	return;
	}
	/*=============================================================*/
	void calculate_fibonacci_sequence(){
	    char char_command;     /* input variables */
	    int int_command,flag;  
	    flag=1;                /* control variable for do while */ 
	    
		do{
		    /* getting input here */
		    scanf("%d",&int_command);
	        char_command=getchar();    
	    	/*=====================*/	
		        if(int_command!=0){  
	    	        if(int_command<0){                                                          /* if input is negative */
	    		       printf("\nPlease enter positive term(s) number(Enter '*' to exit): ");	/* error message        */
			        }	
		            else{  /* if input is positive it calc fibonacci here */
				       printf("\n------------*/Calculating Fibonacci\\*------------\n\n");
					    fibonacci(int_command);
					      printf("Please enter term(s) number (Enter '*' to exit) : ");   /* printf this for new fibo calculation */
			        } 		            
		        }
		        
				else{ /* if input is not number */
		        	if(char_command=='*'){ 
		                printf("_____________________Exiting_____________________\n\n");
						  flag=0;  /* to exit function */
					}
					else{
					    printf("\nPlease enter numeric term(s) number (Enter '*' to exit) : ");	/* error message for char input */
					}			
		        }	
	            int_command=0; 
	    }while(flag==1);	
	}
	/*=============================================================*/ 	
	void decide_perfect_harmonic_number(){
		/* creating input variables */
		int int_command=0;
		char char_command='0';
		int flag=1; /* control variable for do while */ 
		   
		do{	        
				/* getting input */
				scanf("%d",&int_command);
		        char_command=getchar();
			    
				if(int_command!=0){    			    	
					if(int_command<0){  /* if input is negative number */
		        		printf("\nPlease enter positive term(s) number(Enter '*' to exit): ");
					}
					else{   /* if input is positive number */
						printf("\n------------*/Calculating PERFECT/HARMONIC\\*------------\n\n");
					     check_Perfect(int_command); /* function for perfect number */
						   check_Harmonic(int_command);	 /* function for harmonic divisor number */					
					         printf("Please enter term(s) number (Enter '*' to exit) : ");   /* printing for new input after calculations */
					}
				}
				else{  /* if input is not number */
					if(char_command=='*'){
		                printf("_____________________Exiting_____________________\n\n");
						 flag=0; /* making flag 0, so we can exit function */
					}
					else{ /* if input is char */
					    printf("\nPlease enter numeric term(s) number (Enter '*' to exit) : ");							
					}
				}    		        	    				
		        printf("\n\n");	
				int_command=0;			   
		}while(flag==1); 			
	}
    /*=============================================================*/
    void difference_max_min(){
         double min,max;
         double num1,num2,num3,num4,num5; /* we create num variables to store input */
         /*getting inputs */
		 printf("Enter first number : ");
	      scanf("%lf",&num1);
	     printf("Enter second number : ");
	      scanf("%lf",&num2);
	     printf("Enter third number : ");
          scanf("%lf",&num3);
	     printf("Enter forth number : ");
	      scanf("%lf",&num4);
	     printf("Enter fifth number : ");
	      scanf("%lf",&num5);
		 
		 /* at the beginning minimum and maximum values are equal to num1 */
		 min=num1; 
		 max=num1;
		 /* then we find min value by comparing every value */
		 if(min>num1)
		    min=num1;		 
		 if(min>num2)
		    min=num2;		 
		 if(min>num3)
		    min=num3;		 
		 if(min>num4)
		    min=num4;		 
		 if(min>num5)
		    min=num5;
		 
		 printf("\nMinimum number is %g\n",min);
		 
		 /* here we find max number by comparing every value */
		 if(max<num1)
		    max=num1;			   		 
		 if(max<num2)
		    max=num2;		 
		 if(max<num3)
		    max=num3;		 
		 if(max<num4)
		    max=num4;		 
		 if(max<num5)
		    max=num5;        			 
		 
		 printf("Maximum number is %g\n",max); 
		 printf("Difference between maximum and minimum is %g\n",max-min);  /*calculating and printing difference */ 
	}
	/*=============================================================*/
    void bmi_calculation(){
    	float weight,height,BMI; /* neccessary variables for function */
		
		/* getting weight and height inputs */
		printf("\nPlease enter your weight in kg : ");
    	scanf("%f",&weight);
    	printf("\nPlease enter your height in m : ");
    	scanf("%f",&height);
    	
		BMI = weight/((height)*(height));   /* calculating BMI here */
    	
		/* Printing  the category according to BMI */
		if(BMI<16.0)
    	   printf("Your category : Severely Underweight\n");
    	else if(BMI<18.5)
    	   printf("Your category : Underweight\n");
    	else if(BMI<25.0)
    	   printf("Your category : Normal\n");
    	else if(BMI<30.0)
    	   printf("Your category : Overweight\n");
    	else 
    	   printf("Your category : Obese\n");
	}
	/*=============================================================*/
    
int main(){
    /*-----------------------------------------------------------*/
	/*----------------------PART1-FIBONACCI----------------------*/
	printf("--------------------*/PART1\\*---------------------\n");
	printf("------------------*/Fibonacci\\*-------------------\n");
	printf("Please enter term(s) number (Enter '*' to exit) : ");
    calculate_fibonacci_sequence();
    printf("PART1 is over\n");
    /*-----------------------------------------------------------*/
	/*------------------PART2-NATURAL-HARMONIC-------------------*/
	printf("--------------------*/PART2\\*---------------------\n");
	printf("---------------*/PERFECT/HARMONIC\\*---------------\n");
	printf("\nPlease enter input number (Enter '*' to exit) : ");
    decide_perfect_harmonic_number();
    printf("PART2 is over\n");
    /*-----------------------------------------------------------*/
    /*-----------------------PART3-MAX-MIN-----------------------*/ 
    printf("--------------------*/PART3\\*---------------------\n");
	printf("------------------*/DIFFERENCE\\*------------------\n");
    printf("\nPlease enter 5 numbers : \n");
    difference_max_min();
    printf("PART3 is over\n"); 
	/*-----------------------------------------------------------*/
    /*-------------------------PART4-BMI-------------------------*/ 
	printf("--------------------*/PART4\\*---------------------\n");
	printf("----------------*/BODYMASSINDEX\\*-----------------\n");
	bmi_calculation();
	printf("PART4 is over\n");
	/*-----------------------------------------------------------*/
	/*-----------------------------------------------------------*/
	return 0;
    }