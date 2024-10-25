#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define PROPERTY_COUNT 13

typedef enum {stack , heap} data_type;
typedef struct node
{
	void * data;
	struct node * next;
}node;

typedef enum  {
	noone,
	cap,
	car
}player_type;


typedef enum {
	start,
	property,
	tax,
	punish,
	fortune
}block_type;

typedef struct{

	 player_type type;
	int current_block_id;
	int owned_block_ids[PROPERTY_COUNT];
	int account;
	int turn_to_wait;
	char * name;		
} player;

typedef struct {
	int card_no;
	char * name;
}fortune_card;

typedef struct{
	int block_id;
	char *name;
	int price;
	int rent;
	int rent_1;
	int rent_2;
	int rent_3;
	int house_price;
	int house_count;
	player owner;
	block_type type;
} block;

void append(node ** head, void * data);
void flush(node ** head, data_type dt);
int size(node * head);
node * board_to_linked(block board[], size_t size);
block * get_block(node * current);
block * get_propery(node * head,int id);
block * get_block_at(node * head, int id);
block * set_block(int id, char * name,int price,int rent,int rent_1,
	int rent_2,int rent_3,int h_price,int h_count,player_type owner,block_type type);
void init_board(node ** head);
void show_board(node * head , player player_one, player player_two);
void show_property_deed(node * head);
int build_house(block * current_block, player * current_player);
int count_properties(player current_player);
void sell_property(node * head, player* current_player);
void buy_property(block* current_block, player* current_player);
void add_to_owned(player* current_player);
void copy_owner(player* old, player* new);
void pay_rent(node * head, player* current_player,player * owner);
void show_player_properties(node * head, player current_player);
void house_dialog(node * head, player* current_player);
int insufficient_fund(node * head, player* current_player,int required_money);
void show_board(node * head , player player_one, player player_two);
void show_property_deed(node * head);
int check_end(player current_player);
void after_dice_menu(node * head, player* current_player, player* other);
void init_owned(player* current_player);
void turn(node * head, player* current_player, player * other);
void play_game(node * head, player* player_one, player* player_two);
void turns(node * head, player* current_player, player * other);

