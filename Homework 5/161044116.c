#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int compare_strings(char a[], char b[]);
void random_letter(char array[15][15]);
void settled_word(char array[15][15],char *dict[]  ,  int coord[][4], int size_x , int size_y );
void settled_upper_word(char array[15][15], int coord[4]);

int get_line_size(char *line) {
	
	char *ch_iter = line; // so as not to lose beginning of line
	int counter = 0;
	// go until you see new line or null char
	while(*ch_iter != '\n' && *ch_iter != '\0') {
		ch_iter++; // next char
		counter++; // increment counter
	}
	
	return counter;
}

void copy_string(char *source, char *destination) {
	// get iterators over original pointers
	char *src_iter = source;
	char *dst_iter = destination;
	// until null char
	while (*src_iter != '\0') {
		// copy pointers
		*dst_iter = *src_iter;
		// advance to next char
		src_iter++;
		dst_iter++;
   }
   // terminate string
   *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line;
	// go until you see new line
	while(*ch_iter != '\n' && *ch_iter != '\r') {
		ch_iter++; // next char
	}
	*ch_iter = '\0'; // overwrite new line
}

void print_dictionary(char *dict[]) {
	int i;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		printf("%s\n", dict[i]);
	}
}

void print_coord(int coord[DICT_SIZE][4]) {
	int i, j;
	for(i = 0 ; i < DICT_SIZE ; i++) {
		for(j = 0 ; j < 4 ; j++) {
			printf("%d ", coord[i][j]);
		}
		printf("\n");
	}
}

void print_array(char array[15][15]){
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j)
			printf("%c ",array[i][j] );
		
		printf("\n");
	}
}

int main(){
	
	char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];    
    char line[LINE_LEN];
	
	char foundstr[15];				/*input for founded word */
	int  x,y;						/*input coordinat*/
	FILE *fp = fopen("word_hunter.dat", "r");
									/*defined map*/
	char array[15][15];
	srand(time(NULL));
	int line_counter = 0;
	int dict_counter = 0;
	int i=0,j=0;

	
	
	while(fgets(line, LINE_LEN, fp) != NULL){
		if(line_counter%5 == 0) {
			dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
			remove_newline(line);
			copy_string(line, dict[dict_counter]);
		} else if (line_counter%5 == 1){
			coord[dict_counter][0] = atoi(line);
		} else if (line_counter%5 == 2){			
			coord[dict_counter][1] = atoi(line);		
		} else if (line_counter%5 == 3){
			coord[dict_counter][2] = atoi(line);
		} else if (line_counter%5 == 4){
			coord[dict_counter][3] = atoi(line);
			dict_counter++;
		}
		line_counter++;
	}
	
	 fclose(fp);
	// print_dictionary(dict);
	// print_coord(coord);
	// WRITE HERE...
		
	random_letter(array);
	settled_word(array,dict ,coord, DICT_SIZE , 4);
	print_array(array);

	int a = 0;
	while(a!=DICT_SIZE){

		printf("\nPlease enter the character you found: \n");
		scanf("%s",foundstr);
		if(compare_strings(foundstr,"exit" ) == 0) {
			return 0;
		}

		int check;
		printf("Enter x coordinator\n");
		scanf("%d",&x);
		printf("Enter y coordinator\n");
		scanf("%d",&y);
		int location =0;
		for(i=0;i<DICT_SIZE;i++){		                                

			check = compare_strings(foundstr,dict[i]);        
			if(check != -1 && (y==coord[location][0] || y==coord[location][2]) && (x==coord[location][1] || x==coord[location][3]) )
				break;
			location++;
		}
		if(location != DICT_SIZE){
			settled_upper_word(array,coord[location]);
			print_array(array);
			a++;
		}
	}

	if(a==DICT_SIZE){
		printf("YOU WIN!!!!!\n");
	}
	return 0;

}

void random_letter(char array[15][15]){			/* to random characters*/
	int i,j;
	for (i = 0; i < 15; ++i)
	{
		for ( j = 0; j < 15; j++)
		{
			array[i][j]='a'+rand()%26;
		}
	}		
}
int compare_strings(char str1[], char str2[]){
	int i = 0;
	while (str1[i] == str2[i]) {
		if (str1[i] == '\0' || str2[i] == '\0')
			break;
		i++;
	}

	if (str1[i] == '\0' && str2[i] == '\0')
		return 0;
	else
		return -1;
}

void settled_word(char array[15][15], char *dict[] , int coord[][4] , int size_x , int size_y  ){
	
	int start_x;
	int end_x;
	int start_y;
	int end_y;
	int tempnumber;
	int l=0;
	
	for( int i = 0 ; i < size_x ; i++) {
		tempnumber = 0;
		while(dict[i][tempnumber] != '\0') {
			tempnumber++;
		}

		start_x = coord[i][0];
		start_y = coord[i][1];
		end_x = coord[i][2];
		end_y = coord[i][3];
		tempnumber = 0;
		
		if(start_x == end_x || start_y == end_y  ) {				/*8 directions for vertical and horizontol words */
			if(start_y < end_y) {
				for(int k = start_x ; k <= end_x ; k++) {
					for(int l = start_y ; l <= end_y ; l++) {
						array[k][l] = dict[i][tempnumber++];
					}
				}
			}
		
			else{

				for(int k = start_x ; k <= end_x ; k++) {
					for(int l = start_y ; l >= end_y ; l--) {
						array[k][l] = dict[i][tempnumber++];
					}
				}		
			}
			
			if(start_x > end_x) {
				l = start_y ;
				for(int k = start_x ; k >= end_x ; k--) {
					array[k][l] = dict[i][tempnumber++];	
				}
			}
		}
																					/*cross words in  directions*/
		else if(start_x < end_x && start_y < end_y) {
			for(int  m = start_x ,  z = start_y ; m <= end_x ; m++, z++) {
				array[m][z] = dict[i][tempnumber++];
			}
		}
		else if(start_x > end_x && start_y > end_y) {
			for(int  m = start_x ,  z = start_y ; m >= end_x ; m--, z--) {
				array[m][z] = dict[i][tempnumber++];
		
			}
		}
		else if(start_x < end_x && start_y > end_y) {
		for(int  m = start_x ,  z = start_y ; m <= end_x ; m++, z--){
			array[m][z] = dict[i][tempnumber++];
			}
		}
		else if(start_x > end_x && start_y < end_y) {
		for(int  m = start_x ,  z = start_y ; m <= end_x ; m--, z++){
			array[m][z] = dict[i][tempnumber++];
			}
		}					
	}
}

void settled_upper_word(char array[15][15], int coord[4]){		  		  /*for uppercase word*/
	
	if (coord[1] > coord[3]){
		int temp = coord[1];
		coord[1] = coord[3];
		coord[3] = temp;
	}

	if (coord[0] > coord[2]){
		int temp = coord[0];
		coord[0] = coord[2];
		coord[2] = temp;
	}
	if (coord[0] == coord[2] || coord[1] == coord[3]){			   /*for horizontal and vertical*/
		for (int i = coord[1]; i <= coord[3]; ++i)
			for (int j = coord[0]; j <= coord[2]; ++j)
				if(array[j][i] <= 'z' && array[j][i] >= 'a')
					array[j][i]-=32;
	}
	else{
		for(int i = coord[1], j = coord[0]; i <= coord[3]; ++i, ++j)			/*for cross*/
			if(array[j][i] <= 'z' && array[j][i] >= 'a')
				array[j][i]-=32;
	}
	

}
