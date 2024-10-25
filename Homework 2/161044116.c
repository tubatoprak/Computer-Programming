#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int make_a_guess (int trial, int min, int max);
void show_scores(int score_human, int score_program);
void draw_hourglass (int height);
void draw_mountain_road (int length, int max_radius);
void menu();
int game_1 (int trial, int * score_human, int * score_program);  /* I created function for game 1 because I needed a function that I could use 
																					two other functions.*/




int main()
{	
	srand(time(NULL));
	menu();	
	return 0;
}

void menu(){

	int menu,choice,a=0,height;
	int n,r;                                   /*for draw mountains road*/
	int score_human=0, score_program=0;           	 /*I used variables to keep score records.*/
	 	while(a!=1)
	 	{
	 		printf("\n*******MENU*******\n");
		 	printf("1 Play Lucky Number\n");
		 	printf("2. Draw Hourglass\n" );
		 	printf("3. Draw Mountain Road\n");
		 	printf("4. Exit\n");
		 	printf("Enter menu:  ");
		 	scanf("%d",&menu);

		 	switch(menu)
		 	{	
		 	
		 		case 1 :
		 		game_1 (10, &score_human, &score_program);		/*I defined trial  */
		 		break;

		 	 	case 2 : 
		 	 	printf("Height= ");
		 	 	scanf("%d",&height);
		 	 	draw_hourglass (height);
		 	 	break;

		 		case 3 :
		 		
				printf("Enter N: ");
				scanf("%d",&n);
				printf("Enter R: ");
				scanf("%d",&r);
		 		draw_mountain_road (n,r);
		 		break;

				case 4: 
					a=1;
					break;

				default:
						printf("\nINVALID CHOICE \n");
			}
		}
}

int make_a_guess (int trial, int min, int max){		/*this function takes guess number from the user and return guess number.*/
	int guessnumber;
	
	printf("(Trial : %d) Make a guess between %d and %d: ",trial,min,max);
	scanf("%d",&guessnumber);
	return guessnumber;

}
void show_scores(int score_human, int score_program){			/*this function displays the competition score on the screen.*/
	printf("You Score: %d Program Score: %d \n",score_human,score_program);
}
void draw_hourglass (int height){			
 int  space=0, star=height, i, k;

	for(i=0; i<height; i++)
	{					
		 	
		 	for(k=0; k<star;k++){
		            printf("*");
		    } 
			if( i < (height / 2) ){
		            star-=2;
		            space++;
		    }
		    else{
			    star+=2;
			    space--;
		    }
		    printf("\n");
		    for(k=0; k<space;k++)    
		    printf(" ");
	}       
}
void draw_mountain_road (int length, int max_radius){
	int radius;
	int frontspace;
	int i,j,k;
	
	frontspace=max_radius;
	
	for(i=0;i<length;i++)
	{
		radius=(rand()%(max_radius-1))+1;    		/*computer generates random number.*/
		for(j=0;j<2*radius+1;j++)               
		{
			for(k=0;k<frontspace;k++)			/*loop used for spaces.*/
			{
				printf(" ");
			}
			if(i%2==0)						
			{
				if(j<radius)
				{
					printf("\\");			
					frontspace+=1;       /* the space was increased so that it could continue where it was left in the next loop.*/
				}
				else if(j==radius)
				{
					printf("|");
					frontspace-=1;     /*the space was reduced so that it could continue where it was left in the next loop.*/
				}
				else
				{
					printf("/");
					frontspace-=1;
				}
			}
			else
			{
				if(j<radius)
				{
					printf("/");
					frontspace-=1;
				}
				else if(j==radius)
				{
					printf("|");
					frontspace+=1;
				}
				else
				{
					printf("\\");
					frontspace+=1;
				}
			}
			printf("\n");
		}
	}
 }
int game_1 (int trial, int * score_human, int * score_program){    /*I defined this function for the game 1*/
	

	int Luckynumber,i,guessnumber,temp,min=1,max=1024;  
	Luckynumber=1+rand()%1024;
	
	for (i = 1; i <=trial; ++i)			
	{
		
		guessnumber = make_a_guess(i,min,max);		/* call the function to get the guess from the user.*/
		temp=abs(guessnumber-Luckynumber);						/*the distance is determined and sent to the range value.*/
		
		
		if(temp==0)
		{
			printf("You win\n");
			i=trial;
			show_scores(++(*score_human), (*score_program));    		  /*for score saved*/
			return i;
		}
		else if(temp>512 && temp<1023)
		{
			printf("Distance: 10\n");
		}
		else if(temp>=256 && temp<=511)
		{
			printf("Distance: 9\n");
		}
		else if(temp>=128 && temp<=255)
		{
			printf("Distance: 8\n");
	
		}else if(temp>=64 && temp<=127)
		{
			printf("Distance: 7\n");
		}
		else if(temp>=32 && temp<=63)
		{
			printf("Distance: 6\n");
		}
		else if(temp>=16 && temp<=31)
		{
			printf("Distance: 5\n");
		}
		else if(temp>=8 && temp<=15)
		{
			printf("Distance: 4\n");
		}
		else if(temp>=4 && temp<=7)
		{
			printf("Distance: 3\n");
		}
		else if(temp>=2 && temp<=3)
		{
			printf("Distance: 2\n");
		}
		else if(temp==1){
			printf("Distance: 1\n");
		}
		if(Luckynumber<guessnumber)
		{										/*I used "if-else" to change "max" and "min"*/
		max=guessnumber;
		}
		else
		{
		min=guessnumber;
		}	
	}
	printf("\nLucynumber: %d\n",Luckynumber);
	show_scores((*score_human), ++(*score_program));		/*used to record the score when the computer wins.*/
	return i;
}