int main()
{
	block board[24];
    srand(time(NULL));
	node * head = NULL;
	node * temp;
	init_board(&head);
	player player_one,player_two;

	player_one.name="Car";
	player_one.type=cap;
	player_one.current_block_id=0;
    player_one.turn_to_wait=0;
	player_one.account=100000;
    init_owned(&player_one);

    player_two.name="Computer";
	player_two.type=car;
	player_two.current_block_id=0;
    player_two.turn_to_wait=0;
	player_two.account=100000;
    init_owned(&player_two);

	for (int i = 0; i < PROPERTY_COUNT; ++i)
	{
		player_one.owned_block_ids[i]=-1;
		player_two.owned_block_ids[i]=-1;
	}
	show_board(head ,player_one,player_two);
	 play_game(head,&player_one,&player_two);
	flush(&head, heap);
	
	return 0;
}
void append(node ** head, void * data)
{
	node * new_node = (node*) malloc(sizeof(node));
	new_node->data = data;
	new_node->next = NULL;

	if(*head == NULL)
		*head = new_node;
	else
	{
		node * current = *head;
		while(current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void flush(node ** head, data_type dt)
{
	node * current = *head;
	node * temp;
	while(current != NULL)
	{
		temp = current;
		current = current->next;
		if(dt == heap)
			free(temp->data);
		free(temp);
	}
	*head = NULL;
}

int size(node * head)
{
	int size = 0;
	while(head != NULL)
	{
		size++;
		head = head->next;
	}
	return size;
}

node * board_to_linked(block board[], size_t size)
{
	size_t i = 0;
	block * b;
	node * head = NULL;
	for(i = 0; i < size; ++i)
	{
		b = &board[i];
		append(&head, b);
	}
	return head;
}

block * get_block(node * current)
{
	return (block*)(current->data);
}
block * get_propery(node * head,int id)
{
	block * block = NULL;
	int i;
	for (i = 0; head != NULL && i < id; ++i)
	{
		block = get_block(head);
		while(head != NULL && block->type != property)
		{
			head = head->next;
			block = get_block(head);
		}
		head = head->next;
	}
	return block;
}

block * get_block_at(node * head, int id)
{
	int i;
	for (i = 0; head != NULL && i < id; ++i)
		head = head->next;
	return get_block(head);
}
block * set_block(int id, char * name,int price,int rent,int rent_1,
	int rent_2,int rent_3,int h_price,int h_count,player_type owner,block_type type)
{
	block * temp = (block *)malloc(sizeof(block));
	temp->block_id = id;
	temp->name = name;
	temp->price = price;
	temp->rent = rent;
	temp->rent_1 = rent_1;
	temp->rent_2 = rent_2;
	temp->rent_3 = rent_3;
	temp->house_price = h_price;
	temp->house_count = h_count;
	temp->owner.type = owner;
	temp->type = type;
	return temp;
}
void init_board(node ** head)
{
	int i = 0;
	append(head, set_block(0, "Start", 0, 0, 0, 0, 0, 0, 0, noone, start));
	append(head, set_block(1, "Esenyurt", 16000, 800, 4000, 9000, 25000, 10000, 0, noone, property));
	append(head, set_block(2, "Car Park",0,0,0,0,0,0, 0, noone, tax));
	append(head, set_block(3, "Fortune Card",0,0,0,0,0,0, 0, noone, fortune));
	append(head, set_block(4, "Tuzla",16500,850,4250,9500,26000,12000, 0, noone, property));
	append(head, set_block(5, "Arnavutkoy",17000,850,4250,9500,26000,12000, 0, noone, property));
	append(head, set_block(6, "Wait 2 Turn",0,2,0,0,0,0,0, noone, punish));
	append(head, set_block(7, "Catalca",20000,1000,5000,12000,30000,13000,0, noone, property));
	append(head, set_block(8, "Beykoz",23000,1100,5500,12500,33000,13000,0, noone, property));
	append(head, set_block(9, "Fortune Card",0,0,0,0,0,0,0, noone, fortune));
	append(head, set_block(10, "Car Fix",0,1750,0,0,0,0,0, noone, tax));
	append(head, set_block(11, "Maltepe",30000,1350,7000,15000,40000,15000,0, noone,property));
	append(head, set_block(12, "Bills",0,2000,0,0,0,0,0, noone,tax));
	append(head, set_block(13, "Sisli",33000,1500,8000,16000,42000,16000,0, noone,property));
	append(head, set_block(14, "Oil",0,2250,0,0,0,0,0, noone,tax));
	append(head, set_block(15, "Fortune Card",0,0,0,0,0,0,0, noone, fortune));
	append(head, set_block(16, "Atasehir", 35000,1600,8500,17000,45000,17000,0, noone,property));
	append(head, set_block(17, "Sariyer", 40000,1750,9500,19000,48000,19000,0, noone,property));
	append(head, set_block(18, "Wait 1 Turn",0,1,0,0,0,0,0, noone, punish));
	append(head, set_block(19, "Kadikoy", 43000,1900,1100,215000,55000,23000,0, noone,property));
	append(head, set_block(20, "Besiktas",60000,2500,1500,2800,60000,30000,0, noone,property));
	append(head, set_block(21, "Fortune Card",0,0,0,0,0,0,0, noone, fortune));
	append(head, set_block(22, "Vocation",0,5000,0,0,0,0,0, noone,tax));
	append(head, set_block(23, "Bebek",70000,3500,20000,35500,65000,35000,0, noone,property));
}

int build_house(block * current_block, player * current_player)
{
    int flag=0;
    if (current_player->type==current_block->owner.type)
    {
        if (current_block->house_count<3)
        {
            if (current_block->house_price<=current_player->account)
            {
                flag=1;
                current_player->account-=current_block->house_price;
                current_block->house_count+=1;
            }
            else
                printf("You don't have enough money to build house!\n");
        }
        else
            printf("You can't buy more than 3 houses in a property!\n");
    }
    else
        printf("You don't have permission to build house on this property!\n ");
    return flag;
}

int count_properties(player current_player)
{
    int i,count=0;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        if (current_player.owned_block_ids[i]!=-1)
            count++;
    }
    return count;
}

void sell_property(node * head, player * current_player)
{
    int property_id,flag=0,is_owned=-1,i,index,counter=0;
    block * blok = NULL;
    if (count_properties(*current_player)!=0)
    {
        for (i = 0; i < PROPERTY_COUNT; i++)
        {
            if (current_player->owned_block_ids[i] != -1)
            {
            	blok = get_block_at(head, current_player->owned_block_ids[i]);
                printf("%d - %s\n", blok->block_id, blok->name);
                counter++;
            }

        }
        printf("0 - Back\n");
        printf("Please select to sell the property:\n");

        scanf("%d",&property_id);
        if (property_id!=0)
        {
            for(i=0;i<PROPERTY_COUNT;i++)
            {
                if (current_player->owned_block_ids[i]==property_id)
                {
                    is_owned=1;
                    index=i;
                    break;
                }
            }
            if(is_owned!=-1)
            {
                current_player->owned_block_ids[index]=-1;
                player temp;
                blok = get_block_at(head, property_id);
                blok->owner.type=noone;
                if(blok->house_count==0)current_player->account+=blok->price/2;
                if(blok->house_count==1)
                {
                    current_player->account+=(blok->price+blok->house_price)/2;
                }
                if(blok->house_count==2)
                {
                    current_player->account+=(blok->price+(2*blok->house_price))/2;
                }
                if(blok->house_count==3)
                {
                    current_player->account+=(blok->price+(3*blok->house_price))/2;
                }
            }
        }
    }
    else
    {
        printf("You don't have any property to sell.\n");
    }
}

void buy_property(block* current_block, player* current_player)
{
    if (current_block->price<=current_player->account)
    {
        current_player->account-=current_block->price;
        copy_owner(&current_block->owner,current_player);
        add_to_owned(current_player);

        printf("Congratulations! You have buy %s.\n",current_block->name);
        printf("You left %d$ in your account.\n",current_player->account);

    }
    else
        printf("You don't have enough money to buy this property!\n");
}

void add_to_owned(player* current_player)
{
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        if (current_player->owned_block_ids[i]==-1) {
            current_player->owned_block_ids[i] = current_player->current_block_id;
            printf("Current block id %d\n",current_player->current_block_id);
            break;
        } else
            printf("%d ",current_player->owned_block_ids[i]);
    }
    printf("\n");
}

void copy_owner(player* old, player* new)
{
    old->type=new->type;
    old->account=new->account;
    old->turn_to_wait=new->turn_to_wait;
    old->name=new->name;
    old->current_block_id=new->current_block_id;
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        old->owned_block_ids[i]=new->owned_block_ids[i];
    }
}

