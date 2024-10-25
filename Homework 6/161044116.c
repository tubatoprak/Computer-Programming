#include <stdio.h>

int menu();
int gcd(int number1,int number2);
int formula1(int number);
int formula2(int number,int index);
int my_power(int x,int y);
int find_upper_latter(char str[],int start,int lenght);
int len(char *str);
void mergeSort(int array[], int begin, int size);
void merge(int array[], int beginning, int middlesize,int size,int newlenght1,int newlenght2);                                  
int main()
{
	menu();
	return 0;
}
int menu(){
	int a,choice;
	int part1number1,part1number2,part1result;  //variables for part1
	int part4number,temp,index,part4result;	 		 // variables for part4
	int part3number,part3result;						// variables for part3
	char part5str[100],part5result;							// variables for part5
	int part2size,part2array[100];								// variables for part2
	
	while(a!=1){
		printf("\n\n******MENU*******\n");		
		printf("1.GCD CALCULATOR\n");
		printf("2.SORTED ARRAY\n");
		printf("3.FORMULA 1\n");
		printf("4.FORMULA 2\n");
		printf("5.STRING\n");
		printf("6.EXIT\n");
		printf("PLEASE ENTER YOUR CHOICE ");
		scanf("%d",&choice);
		switch(choice){
			case 1:	
					printf("Enter first number: ");
					scanf("%d",&part1number1);
					printf("Enter second number: ");
					scanf("%d",&part1number2);
					part1result=gcd(part1number1,part1number2);
					printf("Greater common divisor of %d and %d is %d\n",part1number1,part1number2,part1result);
					break;
			case 2:
					printf("Enter the lenght of list ");
					scanf("%d",&part2size);			         /*loop to fill array*/
					for (int i = 0; i < part2size; ++i)
					{
						scanf("%d",&part2array[i]);
					}
					mergeSort(part2array, 0, part2size - 1);  
					for (int i = 0; i < part2size; ++i)			/*loop to print array*/
					{
						printf("%d  ",part2array[i]);
					}
					break;
			case 3:
					
					printf("Enter number: ");
					scanf("%d",&part3number);
					part3result=formula1(part3number);
					printf(" %d \n",part3result );
					break;
			case 4:
					printf("Enter your number: ");
					scanf("%d",&part4number);
					temp = part4number;
					  while (temp != 0) 				/*to find count digit number*/
					   {
					     index = index + 1;
					     temp = temp / 10;
   						}
   					part4result=formula2(part4number,index);
   					
   					if(part4result==part4number){
   						printf("Equal\n");
   					} 
   					else
   						printf("Not Equal \n");
   					break;
			case 5:
					printf("Please enter string: ");
					scanf("%s",part5str);
					int lent=len(part5str);           /*firsty I find lengh of string */
					part5result=find_upper_latter(part5str,0,lent);
					if(part5result=='a')
						printf("No capital letters in your string!!\n");  /*if the string is null,warning message*/
					else
						printf("%c is the first capital letter in your string.\n",part5result);
					break;
			case 6:
					a=1;
					break;
			default:
				printf("Invalid choice\n");
				break;
		}
	}	
}
int gcd(int number1,int number2){
	
	if(number2==0 || number1==0){
		return 0;
	}

	if (number2==number1){        /*simple case*/
        return number2;
	}
    if(number2>number1){						/*extra simple case */
        return gcd(number2-number1,number1);
    }
    return gcd(number2,number1-number2);
}
int formula1(int number){
	int i=0;
	
	if(number==0)
		return 0;
	while(number!=1){
		if(number%2==0){
			printf("%d ",number );
			number=formula1(number/2);		
		}
		else {
			printf("%d ",number );
			number=formula1(3*number+1);
		}
	i++;
	}
	return number;
}
int formula2(int number,int index){
	
	if(number!=0){
		return my_power((number%10),index)+formula2(number/10,index);
	}
	else 
		return 0;
}
int my_power(int x,int y){
	
	if(y == 0) 
		return 1;
    else 
    	return x * my_power(x, y-1);
}
int len(char *str){
	if (*str == '\0')  
        return 0; 
    else
        return 1 + len(str + 1);  
}
int find_upper_latter(char str[],int start,int lenght){
	char ans;
	char temp='a';
	if(lenght<=0)
		return temp ;
	
	if(start==lenght)
		return temp;
	
	if(str[start]>='A'&& str[start]<='Z'){
		ans=str[start];
		return ans;
	}		
	return find_upper_latter(str,start+1,lenght);
}
void merge(int array[], int beginning, int middlesize,int size,int newlenght1,int newlenght2) 
{ 
    int i=0, j=0, k=0; 
	int temparray[newlenght1],temparray2[newlenght2]; 
  
    for (i = 0; i < newlenght1; i++){
        temparray[i] = array[beginning + i]; 			/*firsly  the arrays are  filled*/
    }
    
    for (j = 0; j < newlenght2; j++){ 
        temparray2[j] = array[middlesize + 1+ j]; 
  	}
    i = 0;  
    j = 0;   
    for(k=beginning;i<newlenght1 && j<newlenght2;k++){		/*Then the arrays were compared.*/
        if (temparray[i] <= temparray2[j]) 							/*finally filled in our original array.*/
        { 
            array[k] = temparray[i]; 
            i++; 
        } 
        else
        { 
            array[k] = temparray2[j]; 
            j++; 
        } 
    }
    for (i;i < newlenght1;i++,k++) 							
    { 
        array[k] = temparray[i]; 
    } 
    for (j; j < newlenght2;j++,k++)
    {
        array[k] = temparray2[j];
    }
} 
void mergeSort(int array[], int begin, int size) 
{   
    if (begin< size) 
    { 
        int middle =((size-begin) /2)+begin;			/*middle of string*/
        int newlenght1 = middle - begin + 1; 				/*new size for new array*/
        int newlenght2 =  size - middle; 		
        mergeSort(array, begin, middle); 		
        mergeSort(array, middle+1, size); 
 		merge(array, begin, middle, size,newlenght1,newlenght2); 
    } 
} 