#include <stdio.h>

typedef enum{
	Charmander=0,
	Pikachu,
	Squirtle,
	Bulbasaur,
	Pidgeotto,
	Ratata,
	Mug,
	Caterpie,
	Zubat,
	Krabby
} pokemon;

typedef enum{
	quadratic=0,
	linear
} attack_type;

void menu();

void pokedex(char  Pokemon_name[][12], int range[],int attack_power[],attack_type type[], int stamina[]);

void oaks_laboratory(char  Pokemon_name[][12], pokemon Pokemons[],pokemon *my_Pokemons);

void show_Pokemons(char  Pokemon_name[][12], pokemon Pokemons[],int pokemon_count);

void catch_a_pokemon(char  Pokemon_name[][12], pokemon Pokemons[],pokemon *my_Pokemons);

void release_a_pokemon(char  Pokemon_name[][12], pokemon Pokemons[],pokemon *my_Pokemons);

void battle(char Pokemon_name[][12], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_Pokemons[]);

void show_area (char Pokemon_name[][12],int area[8][8],int pokemon_staminas[8][8]);

int compare_strings(char a[], char b[]);				/*For Part1 compare string*/

int  main()
{
	menu();
	return 0;
}

void menu()
{
	attack_type type[10] = {quadratic, linear, linear, linear, quadratic, linear, quadratic, quadratic, linear, linear};
	char Pokemons[10][12]={"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};
	int attack_power[10]={500,350,300,400,250,250,350,200,350,300};
	int range[10]={1,3,4,3,2,2,1,2,3,2};
	int stamina[10]={2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
	pokemon pokemons[10]={Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby};
	pokemon my_Pokemons[4];
	int a=0,menu;
	while(a!=1)
	{
		printf("\n\n1. Open Pokedex\n");
		printf("2. Go to Oak’s Laboratory\n" );
		printf("3. Enter the tournament\n");
		printf("4. Exit\n");
		printf("Enter menu:  ");
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:
				pokedex(Pokemons,range,attack_power,type,stamina);
				break;
			case 2:
				oaks_laboratory(Pokemons, pokemons, my_Pokemons);
				break;
			case 3:

				break;
			case 4:
				a=1;
				break;
		}
	}
}

int compare_strings(char str1[], char str2[])
{
   int i = 0;
   while (str1[i] == str2[i])
   {
      if (str1[i] == '\0' || str2[i] == '\0')
         break;
    i++;
   }
   if (str1[i] == '\0' && str2[i] == '\0')
      return 0;
   else
      return -1;
}
void pokedex(char Pokemon_name[][12], int range[],int attack_power[],attack_type type[], int stamina[])
{
	int i,a=0,j;
	char str[11];
	while(a!=1)
	{
		printf("Please type name of the Pokémon (type exit to close Pokedex):  ");
		scanf("%s",str);
		if(compare_strings(str,"exit" ) == 0)
		{
			a = 1;
		}
		for (int i = 0; i < 10; ++i)
		{
			if(compare_strings(str,*(Pokemon_name+i))==0)
			{
				printf("Name: %s \n",Pokemon_name[i]);
				
				if(type[i] == linear)
				{
					printf("A.type: Linear\n" );
				}
				else if(type[i] == quadratic)
				{
					printf("A.type: Guadratic\n" );
				}
				printf("Range: %d block\n", range[i]);
				printf("A. Power: %d\n", attack_power[i]);
				printf("Stamina :%d\n",stamina[i]);
			}
		}		
	}
}
void oaks_laboratory(char  Pokemon_name[][12], pokemon Pokemons[],pokemon *my_Pokemons)
{
	int b,i=0,selected,menu,c,pokemon_count;
	while (b!=1)
	{
		printf("\n\nWelcome To Laboratory of Professor Oak.How Can I Help You ?\n");
		printf("1. Show Pokémons \n");
		printf("2. Catch a Pokémon\n" );
		printf("3. Release a Pokémon\n");
		printf("4. Show my pocket\n");
		printf("5. Back\n");
		printf("Enter menu: ");
		scanf("%d",&menu);
		switch(menu)
		{
			case 1:
				show_Pokemons(Pokemon_name, Pokemons, 10);
				break;
			case 2:	
				if(i<4)
				{	
					catch_a_pokemon(Pokemon_name,Pokemons,&my_Pokemons[i]);
					i++;
				}
				else
					printf("There are four pokemon in your pocket!!!\n");
				break;
			case 3:
				printf("Please enter the pokemon number you want to relase. \n");
				scanf("%d",&selected);
				for(c=selected; c < i; c++)
				release_a_pokemon(Pokemon_name,Pokemons,&my_Pokemons[c]);
				i--;
			case 4:
					pokemon_count = i;
					show_Pokemons(Pokemon_name, my_Pokemons, pokemon_count);
					break;
			case 5:
					b=1;
		}
	}
}
void show_Pokemons(char  Pokemon_name[][12], pokemon Pokemons[],int pokemon_count)
{
	int i;
	if(pokemon_count == 10)
	{	
		printf("\n");
		pokemon_count = 10;
		for (i = 0; i < pokemon_count; ++i)
		{	
			printf("%d-) %s\n",i,Pokemon_name[i] );
		}
	}
	else 
	{
		printf("\n**Pokemons In My Pocket**\n");
		for(i = 0 ; i < pokemon_count ; ++i)
		{
			if(Pokemons[i] == 0)
			{
				printf("%d- Charmander\n",i);
			}
			else if(Pokemons[i] == 1)
			{
				printf("%d- Pikachu\n",i);
			}
			else if(Pokemons[i] == 2)
			{
				printf("%d- Squirtle\n",i);
			}
			else if(Pokemons[i] == 3)
			{
				printf("%d- Bulbasaur\n",i);
			}
			else if(Pokemons[i] == 4)
			{
				printf("%d- Pidgeotto\n",i);
			}
			else if(Pokemons[i] == 5)
			{
				printf("%d- Ratata\n",i);
			}
			else if(Pokemons[i] == 6)
			{
				printf("%d- Mug\n",i);
			}
			else if(Pokemons[i] == 7)
			{
				printf("%d- Caterpie\n",i);
			}
			else if(Pokemons[i] == 8)
			{
				printf("%d-  Zubat\n",i);
			}
			else if(Pokemons[i] == 9)
			{
				printf("%d- Krabby\n",i);
			}
		}
	}
}
void catch_a_pokemon(char  Pokemon_name[][12], pokemon Pokemons[],pokemon *my_Pokemons)
{
	int selected,i,j;
	int pokemon_count=0;
	printf("Please enter the pokemon number you want to select. \n");
	scanf("%d",&selected);
	*my_Pokemons = selected;
}
void release_a_pokemon(char  Pokemon_name[][12], pokemon Pokemons[], pokemon *my_Pokemons)
{
	*my_Pokemons = *my_Pokemons +1;
}