void pay_rent(node * head, player* current_player,player * owner)
{
    int rent=0,owned_property_count;
    block * block = get_block_at(head, current_player->current_block_id);
    rent=block->rent;
    if (block->house_count==1) rent=block->rent_1;
    if (block->house_count==2) rent=block->rent_2;
    if (block->house_count==3)rent=block->rent_3;
    if (rent>current_player->account)
    {
        owned_property_count=count_properties(*current_player);
        while(rent>current_player->account && owned_property_count!=0)
        {
            insufficient_fund(head,current_player,rent);
            owned_property_count=count_properties(*current_player);
        }
    }
    if (rent<current_player->account)
    {
        current_player->account-=rent;
        owner->account+=rent;
    } else
        current_player->account=0;
}
void show_player_properties(node * head, player current_player)
{
    int i,counter=0,selection = 1;
    block * block;
    while (selection!=0) {
        printf("----------------------------------------\n");
        for (i = 0; i < PROPERTY_COUNT; i++) {
            if (current_player.owned_block_ids[i] != -1) {
            	block = get_block_at(head, current_player.owned_block_ids[i]);
                printf("%d - %s\n", block->block_id, block->name);
                counter++;
            }

        }
        if (counter == 0)
        {
            printf("You have not owned any property yet.\n");
            printf("----------------------------------------\n");
            selection=0;
        }
        else
        {

            printf("0 - Back \n");
            printf("----------------------------------------\n");
            printf("Please select an property to see details.\n");
            scanf("%d", &selection);

            if (selection!=0) {
            	block = get_block_at(head, selection);
                if (block->owner.type != current_player.type)
                    printf("You made a wrong selection!\n");
                else {
                    printf("\n\n---------------------------------\n");
                    if (strlen(block->name) < 8)
                        printf("|\t\t%s\t\t|\n", block->name);
                    else
                        printf("|\t    %s\t\t|\n", block->name);
                    printf("---------------------------------\n");
                    printf("|\tRent \t\t%d$\t|\n", block->rent);
                    printf("|\tRent 1 H \t%d$\t|\n", block->rent_1);
                    printf("|\tRent 2 H \t%d$\t|\n", block->rent_2);
                    printf("|\tRent 3 H \t%d$\t|\n", block->rent_3);
                    printf("---------------------------------\n");
                    printf("|\tHouse Price \t%d$\t|\n", block->house_price);
                    printf("|\tHouse count \t%d\t|\n", block->house_count);
                    printf("---------------------------------\n\n\n");
                }
            }
        }
    }
}

