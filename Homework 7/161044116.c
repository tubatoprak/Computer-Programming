#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum  {
	noone,
	cap,
	car
}player_type;

typedef enum  {
	start,
	property,
	tax,
	punish
}block_type;

 struct player {

	 player_type type;
	int current_block_id;
	int owned_block_ids[11];
	int account;
	int turn_to_wait;
	char * name;		
};

 struct block{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	struct player owner;
	 block_type type;
};

void init_the_board(struct block board[20]);
void show_board(struct block board[20], struct player player_one, struct player player_two);
void show_properties(struct block board[20]);
void buy_property(struct block* current_block, struct player* current_player);
void sell_property(struct block board[20], struct player* current_player);
void gameplay(struct block board[20], struct player player_one, struct player player_two);
void add_id(int blokc_ids[], int id);
void buy_house(struct block* current_block, struct player* current_player);
void sell_house(struct block* current_block,struct player* current_player);
void show_my_properties(struct block board[20], struct player* current_player);
void sub_id(int block_ids[], int id);

int main (){

	srand(time(NULL));
	struct block board[20];
	struct player player_one;
	struct player player_two;
	
	player_one.type=car;
	player_two.type=cap;
	player_one.current_block_id=0;
	player_two.current_block_id=0;
	player_one.account=100000;
	player_two.account=100000;
	player_one.turn_to_wait=0;
	player_two.turn_to_wait=0;
	player_one.name="car";
	player_two.name="cap";

	for (int i = 0; i < 11; ++i)
	{
		player_one.owned_block_ids[i]=-1;
		player_two.owned_block_ids[i]=-1;

	}

	init_the_board(board);
	
	show_board(board,player_one,player_two);
	gameplay(board,player_one,player_two);

	
	return 0;
}
void show_board(struct block board[20], struct player player_one, struct player player_two){
 int i=0,j=0,k=0;	  /*board u üç parçaya böldüm.ilk parça için k=0 oldugu yer.ortası boşluk olan 
 											parça için k=1 ve son parça içi k=2.*/
	printf("\n");
	if(k==0){
	 
		for ( i = 0; i <= 132; ++i)	         /*kendi terminalim göre ölçeklendirdim.*/
		{
			printf("-");
		}
		printf("\n|");
		 
		for (j = 0; j < 6; ++j)
		{
			printf("   %-15s   |",board[j].name);
		}
		printf("\n|");
		 
		for (j = 0; j < 6; ++j)
		{	
		 	if(board[j].price==0)
		 		printf("                     |");
		 	else 
		 		printf("   %-15d   |",board[j].price);
		}

		printf("\n|");
		 
		for ( j = 0; j < 6; ++j)		
		{
		 		if(player_one.current_block_id==j && player_two.current_block_id==j) /*car ve cap in aynı yerde olması durumu*/
		 			printf("   Car-Cap           |");
		 		
		 		else if(player_one.current_block_id==j)
		 		{
			 		if(player_one.type==car)		    /*car ve cap farklı seçilmesi durumunda kodun çalışması için iki ihtimali göz önüne aldım.*/
			 			printf("   Car               |");
			 		else if (player_one.type==cap)
			 			printf("   Cap               |");
		 		}

		 		else if(player_two.current_block_id==j)
		 		{		
		 		
			 		if(player_two.type==car)
			 			printf("   Car               |");
			 		else if (player_two.type==cap)
			 			printf("   Cap               |");
		 		}
		 		else
		 			printf("                     |");  
		}
	}

	printf("\n");
	
	for (i = 0; i <= 132; ++i)
	{
		 	printf("-");
	}
	k++;
	printf("\n|");
	
	int c=6,d=19;
	if(k==1)
	{
		for(c=6;c<=9;c++,d--)
		{
		 	printf("   %-15s   |",board[d].name);
		 	printf("                      "); 
		 	printf("                      "); 
		 	printf("                      "); 
		 	printf("                     |");
		 	printf("   %-15s   |",board[c].name);
		 	printf("\n|");
		 	printf("   %-15d   |",board[d].price);
		 	printf("                      "); 
		 	printf("                      "); 
		 	printf("                      "); 
		 	printf("                     |");
		 	printf("   %-15d   |",board[c].price);
		 	printf("\n|");
		 	if(player_one.current_block_id==d && player_two.current_block_id==d)
		 	{
		 		printf("   Car-Cap           |");
		 	}
		 	else if(player_one.current_block_id==d)
		 	{
			 	if(player_one.type==car)				
			 		printf("   Car               |");
			 	else if (player_one.type==cap)
			 		printf("   Cap               |");
		 	}
			else if(player_two.current_block_id==d)
			{			
				if(player_two.type==car)
					printf("   Car               |");
				else if (player_two.type==cap)
					printf("   Cap               |");
			}
			else
				printf("                     |");
			 		
			printf("                      ");
			printf("                      ");
			printf("                      ");
			printf("                     |");
			if(player_one.current_block_id==c && player_two.current_block_id==c)
			{
				printf("   Car-Cap           |");
			}	
			else if(player_one.current_block_id==c)
			{
				if(player_one.type==car)				
			 		printf("   Car               |");
			 	else if (player_one.type==cap)
			 		printf("   Cap               |");
			}
			else if(player_two.current_block_id==c)
			{		
			 	if(player_two.type==car)
			 		printf("   Car               |");
			 	else if (player_two.type==cap)
			 		printf("   Cap               |");
			}
			else
			 	printf("                     |");
			
			printf("\n|");	
			for ( i = 0; i <=21; ++i)
			{
				printf("-");
			}
			if (c==9)
			{
			 	for ( i = 0; i <=86; ++i)
			 	{
			 	printf("-");
			 	}
			}
			else 
				for ( i = 0; i <=86; ++i)
				{
					printf(" ");
				}
				for (i = 0; i <=22; ++i)
				{
				 	printf("-");
				}
			 		printf("\n|");
				}
	}
	k++;
	if(k==2)
	{
		for ( j = 15; j >9; j--)
		{
		 	printf("   %-15s   |",board[j].name);
		}
		printf("\n|");		 
		for (j = 15; j > 9; --j)
		{	
			if(board[j].price==0){
				printf("                     |");	
			}
			else 
				printf("   %-15d   |",board[j].price);
		}
		printf("\n|");
		for ( j = 15; j > 9; --j)		
		{
				 
			if(player_one.current_block_id==j && player_two.current_block_id==j)
				printf("   Car-Cap           |");
			else if(player_one.current_block_id==j)
			{
				if(player_one.type==car)				
					printf("   Car               |");
				else if (player_one.type==cap)
					printf("   Cap               |");
			}
			else if(player_two.current_block_id==j)
			{		
				if(player_two.type==car)
					printf("   Car               |");
				else if (player_two.type==cap)
					printf("   Cap               |");
			}
			else
				printf("                     |");  
		}
		printf("\n");		
		for ( i = 0; i <= 132; ++i)
		{
			printf("-");
		}
	}
	printf("\n");
}
void show_properties(struct block board[20]){
	int choice,menu=0;
	while(menu!=1){
		printf("1-   Esenyurt\n");
		printf("4-   Arnavutköy\n");
		printf("6-   Catalca \n");
		printf("7-   Beykoz\n");
		printf("9-   Maltepe\n");
		printf("11-  Sisli\n");
		printf("13-  Atasehir\n");
		printf("14-  Sarıyer\n");
		printf("16-  Kadıkoy\n");
		printf("17-  Besiktas\n");
		printf("19-  Bebek\n");
		printf("0-   exit\n");
		printf("Please select a property to see details: ");
		scanf("%d",&choice);
		printf("-----------------------------------\n");
			
		switch(choice) {
			
			case 1:
				printf("|\t     %-18s   |\n",board[1].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[1].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[1].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[1].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[1].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[1].house_price);
				printf("-----------------------------------\n");
				break;
			case 4:
				printf("|\t     %-18s   |\n",board[4].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[4].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[4].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[4].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[4].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[4].house_price);
				printf("-----------------------------------\n");
				break;

			case 6:
				printf("|\t     %-18s   |\n",board[6].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[6].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[6].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[6].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[6].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[6].house_price);
				printf("-----------------------------------\n");
				break;
			case 7:
				printf("|\t     %-18s   |\n",board[7].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[7].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[7].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[7].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[7].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[7].house_price);
				printf("-----------------------------------\n");
				break;
			case 9:
				printf("|\t     %-18s   |\n",board[9].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[9].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[9].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[9].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[9].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[9].house_price);
				printf("-----------------------------------\n");
				break;
			case 11:
				printf("|\t     %-18s   |\n",board[11].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[11].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[11].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[11].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[11].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Pric3: %-12d |\n",board[11].house_price);
				printf("-----------------------------------\n");
				break;
			case 13:
				printf("|\t     %-18s   |\n",board[13].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[13].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[13].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[13].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[13].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[13].house_price);
				printf("-----------------------------------\n");
				break;
			case 14:
				printf("|\t     %-18s   |\n",board[14].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[14].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[14].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[14].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[14].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[14].house_price);
				printf("-----------------------------------\n");
				break;
			case 16:
				printf("|\t     %-18s   |\n",board[16].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[16].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[16].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[16].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[16].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[16].house_price);
				printf("-----------------------------------\n");
				break;
			case 17:
				printf("|\t     %-18s   |\n",board[17].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[17].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[17].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[17].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[17].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[17].house_price);
				printf("-----------------------------------\n");
				break;
			case 19:
				printf("|\t     %-18s   |\n",board[19].name);
				printf("-----------------------------------\n");
				printf("|\tRent:         %-12d|\n",board[19].rent);
				printf("|\tRent 1 H:     %-12d|\n",board[19].rent_1);
				printf("|\tRent 2 H:     %-12d|\n",board[19].rent_2);
				printf("|\tRent 3 H:     %-12d|\n",board[19].rent_3);
				printf("-----------------------------------\n");
				printf("|\tHouse Price: %-12d |\n",board[19].house_price);
				printf("-----------------------------------\n");
				break;
			case 0:
					menu=1;
					break;
			default:
					printf("\nINVALID CHOICE \n");
		}
	}
}
void init_the_board(struct block board[20]) { 
	int i =0;
	for(i=0; i<20; i++) {
		board[i].block_id = i;
	}
	board[0].name = "Start";
	board[1].name = "Esenyurt";
	board[2].name = "Car Park";
	board[3].name = "Tuzla";		
	board[4].name = "Arnavutkoy";		
	board[5].name = "Wait 2 Turn";	
	board[6].name = "Catalca";		
	board[7].name = "Beykoz";			
	board[8].name = "Car Fix";		
	board[9].name = "Maltepe";		
	board[10].name = "Bills";			
	board[11].name = "Sisli";			
	board[12].name = "Oil";			
	board[13].name = "Atasehir";		
	board[14].name = "Sariyer";		
	board[15].name = "Wait 1 Turn";	
	board[16].name = "Kadikoy";		
	board[17].name = "Besiktas";		
	board[18].name = "Vocation";		
	board[19].name = "Bebek";			
	board[0].price = 0 ;
	board[1].price = 16000 ;
	board[2].price = 1500 ;	
	board[3].price = 16500 ;	
	board[4].price = 17000 ;	
	board[5].price = 0 ;
	board[6].price = 20000 ;
	board[7].price = 23000 ;
	board[8].price = 1750 ;
	board[9].price = 30000 ;
	board[10].price = 2000 ;
	board[11].price = 33000 ; 
	board[12].price = 2250 ;
	board[13].price = 35000 ;
	board[14].price = 40000 ;
	board[15].price = 0;
	board[16].price = 43000 ;
	board[17].price = 60000 ;
	board[18].price = 5000 ;
	board[19].price = 70000 ;

	board[0].rent = 0 ;
	board[1].rent = 800 ;
	board[2].rent = 1500 ;	
	board[3].rent = 850 ;	
	board[4].rent = 875 ;	
	board[5].rent = 2 ;
	board[6].rent = 1000 ;
	board[7].rent = 1100 ;
	board[8].rent = 1750 ;
	board[9].rent = 1350 ;
	board[10].rent = 2000 ;
	board[11].rent = 1500 ; 
	board[12].rent = 2250 ;
	board[13].rent = 1600 ;
	board[14].rent = 1750 ;
	board[15].rent = 1;
	board[16].rent = 1900 ;
	board[17].rent = 2500 ;
	board[18].rent = 5000 ;
	board[19].rent = 3500 ;

	board[0].rent_1 = 0 ;
	board[1].rent_1 = 4000 ;
	board[2].rent_1 = 0 ;	
	board[3].rent_1 = 4250 ;	
	board[4].rent_1 = 4500 ;	
	board[5].rent_1 = 0 ;
	board[6].rent_1 = 5000 ;
	board[7].rent_1 = 5500 ;
	board[8].rent_1 = 0 ;
	board[9].rent_1 = 7000 ;
	board[10].rent_1 = 0 ;
	board[11].rent_1 = 8000 ; 
	board[12].rent_1 = 0 ;
	board[13].rent_1 = 8500 ;
	board[14].rent_1 = 9500 ;
	board[15].rent_1 = 0;
	board[16].rent_1 = 11000 ;
	board[17].rent_1 = 15000 ;
	board[18].rent_1 = 0 ;
	board[19].rent_1 = 20000 ;

	board[0].rent_2 = 0 ;
	board[1].rent_2 = 9000 ;
	board[2].rent_2 = 0 ;	
	board[3].rent_2 = 9500 ;	
	board[4].rent_2 = 10000 ;	
	board[5].rent_2 = 0 ;
	board[6].rent_2 = 12000 ;
	board[7].rent_2 = 12500 ;
	board[8].rent_2 = 0 ;
	board[9].rent_2 = 15000 ;
	board[10].rent_2 = 0 ;
	board[11].rent_2 = 16000 ; 
	board[12].rent_2 = 0 ;
	board[13].rent_2 = 17000 ;
	board[14].rent_2 = 19000 ;
	board[15].rent_2 = 0;
	board[16].rent_2 = 21500 ;
	board[17].rent_2 = 28000 ;
	board[18].rent_2 = 0 ;
	board[19].rent_2 = 35500 ;

	board[0].rent_3 = 0 ;
	board[1].rent_3 = 25000 ;
	board[2].rent_3 = 0 ;	
	board[3].rent_3 = 26000 ;	
	board[4].rent_3 = 28000 ;	
	board[5].rent_3 = 0 ;
	board[6].rent_3 = 30000 ;
	board[7].rent_3 = 33000 ;
	board[8].rent_3 = 0 ;
	board[9].rent_3 = 40000 ;
	board[10].rent_3 = 0 ;
	board[11].rent_3 = 42000 ; 
	board[12].rent_3 = 0 ;
	board[13].rent_3 = 45000 ;
	board[14].rent_3 = 48000 ;
	board[15].rent_3 = 0;
	board[16].rent_3 = 55000 ;
	board[17].rent_3 = 60000 ;
	board[18].rent_3 = 0 ;
	board[19].rent_3 = 65000 ;

	board[0].house_price = 0 ;
	board[1].house_price = 10000 ;
	board[2].house_price = 0 ;	
	board[3].house_price = 12000 ;	
	board[4].house_price = 12000 ;	
	board[5].house_price = 0 ;
	board[6].house_price = 13000 ;
	board[7].house_price = 13000 ;
	board[8].house_price = 0 ;
	board[9].house_price = 15000 ;
	board[10].house_price = 0 ;
	board[11].house_price = 16000 ; 
	board[12].house_price = 0 ;
	board[13].house_price = 17000 ;
	board[14].house_price = 19000 ;
	board[15].house_price = 0;
	board[16].house_price = 23000 ;
	board[17].house_price = 30000 ;
	board[18].house_price = 0 ;
	board[19].house_price = 35000 ;


	for(i=0; i<20; i++){
		board[i].house_count = 0;
	}

	board[0].owner.type =  noone ;
	board[1].owner.type =  noone ;
	board[2].owner.type =  noone ;	
	board[3].owner.type =  noone ;	
	board[4].owner.type =  noone ;	
	board[5].owner.type =  noone ;
	board[6].owner.type =  noone ;
	board[7].owner.type =  noone ;
	board[8].owner.type =  noone ;
	board[9].owner.type =  noone ;
	board[10].owner.type = noone ;
	board[11].owner.type = noone ; 
	board[12].owner.type = noone ;
	board[13].owner.type = noone ;
	board[14].owner.type = noone ;
	board[15].owner.type = noone ;
	board[16].owner.type = noone ;
	board[17].owner.type = noone ;
	board[18].owner.type = noone ;
	board[19].owner.type = noone ;

	board[0].type =  start ;
	board[1].type =  property ;
	board[2].type =  tax ;	
	board[3].type =  property ;	
	board[4].type =  property ;	
	board[5].type =  punish ;
	board[6].type =  property ;
	board[7].type =  property ;
	board[8].type =  tax ;
	board[9].type =  property ;
	board[10].type = tax ;
	board[11].type = property ; 
	board[12].type = tax ;
	board[13].type = property ;
	board[14].type = property ;
	board[15].type = punish ;
	board[16].type = property ;
	board[17].type = property ;
	board[18].type = tax ;
	board[19].type = property ;
}
void buy_property(struct block* current_block, struct player* current_player){
	if(current_block->type != property)  /*öncelikle, bloğun türünü kontrol ediyorum. */
	 return;

	if(current_block->owner.type == noone)	/*blogun farklı biri tarafından alınıp-alınmadığını kontrol ediyorum. */
		if(current_block->price <= current_player->account)	/*blok sahipsizse para durumuna bakıyorum.*/
		{
			current_block->owner.type = current_player->type;	/*oyuncunun parası yetiyorsa blogun türünü değiştiriyorum.*/
			add_id(current_player->owned_block_ids, current_block->block_id); /*blogun kaydını yapan extra fonks. gönderiyorum*/
			current_player->account -= current_block->price;	/*hesaptan parayı azaltıyorum*/
			printf("\nYou bought this property.\n");
		}
		else
		{
			printf("You don't have enough money.\n");
		}
	buy_house(current_block, current_player); /*eğer ki evi daha önce almışsa ve yeniden üzerine geldiyse ev inşası için soru soruyoruz.*/
}	
void sell_property(struct block board[20], struct player* current_player)
{
	int id = 0,prop;
	char choice = 'N';
	
	do
	{
		
		printf("Please select which property do you want to sell.(Exit -1): ");
		scanf("%d",&id);
		if(id < 20 && board[id].owner.type == current_player->type)/*oyuncunun satmak istediği evin ona ait oldugunun kontrolu*/
		{
			if(board[id].house_count > 0)	/*mülkün üzerinde ev varsa öncelikle onları satmalı.bu durum için kontrolu*/
			{
				printf("Do you want to sell house?(Y/N): ");
				scanf("%c", &choice);
				if(choice == 'Y')
					sell_house(board, current_player);		/*ev satma extra fonks.*/
				else {
					board[id].owner.type==noone; /*mülk ve evi satmak istiyorsa, mülkün türünü değiştirip, kullanıcıya
																		 fiyatın yarısını iade ediyor. */
					current_player->account+=(board[id].price/2);
					sub_id(current_player->owned_block_ids,id);	 /*blogun id sini playerden silmek için extra. fnk*/
				}
			}
			else  {					
				board[id].owner.type==noone;
					current_player->account+=(board[id].price/2);
					sub_id(current_player->owned_block_ids,id);
			}
		}
	}
	while(id != -1);	
}
void add_id(int block_ids[], int id)
{
	int i;
	for(i = 0; i < 11; ++i)
	{
		if(block_ids[i]==-1){
			block_ids[i] = id;
		}
		i=11;
	}
}
void sub_id(int block_ids[], int id){
	int i;
	for(i = 0; i < 11; ++i)
		if(block_ids[i] == id)
			block_ids[i] = -1;
}

void buy_house(struct block* current_block, struct player* current_player)
{
	int choice = 0;
	if(current_block->owner.type == current_player->type)
	{
		printf("Current house count is %d in this property.\n", current_block->house_count);
		if(current_block->house_count < 3)
		{
			printf("Price is %d. %s", current_block->house_price
				, "How many house do you want to buy? ");
			scanf("%d", &choice);
			choice %= 4;
			if(current_block->house_count+choice < 4)
			{
				if(current_block->price*choice <= current_player->account)
				{
						current_player->account -= current_block->house_price*choice;
						current_block->house_count += choice;
						printf("your house-s were made.\n");
				}
				else
				{
					printf("You don't have enough money.\n");
				}
			}
		}
	}
	else
	{
		printf("This place is not yours.\n");
	}
}

void sell_house(struct block* current_block,struct player* current_player)
{	int choice;
	if(current_block->owner.type == current_player->type)
	{
		printf("Current house count is %d in this property.\n", current_block->house_count);
		if(current_block->house_count > 0)
		{
			printf("Price is %d. %s", current_block->house_price
				, "How many house do you want to sell? ");
			scanf("%d", &choice);
			choice %= 4;
			if(current_block->house_count - choice >= 0)
			{
				current_player->account += current_block->house_price*choice*0.5;
				current_block->house_count -= choice;
			}
		}
	}
	else
	{
		printf("This place is not yours.\n");
	}
}
void show_my_properties(struct block board[20], struct player* current_player)
{	int i;
	printf("--Properties of %s have \n", current_player->name);

	for(i = 0; i < 11; ++i)
	{
		if(current_player->owned_block_ids[i]!= -1 )
		{
			int id = *(current_player->owned_block_ids+i);
			printf("Property id: %d property Name: %s House: %d", board[id].block_id, board[id].name, board[id].house_count);
			/*if(board[i].house_count > 0)
				printf(" House: %d Price: %d", board[id].house_count, board[id].house_price);
			printf("\n");*/
		}
	}
}
void gameplay(struct block board[20], struct player player_one, struct player player_two)
{
	int choice,dice=0,temp=player_one.type;
	int ch=0;
	while(player_one.account!=0 && player_two.account!=0 ){	/*Kullanıcıların paralarını bitmesi durumuna kadar döngü.*/
	/*temp adındaki değişken oyunun kimde oldugunu söylüyor.roll the dice  show_propteries  deeds  dışında kullanıcı 
	sırası  değişiyor.case'lerde temp değitirip farklı if'lere girmesini sağlayarak kullanıcı değişikliği
	yaptım. 
	oyunu player_one dan başlatıyorum.zar attıktan sonra işlem yapması için diğer kullanıcıya sırayı
	vermiyorum.*/	
		if(temp==player_one.type)	
		{	printf("\n-----PLAYER TO PLAY NOW: CAR------- \n");
			printf("\n\n1-Roll The dice\n");
			printf("2-Show my account\n");
			printf("3-Show my Properties\n");
			printf("4-Show Properties deeds\n");
			printf("5-Buy Property\n");
			printf("6-Buy_House\n");
			printf("7-Sell Property\n");
			printf("Please select an option to continue: ");
			scanf("%d",&choice);
			
			switch(choice)
			{
				case 1: 
					dice=1+rand()%6;
					printf("discarded dice %d",dice);
					player_one.current_block_id+=dice;
					show_board(board,player_one,player_two);
						
					if(board[player_one.current_block_id].type==property)
					{
						printf("Would you like to buy this property?(Yes=1/No=2)");
						scanf("%d",&ch);
						if(ch==1)
						{
							buy_property(&board[player_one.current_block_id],&player_one);
							temp=player_two.type;
						}
					else 
						temp=player_two.type;
					}
					break;
				case 2:
					printf("\nPlayer_one is account: %d ",player_one.account);
					temp=player_two.type;
					break;
				case 3:
					show_my_properties(board,&player_one);
					temp=player_two.type;
					break;
				case 4:
					show_properties(board);
					break;
				case 5:
					buy_property(&board[player_one.current_block_id],&player_one);
					temp=player_two.type;
					break;
				case 6:
					buy_house(&board[player_one.current_block_id],&player_one);
					temp=player_two.type;
					break;
				case 7:
					sell_property(&board[player_one.current_block_id],&player_one);
					temp=player_two.type;
					break;
				default:
					printf("invalid choice\n");
			}
		}
		else if(temp==player_two.type)
		{	printf("\n-----PLAYER TO PLAY NOW: CAP------- \n");
			printf("\n\n1-Roll The dice\n");
			printf("2-Show my account\n");
			printf("3-Show my Properties\n");
			printf("4-Show Properties deeds\n");
			printf("5-Buy Property\n");
			printf("6-Buy_House\n");
			printf("7-Sell Property\n");
			printf("Please select an option to continue: ");
			scanf("%d",&choice);
			
			switch(choice)
			{
				case 1: 
					dice=1+rand()%6;
					printf("discarded dice %d",dice);
					player_two.current_block_id+=dice;
					show_board(board,player_one,player_two);

					if(board[player_two.current_block_id].type==property)
					{
						printf("Would you like to buy this property?(Yes=1/No=2)");
						scanf("%d",&ch);
						if(ch==1)
						{
							buy_property(&board[player_two.current_block_id],&player_two);
							temp=player_one.type;
						}
					}
					
					break;
				case 2:
					printf("\nPlayer_one is account: %d ",player_two.account);
					temp=player_one.type;
					break;
				case 3:
					show_my_properties(board,&player_two);
					temp=player_one.type;
					break;
				case 4:
					show_properties(board);
					break;
				case 5:
					buy_property(&board[player_two.current_block_id],&player_two);
					temp=player_one.type;
					break;
				case 6:
					buy_house(&board[player_two.current_block_id],&player_two);
					temp=player_one.type;
					break;
				case 7:
					sell_property(&board[player_two.current_block_id],&player_two);
					temp=player_one.type;
					break;
				default:
					printf("invalid choice\n");
			}
		}
	}
}
