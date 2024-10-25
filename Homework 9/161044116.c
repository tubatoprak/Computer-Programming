#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
	
	int age;
	char  * name;
	char  * surname;
	char  * musical_work;
	struct person *next;

} *top;

void scpy(char * d, char * s);

void addnode(char name[],char surname[],char musical_work[],int age);

void deletenode();

void sort_alphabetically();

void printstack();

void increasingly();

void swap(struct person *a, struct person *b);

void menu();

int main()
{
	top = NULL;
	menu();
	return 0;
}

void menu()
{
	int  a=1 , choice , age;
	char name[20] , surname[20] , creation[20];
	
	while(a!=0)
	{
		printf("\n****************MENU********************\n");
		printf("1.Add a Person to the Stack \n");
		printf("2.Pop a Person to the Stack \n");
		printf("3.Sort Alphabetical Order \n");
		printf("4.Sort Age in Increasing Order \n");
		printf("5.Exit Menu \n");
		printf("****************************************\n");
		printf("Select Your choise: ");
		scanf("%d",&choice);
		
		switch(choice)
		{	
			case 1: 
					printf("Enter Name: ");
					scanf(" %[^\n]s",name);
					printf("Enter Surname: ");
					scanf(" %s",surname);
					printf("Enter Creation: ");
					scanf(" %[^\n]s",creation);
					printf("Enter Age: ");
					scanf("%d",&age);
					addnode(name,surname,creation,age);
					printstack();
				break;
			
			case 2:
					deletenode();
					printstack();
				break;
			
			case 3:
					sort_alphabetically();
					printstack();
				break;
			
			case 4:
					increasingly();
					printstack();
				break;
			case 5:
					a=0;
		}
	}
}
void scpy(char * d, char * s)
{
	while(*d++ = *s++);
}

void addnode(char name[],char surname[],char musical_work[],int age)
{
	
 	struct person * temp = (struct person *) malloc(sizeof(struct person));
	temp->age = age;
	temp->name = malloc(sizeof(*name));
	scpy(temp->name, name); 
	temp->surname = malloc(sizeof(*surname));
	scpy(temp->surname,surname);
	temp->musical_work = malloc(sizeof(*musical_work));
	scpy(temp->musical_work,musical_work);
	
	if(top == NULL)
	{
		top = temp;
		top->next = NULL;	
	}
	
	else
	{
		temp->next = top;
		top = temp;
	}
}

void deletenode()
{
	struct person * temp;
	temp = top;
	
	if(temp == NULL)
	{
		printf("\nError : Empty stack");
        return;
	}
	
	else
		temp = temp->next;
	free(top);
	top = temp;	

}

void printstack()
{
	int count = 1;
	struct person * temp = top;
    
    if(temp == NULL)
	   return;
	
	else{
	    while(temp != NULL)
	    {
	    	printf("\n%d-) Name: %s",count,temp->name);
	    	printf("\n    Surname: %s",temp->surname);
	    	printf("\n    Creation: %s",temp->musical_work);
	    	printf("\n    Age: %d ",temp->age);
	    	printf("\n----------------------");
	    	temp = temp->next;
	    	count++;
	    }
	}
}

void swap(struct person *a, struct person *b) 
{ 	
	int temp;
	char * tempchar;
    
    temp = a->age; 
    a->age = b->age; 
    b->age = temp;
    
    tempchar = a->name;
    a->name = b->name;
    b->name = tempchar;

	tempchar = a->surname;
    a->surname = b->surname;
    b->surname = tempchar;

	tempchar = a->musical_work;
    a->musical_work = b->musical_work;
    b->musical_work = tempchar;
}

void increasingly()
{
	int count, i; 
	struct person * temp;
	struct person * temp2 = NULL; 
	
	if (top == NULL) 
    	return; 
    
    while(count)
    {

    	count = 0; 
        temp = top;

          while (temp->next != temp2) 
        { 
            if (temp->age > temp->next->age) 
            {  
                swap(temp, temp->next); 
                count = 1; 
            } 
            temp = temp->next; 
        } 
        temp2 = temp; 
    }
     
}


void sort_alphabetically(){

	  int count, i; 
	  struct person * temp;
	  struct person * temp2 = NULL; 
	  if (top == NULL) 
        return; 
   	
   	while(count)
    {
    	count = 0; 
        temp = top;

          while (temp->next != temp2) 
        { 
            if (strcmp(temp->name,temp->next->name)>0) 
            {  
                swap(temp, temp->next); 
                count = 1; 
            } 
            temp = temp->next; 
        } 
        temp2 = temp; 
    }

}
