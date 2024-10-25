#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SQUARE 1
#define RECTENGULAR 2 
#define CIRCULAR 3
#define PI 3.0

#define Red 0
#define Blue 2
#define Yellow 1
#define Black 3
#define White 4


double CreateBody (int shape);
int SetColor (int color); 
double LoadMoves(int shape, double body_size);
int SetAttackPower(int lower_bound, int upper_bound) ;
void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power);


int  main(){
		
	int shape, color, attack_power;
	double size_of_body, move_length;
	shape = CIRCULAR; // RECTENGULAR/ SQUARE // Pick one of them
	size_of_body = CreateBody (shape);
	color = 798;
	color = SetColor(color);
	move_length = LoadMoves(shape, size_of_body);
	attack_power = SetAttackPower (0, 150);
	ShowPokemon(shape, size_of_body, color, move_length, attack_power);
	return 0;
}


double CreateBody (int shape){
	
	int longside,shortside,r,side;						
	
	if (shape ==2)								/* If the shape is rectangular, the edge lengths is taken from the user and the area is calculated. */
	{
		printf("Please enter a longside  :");
		scanf("%d",&longside);
		printf("Please enter a shortside:  ");
		scanf("%d",&shortside);
		return  shortside * longside;
	}
	
	else if (shape ==1)					/* If the shape is square, the edge length is taken from the user and the area is calculated. */
	{
		printf("Enter side :");
		scanf("%d",&side);
		return side*side;
	}
	
	else if (shape ==3)							/* If the shape is circular, radius is taken from the user and the area is calculated. */
	{
		printf("Please enter a positive number for the radius: ");
		scanf("%d",&r);
		return  r*r*PI;
	}
}

int SetColor (int color){				
	
	if (color>=0 && color<=1000)
	{
		color = color % 5;
		return color ;
	}
	else return 1;									/*if the entered number is not in the desired range,returns the number=1*/
}

int SetAttackPower(int lower_bound, int upper_bound)	
{
	int random;
	srand(time(NULL));									
	random =lower_bound +(rand() % upper_bound);
	return random;
}

double LoadMoves(int shape, double body_size)		/*The environment is calculated according to the figure.*/
{
  	

  	if (shape ==2){
		return ((body_size/ 5)+5)*2 ;
	}
	
	if (shape ==1){
		return sqrt(body_size)*4;
	}
	
	if (shape ==3){
		return  sqrt((body_size/PI))*2*PI;
	}
}

void ShowPokemon(int shape, double body_size, int color, double move_length, int attack_power)
{
 	int a,i;
 	double rectengular=(move_length-10)/2,square=sqrt(body_size);	 /*we have found the edge or radius here. */
 	int radius=sqrt(body_size/PI);
 	printf("\n");
 	if(shape==1)
 	{
 		 
 		for (i=0; i <square ;i++)								/*I used the for loop to make the  square.*/
 		{
 			for (a = 0; a <square; a++)
 			{
 				printf("X");
 			}
			printf("\n");
		}

		printf("\nName: SQUARE POKEMON\n");

		
 	}

 	if (shape==2)
 	{
	 	for (i=0; i <5;i++)
	 	{
	 		for (a = 0; a < rectengular; a++)       /*I used the for loop to make the rectangle.*/
	 		{
	 			printf("X");
	 		}
			printf("\n");
		}
		printf("\nName: RECTANGULAR POKEMON\n");	

		
	}
	if (shape==3)
	{
		/* So I did this code in 3 pieces.First and last line has their own blanks (due to having half a tab based on given number). For middle line its also decided (Radius-1 tabs). And I used middle lines in 2 pieces,increasing middlegap and decreasing frontgap for top side,and the opposite for bottom side. */

		int iseven=0;
	    int i,j,line=radius,currentline=1;
	    int gap=-1;
	    int savepoint;
	    int savefirst;
		int frontgap=0;			
		int middlegap;
		if(radius%2==0)
		{
			iseven=1;
	    }
		
	    if(radius<2)                                     /* this is a special situation so I used a piece without any tabs */
	    {
	        printf("X\n");
	    }
	   
	    else
	    {
		    if(radius%2==0)
		    {                                                /* due to certain calculations I had to adjust lines number */

		        line=line+1;
		    }
			frontgap=radius/2;
	    	for(i=0;i<(radius-1)/2;i++)
	    	{
	       		 printf("\t");
	    	}
			if(iseven==1)
			{
				printf("    ");
			}
	   		printf("X\n");

	    	currentline=currentline+1;
	    	gap+=2;
		    for (int i = 0; i < line/2-1; ++i)                     /* Top half of the shape */
		    {
		    	frontgap-=1;
		        for (int i = 0; i <frontgap; ++i)
		        {
		        	printf("\t");

		        }

				printf("X");
		        for (int i = 0; i < gap;i++)
		        {
		        	printf("\t");
	            }
				if(radius%2==1)
				{
					printf("\t");
				}
	            

	            printf("X\n");
	            currentline += 1;
	            gap+=2;
			}
	    
		    savefirst=radius-currentline+1;
		    savepoint=gap;
		    gap=0;
	   		if (currentline==(line+1)/2)                    /* Middle line of the shape */
	    	{
	            printf("X");
	            for (int i = 0; i < radius-1; ++i)
	            {
	                printf("\t");
	            }
	            printf("X\n");
	            currentline+=1;
	            gap+=2;

	    	}

	    	for(int i=0;i<line/2-1;i++)
	    	{                                               /* Bottom half of the shape */
		        for(int i=0;i<frontgap;i++){
		            printf("\t");
		        }
		
	        	printf("X");
	        	for(int i=0;i<savepoint-gap;i++)
	        	{
	            printf("\t");
	        	}
				if(radius%2==1){
						printf("\t");
				}
		        printf("X\n");
		        currentline+=1;
		        savefirst+=1;
		        gap+=2;
				frontgap+=1;
	    	}

	    	for(i=0;i<(radius-1)/2;i++)
	    	{                                                     /* Last line */

	       		printf("\t");
	    	}
			if(iseven==1)
			{
			printf("    ");
			}
	    	printf("X\n");
		}

		printf("\nName: CIRCULAR POKEMON\n");
	}
	printf("Size: %.0lf\n",body_size);                    /*Finally, I pressed it according to colors.*/
		
		if (color==1)
		{
			printf("Color :Yellow");
		}
			
		else if (color==2)
		{
			printf("Color :Blue"); 
		}
		else if (color==3)
		{
			printf("Color :Black");	
		}
		else if (color==4)
		{
			printf("Color :White");	
		}	
		else
		{
			printf("Color :Red");
		}
		printf("\nMove: %2.lf\n",move_length);
		printf("Attack Power: %d\n",attack_power );

}