void house_dialog(node * head, player* current_player)
{
    int house_flag=1,selection,insuf_flag=1,build_flag=1;
    block * block;
    while (house_flag && build_flag) {
    	block = get_block_at(head, current_player->current_block_id);
        printf("Do you want to build house on %s ?\n",
               block->name);
        printf("1- Yes\n");
        printf("2- No\n");
        scanf("%d", &selection);
        if (selection == 1) {

            if (current_player->account < block->house_price) {
                while (count_properties(*current_player)!=0 && current_player->account < block->house_price && insuf_flag==1)
                    insuf_flag=insufficient_fund(head,current_player,block->house_price);
            }
            if (current_player->account >= block->house_price)
                build_flag=build_house(block, current_player);
            else
                house_flag=0;


        } else
            house_flag=0;
    }
}

int insufficient_fund(node * head, player* current_player,int required_money)
{
    int selection = 0,flag=1;
    while (selection!=4 && current_player->account<required_money && count_properties(*current_player)!=0)
    {
        printf("You don't have enough money to continue your transaction.You need %d$ more. Please select an option to continue: \n",required_money-current_player->account);
        printf("1- Sell Property\n");
        printf("2- Show my Properties\n");
        printf("3- Show my Account\n");
        printf("0- Back\n");
        scanf("%d",&selection);
        switch (selection)
        {
            case 1:
                sell_property(head,current_player);
                break;
            case 2:
                show_player_properties(head,*current_player);
                break;
            case 3:
                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
                break;
            case 0:
                flag=0;
                break;
            default:
                printf("You made a wrong selection!\n");
                break;

        }
    }
    return flag;
}

void after_dice_menu(node * head, player* current_player, player* other)
{
    int selection,insuf_flag=1;
    block * block = get_block_at(head, current_player->current_block_id);
    switch (block->type)
    {
        case property:
            printf("%s has arrived %s \n",current_player->name,block->name);
            if (block->owner.type==noone)
            {
                printf("Do you want to buy %s ?\n",block->name);
                printf("1- Yes\n");
                printf("2- No\n");
                scanf("%d",&selection);
                if (selection==1)
                {

                    if (current_player->account< block->price)
                    {
                        while (count_properties(*current_player)!=0 && current_player->account<block-> price && insuf_flag==1 )
                        {
                            insuf_flag=insufficient_fund(head,current_player,block->price);
                        }
                    }
                    buy_property(block,current_player);
                    if (current_player->type==block->owner.type)
                    {
                        house_dialog(head,current_player);
                    }

                }

            } else
            {
                pay_rent(head,current_player,other);
            }
            break;
        case tax:
            printf("%s has arrived tax block(%s)\n",current_player->name,block->name);
            while (count_properties(*current_player)!=0 && current_player->account < block->price) {
                insuf_flag = insufficient_fund(head, current_player,
                                               block->price);
                if (insuf_flag == 0 && current_player->account < block->price)
                    printf("You must pay your tax!\n");
            }
            if (current_player->account > block->price)
                current_player->account=current_player->account-block->price;
            else
            {
                current_player->account=0;
            }
            break;
        case punish:
            printf("%s has punished for %d turn. \n",current_player->name,block->price);
            current_player->turn_to_wait+=block->price;
            break;
    }
}

