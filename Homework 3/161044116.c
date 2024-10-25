#include <stdio.h>
#include <math.h>
#include <string.h>


#define MAX 1000 
#define MIN 2


void menu();		/*menu was used to select the desired party.*/
int part_1();								/*I created a function for each part.*/
int part_2();
void part_3();

int take_grades(int [] );
int take_exam_grades(int[]);
double calculate_homework(int[]);
double calculate_lab(int[]);
double calculate_all(int ,int[],int);

int main(){

menu();	
	return 0;

}

void menu()
{
	int menu,choice,a;
	while(a!=1)
	{	printf("\n*******MENU*******\n");
	 	printf("1 Part 1\n");
	 	printf("2.Part 2\n" );
		printf("3.Part 3\n");
	 	printf("4. Exit\n");
	 	printf("Enter menu: ");
	 	scanf("%d",&menu);
	 	switch(menu)
		{		
		 		case 1 :
				   part_1();
		 		break;

		 	 	case 2 : 
		 	 	part_2();
		 	 	break;

		 		case 3 :
				part_3();
		 		break;

				case 4: 
					a=1;
					break;

				default:
						printf("\nINVALID CHOICE \n");
		}
	}
}


int part_2()
{
	int array_lab[9],array_homework[9],array_exams[1];
	double average,average_lab,average_homework;
	
	printf("Please enter lab notes.\n");
	take_grades(array_lab);						/*function is called for note entry and array filled.*/
	average_lab=calculate_lab(array_lab);				/*array was calculated and stored in variable.*/
	
	printf("Please enter homework notes.\n");	
	take_grades(array_homework);							/*function is called for note entry and array filled.*/
	average_homework=calculate_homework(array_homework);		/*array was calculated and stored in variable.*/
	
	printf("Please enter midterm and final.\n");			
	take_exam_grades(array_exams);					
	
	average=calculate_all(average_homework,array_exams,average_lab);	/*sent to the function for the average of the stored data.*/
	printf("Average: %.2lf",average);
	
	return 0;
}

int take_grades(int array[]){
	int i;
	
	
	for ( i = 0; i < 10; ++i)				
	{
		printf("%d. grade: \n",i+1);
		scanf("%d",&array[i]);
	}
}
int take_exam_grades(int array[]){

	printf("Enter your midterm: ");
	scanf("%d",&array[0]);
	printf("Enter your final: ");
	scanf("%d",&array[1]);

}

double calculate_homework(int array[])
{
	int i;
	double average=0;
	for ( i = 0; i < 10; ++i)
	{
		average+=array[i];
	}
	return average/10;
}
double calculate_lab(int array[])
{
	int i;
	double average=0;
	for ( i = 0; i < 10; ++i)
	{
		average+=array[i];
	}
	return average/10;
}

double calculate_all(int homework,int array[],int lab){
	int result;
	result=(((homework*10)/100)+((lab*20)/100)+(array[0]*30/100)+(array[1]*40/100));
	return result;
}

void part_3(){
int i=0,j=0 ,k=0,number,star,emptiness;	
	printf("Enter number: ");
	scanf("%d",&number);
	star=2;							
	emptiness=number-1;
	
	while ( i < number)
	{
		for (j = 0; j < emptiness; ++j)
		{
			printf(" ");
		}
		for (j = 0; j< star; ++j)
		{
			if(j==0)
			{
				printf("/");
			}
			else if (j==star-1)
			{
				printf("\\");
			}
			else
			printf("*");
		}
		printf("\n");
		emptiness--;			/*reduced gaps as stars increase in each loop*/
		star +=2;				
		i++;
	}
	
	star -=2;				/*Stars and gaps set to printed  the inverse pyramid.*/
	emptiness=0;
	i=0;
	
	while(i < number)
	{
		for (j = 0; j < emptiness; ++j)
		{
			printf(" ");
		}
		for (j = 0; j< star; ++j)
		{
			if(j==0)
			{
				printf("\\");
			}
			else if (j==star-1)
			{
				printf("/");
			}
			else
			printf("*");

		}
		printf("\n");
		emptiness++;
		star -=2;
		i++;
	}
}


int part_1(){
		
		int c=0,oper;				
		char  str[MAX];				/*the string was used to store the numbers.*/
		str[0]=0;					/*The first number was stored in str0 but only number,If a double digit number is entered, the code explodes. */
		str[2]=0; 						/*user leaves space  in str1 */
		printf("1-for + \n");
		printf("2-for - \n");
		printf("3-for / \n");
		printf("4-for * \n");
		printf("5-for **\n");
		scanf("%d",&oper);
	
		printf("Enter your  number/numbers:  ");
		fgetc(stdin);										/*in order to counter the newline problem in buffer*/
	    fgets( str, MAX, stdin); 
	    

	    if(oper==1){
	    	 
	    	if(str[2]=='\0'){
	    	 	c=(str[0]-48)+c;
	    	 	printf("toplam: %d\n",c);
	    	}
	    	else{
	    	 	c=(str[0]-48)+(str[2]-48)+c;
	    	 	printf("toplam: %d\n",c);
	    	}

	    }
	    
	    else if(oper==2)
	    {
		    if(str[2]=='\0'){
		    	c= c-(str[0]-48);
		    	printf("toplam: %d\n",c);
		    }
		    else{
		    	c=(str[0]-48)-(str[2]-48);
		    	printf("toplam: %d\n",c);
		   	}
	    }
	    else if(oper==3)
	    {
			if(str[2]=='\0'){
			    c= c/(str[0]-48);
			    printf("toplam: %d\n",c);
			}
			else
			{
			 	c=(str[0]-48)/(str[2]-48);
		 		printf("toplam: %d\n",c);
			}


	    }
	    else if(oper==4)
	    {
	    	
	    	if(str[2]=='\0'){
			   	c= c*(str[0]-48);
			    printf("toplam: %d\n",c);
			}
			else
			{
				c=(str[0]-48)*(str[2]-48);
			    printf("toplam: %d\n",c);
			}
	    	

	    }
	    else if(oper==5)
	    {
	    	c=0;
	    	c=(str[0]-48)*(str[0]-48);
	    	printf("toplam: %d\n",c);
	    }
  
    return 0; 
}