void show_board(node * head , player player_one, player player_two){
	node * temp;
	temp = head;
	int i = 0, j=0,space_flag=0;
	block * blok, * bloks;
	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
	/*top*/
	printf("|");
	for (j = 0; j < 7; ++j)
	{	
		printf("   %-12s   |",get_block(temp)->name);
		temp = temp->next;
	}
	temp = head;
	printf("\n|");
	for (j = 0; j < 7; ++j)
	{	
		blok = get_block(temp);
		if(blok->price!=0)
			printf("   %-12d   |",blok->price);
		else
			printf("                  |");
		temp = temp->next;
		}
	printf("\n|");
	for (j = 0; j < 7; ++j)
	{
		if(player_one.current_block_id==j && player_two.current_block_id==j) 
		 	printf("   Car-Computer   |");
		else if(player_one.current_block_id==j)
		 	printf("   Car            |");
		else if(player_two.current_block_id==j)
			printf("   computer       |");
		else
		 	printf("                  |");
	}
	printf("\n");
	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("|");
	/*middle*/
	temp = head;
	node * end;
	end=head;
	
	int a=7;
	for (int j=23; j>18 ;--j)
	{
		if(j==23)
		{
			for (i = 0; i < 23; ++i)	
				temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);
		}

		else if(j==22)
		{
			printf("|");
			temp = head;
			for (i = 0; i < 22; ++i)	
				temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);
		}
		else if(j==21)
		{
			printf("|");
			temp = head;
			for (i = 0; i < 21; ++i)	
				temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);
		}
		else if(j==20)
		{
			printf("|");
			temp = head;
			for (i = 0; i < 20; ++i)	
				temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);
		}
		else if  (j==19)
		{
			printf("|");
			temp = head;
			for (i = 0; i < 19; ++i)	
				temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);
		}

		for (i = 0; i < 4; ++i)
			printf("                   ");
		printf("                  |");
		end=head;
		for (i = 0; i < a ; ++i)
			end=end->next;
		bloks = get_block(end);
		printf("   %-12s   |",bloks->name);
		
		end=end->next;
		printf("\n|");
		
		blok = get_block(temp);
		printf("   %-12d   |",blok->price);
		printf("                   ");
		printf("                   ");
		printf("                   ");
		printf("                   ");
		printf("                  |");
		printf("   %-12d   |",bloks->price);
		printf("\n|");
		if(player_one.current_block_id==j && player_two.current_block_id==j) 
		 	printf("   Car-Computer   |");
		else if(player_one.current_block_id==j)
		 	printf("   Car            |");
		else if(player_two.current_block_id==j)
			printf("   computer       |");
		else
		 	printf("                  |");

		printf("                   ");
		printf("                   ");
		printf("                   ");
		printf("                   ");
		printf("                  |");
		if(player_one.current_block_id==a && player_two.current_block_id==a) 
		 	printf("   Car-Computer   |");
		else if(player_one.current_block_id==a)
		 	printf("   Car            |");
		else if(player_two.current_block_id==a)
			printf("   Computer       |");
		else
		 	printf("                  |");
		 printf("\n");
		 a+=1;
		 if (j==19)
		 	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");
		 else
		printf("--------------------                                                                                              --------------------\n");

	}
	temp = head;
	/*end*/
	
	printf("|");
	for (j=18; j>11 ;--j)
	{
			temp = head;
			for (int i = 0; i < j; ++i)	
			temp = temp->next;
			blok = get_block(temp);
			printf("   %-12s   |",blok->name);	
	}
	printf("\n|");
	
	for (j = 18 ; j>11 ; --j)
	{	
		temp = head;
		for (i = 0; i < j; ++i)	
			temp = temp->next;
		blok = get_block(temp);
		if(blok->price!=0)
			printf("   %-12d   |",blok->price);
		else
			printf("                  |");
	}
	printf("\n|");
	for (j = 18; j > 11; --j)
	{
		if(player_one.current_block_id==j && player_two.current_block_id==j) 
		 	printf("   Car-Computer   |");
		else if(player_one.current_block_id==j)
		 	printf("   Car            |");
		else if(player_two.current_block_id==j)
			printf("   computer       |");
		else
		 	printf("                  |");
	}
	printf("\n");
	printf("--------------------------------------------------------------------------------------------------------------------------------------\n");	
}
void show_property_deed(node * head)
{
	node *temp;
	block * blok;
	int exit_flag=0,selection,tempss=1;
    while (exit_flag==0)
    {	
    	temp=head;
    	tempss = 1;
        printf("Please select a property to see details:\n");
        while(temp != NULL)
		{	
			blok = get_block(temp);
			if(blok->type==property)
			{
				printf("%d- %s \n",tempss, blok->name);
				tempss++;
			}
			temp = temp->next;	
		}
        printf("0 -\tExit\n");
        scanf("%d",&selection);
        if (selection==0)
            exit_flag=1;
        else
        {
        	temp = head;
        	blok = get_propery(head, selection);
			printf("\n");
			printf("-----------------------------------\n");
			printf("|\t     %-18s   |\n",blok->name);
			printf("-----------------------------------\n");
			printf("|\tRent:         %-12d|\n",blok->rent);
			printf("|\tRent 1 H:     %-12d|\n",blok->rent_1);
			printf("|\tRent 2 H:     %-12d|\n",blok->rent_2);
			printf("|\tRent 3 H:     %-12d|\n",blok->rent_3);
			printf("-----------------------------------\n");
			printf("|\tHouse Price: %-12d |\n",blok->house_price);
			printf("-----------------------------------\n");
		}
    }
}
int roll_dice()
{

    int i=rand()%6+1;
    return i;
}
int check_end(player current_player)
{
    int owned_property_count=count_properties(current_player);
    if (current_player.account<=0 && owned_property_count==0)return 1;
    else return 0;
}

void init_owned(player* current_player)
{
    int i;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        current_player->owned_block_ids[i]=-1;
    }

}
void play_game(node * head, player* player_one, player* player_two)
{
    int is_end=0;
    printf("Welcom to Monopoly! %s will roll the dice first.\n",player_one->name);
    while(is_end!=1)
    {
        printf("%s :%d$ , %s:%d$\n",player_one->name,player_one->account,player_two->name,player_two->account);
        turn(head,player_one,player_two);
        show_board(head,*player_one,*player_two);
        is_end=check_end(*player_one);
        if (is_end==0)
        {
            printf("%s :%d$ , %s:%d$\n",player_one->name,player_one->account,player_two->name,player_two->account);
            turns(head,player_two,player_one);
            show_board(head,*player_one,*player_two);
            is_end=check_end(*player_two);
            if (is_end==1)
                printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_two->name,player_two->name);
        } else
            printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_one->name,player_one->name);

    }

}
void turn(node * head, player* current_player, player * other)
{
    int flag=1,next_block,dice2;
    block * block = get_block_at(head, current_player->current_block_id);
    	while(flag)
    	{
	        int selection;
	        printf("1 - Roll the dice\n");
	        printf("2 - Show my account\n");
	        printf("3 - Show my properties\n");
	        printf("4 - Show property deeds\n");
	        printf("5 - Buy Property\n");
	        printf("6 - Buy house \n");
	        printf("7 - Sell property\n");
	        printf("Please select an option to continue (%s):\n",current_player->name);
	        scanf("%d",&selection);
	        switch(selection)
	        {	
	            case 1:
	                if (current_player->turn_to_wait==0)
	                {
	                    next_block=(current_player->current_block_id + roll_dice());
	                    if (next_block>=24)current_player->account+=10000;	                    
	                    current_player->current_block_id = next_block % 20;	                    
	                    after_dice_menu(head,current_player,other);
	                    flag = 0;
	                } else
	                {
	                    printf("You need to wait %d turn to continue.\n",current_player->turn_to_wait);
	                    current_player->turn_to_wait-=1;
	                    flag=1;
	                }
	                break;
	            case 2:
	                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
	                break;
	            case 3:
	                show_player_properties(head,*current_player);
	                break;
	            case 4:
	                show_property_deed(head);
	                break;
	            case 5:
	            	
	                if (block->type==property &&block->owner.type==-1)
	                buy_property(block,current_player);
	                else
	                {

	                    printf("You don't have permission to buy this block!\n");
	                }

	                break;
	            case 6:
	                if (current_player->type==block->owner.type) {
	                    house_dialog(head,current_player);
	                }else
	                {
	                    printf("You don't have permission to build house on this block!\n");
	                }
	                break;
	            case 7:
	                sell_property(head,current_player);
	                break;
	            default:
	                printf("Wrong selection!\n");
	        }
	    }
}
void turns(node * head, player* current_player, player * other)
{
    
    int flag=1,next_block,dice2,insuf_flag;;
    block * block = get_block_at(head, current_player->current_block_id);
	while(flag==1)
	{
		
		if (current_player->turn_to_wait==0)
		{

			int dice=roll_dice();
			printf("Computer rolled the dice: %d \n",dice);
	        next_block=(current_player->current_block_id + dice );
	        
	        if (next_block>=24)current_player->account+=10000;	                    
            current_player->current_block_id = next_block % 20;	                    
                        
            switch (block->type)
    		{
            	case property:
	            	if (block->owner.type==noone)
	            	{
		        		if(block->price <= 330625)
		        		{
		        			buy_property(block,current_player);
		        				flag=0;

		        		}
		        		
		        		else
		        		{
		        			dice2==roll_dice();
		        			if (dice2<=3 && dice2>=1)
		        			{
		        				buy_property(block,current_player);
		        				flag=0;
		        			}
		        			else
		        				flag=0;
		        		}
	        		}
		        	else if (block->owner.type==cap)
	            	{
	            		if(current_player->owned_block_ids[0]!=-1 && current_player->owned_block_ids[1]!=-1 && 
	            		    current_player->owned_block_ids[2]!=-1 && current_player->owned_block_ids[3]!=-1)
	            		{
	            		
		            		dice2=roll_dice();
		            		if(dice2<=3 && dice2>=1)
		            		{
		            			build_house(block, current_player);
		            			flag=0;
		            		}
		            		else 
		            			flag=0;	
	           			}
	           		}
	            	else if (block->owner.type==car)
	            	{
	            		pay_rent(head,current_player,other);
	            		flag=0;
	            	}  
            		break;
	            case tax:
		            printf("%s has arrived tax block(%s)\n",current_player->name,block->name);
		            while (count_properties(*current_player)!=0 && current_player->account < block->price) {
		                insuf_flag = insufficient_fund(head, current_player,
		                                               block->price);
		                if (insuf_flag == 0 && current_player->account < block->price)
		                    printf("You must pay your tax!\n");

		            }
		            if (current_player->account > block->price){
		                current_player->account=current_player->account-block->price;
		                flag=0;
		            }
		            else
		            {
		                current_player->account=0;
		                flag=0;
		            }
		            flag=0;
		        	break;
	       		case punish:
		            printf("%s has punished for %d turn. \n",current_player->name,block->price);
		            current_player->turn_to_wait+=block->price;
		            flag=0;
		            break;
       		 flag=0;
        	}
        }
        else
    	{
            printf("You need to wait %d turn to continue.\n",current_player->turn_to_wait);
            current_player->turn_to_wait-=1;
            flag=0;
    	}
    flag=0;
    }
}

void fortune_card_(node * head,player* current_player, player * other){
	int dice1=roll_dice()-1,next_block;
	block * block = get_block_at(head, current_player->current_block_id);

	if (dice1==2)
	{
		printf("Card Name:Time Travel \n");
		int dice2=roll_dice();
		printf("rolled the dice: %d\n",dice2);
		if(dice2>=1 && dice2<=3)
			next_block=(current_player->current_block_id + 2);
		else 
			next_block=(current_player->current_block_id - 2);
	}
	if (dice1==3){
		printf("Card Name:Garnishment \n");
		current_player->account-=5000;

	}
	if (dice1==4){
		printf("Card Name:Generosity \n");
		current_player->account-=10000;
		other->account+=10000;	
	}
	if(dice1==5){
		printf("Card Name: Treasure Hunter\n");
		current_player->account+=20000;
	}
		
}