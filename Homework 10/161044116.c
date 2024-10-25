#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	SIZE 20

typedef struct stack { 
	int data;
	struct stack * next;
}stack;

typedef struct queue {
	int data;
	struct queue * next;
}queue;

typedef struct  bst {
	int data;
	struct bst * left;
	struct bst * right; 

}bst;


void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[20]);
void ordered_print(stack * stack_, queue * queue_, bst * bst_);
void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search);

void add_stack(stack **stack_,int data);
void add_queue(queue **queue_,int data);
void add_bst(bst ** bst_,int data);

void printf_stack(stack *stack);
void printf_queue(queue *queue_);
void printf_bst(bst * bst_);

void sort_stack(stack * stack_);
void sort_queue(queue *queue_);
void swap(stack *a, stack *b);
void swap2(queue *a, queue *b);

bst * search_bst(bst* bst_, int data);
void stack_traverse(stack ** stack_);
void queue_traverse(queue ** queue_);
void printf_treverse_bst(bst* bst_);


void special_traverse(stack * stack_, queue * queue_, bst * bst_);

int main()
{
	int data[20]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17,8, 23, 4};
	bst * bst_;
	queue * queue_;
	stack * stack_;
	fill_structures(&stack_,&queue_,&bst_, data);
	ordered_print(stack_, queue_, bst_);
	search(stack_, queue_, bst_, 7);
	special_traverse(stack_, queue_, bst_);
	return 0;
}
void fill_structures(stack ** stack_, queue ** queue_, bst ** bst_, int data[20])
{	
	int temp;
	float time_stack, time_queue , time_bst ;
	clock_t start_stack, end_stack, start_queue, end_queue, start_bst, end_bst;
	
	start_stack = clock();
	for (int i = 0; i < SIZE ; ++i)
		add_stack(stack_,data[i]);
	end_stack = clock();
	time_stack =((double) end_stack - start_stack);
	
	start_queue = clock();
	for (int i = 0; i < SIZE ; ++i)
		add_queue(queue_,data[i]);
	end_queue = clock();
	time_queue =((double) end_queue - start_queue);
	start_bst = clock();
	for (int i = 0; i < SIZE ; ++i)
		add_bst(bst_,data[i]);
	end_bst = clock();
	time_bst =((double) end_bst - start_bst);

	printf("\nThe Performance result reports should be seem as following:\n");
	printf("\nStructures     Stack        Queue      Bst \n");
	printf("\nExe.Time       %.2lf         %.2lf      %.2lf \n",time_queue/60,time_stack/60,time_bst/60);
}
void add_stack(stack **stack_,int data)
{
	stack * temp = (stack * )malloc(sizeof(stack));
	temp->data = data;
	
	if(*stack_ == NULL)
	{   
     	*stack_ = temp;
     	(*stack_)->next = NULL;
    }
    else 
    {
	    temp->next = *stack_;
	    *stack_ = temp;
	}
}
void add_queue(queue **queue_,int data)
{
	
	queue * tail = *queue_;
	tail = *queue_;
	queue * temp = (queue * )malloc(sizeof(queue));
	temp->data = data;
	temp->next = NULL;

	if(*queue_ == NULL)
	{
		*queue_= temp;
	}
	else
	{
		while(tail->next != NULL)
			tail = tail->next;
		tail->next = temp;
		tail=temp;
	}	
}

void add_bst(bst ** bst_ , int data)
{
	bst * temp = (bst *) malloc(sizeof(bst));
	temp->data = data;
	temp->left=temp->left=NULL;
	
	if(*bst_ == NULL)
	{
		*bst_ = temp;
	}
	if(data < (*bst_)->data)

		add_bst(&((*bst_)->left),data);
	
	else if(data > (*bst_)->data) 
        
        add_bst(&((*bst_)->right),data); 
}
void printf_stack(stack *stack_)
{
	printf("\n");
    stack * temp = stack_;
    printf("\nStack : ");	
    if(stack_== NULL)
	    printf("Stack: Empty \n");
	
	else{
	    while(temp != NULL){
	    	
	    	printf("%d ",temp->data);
	    	temp = temp->next;
	    }
	}
}
void printf_queue(queue *queue_)
{
    queue * temp = queue_;
    printf("\nQueue : ");
    if(queue_== NULL)
	    printf("Queue: Empty \n");
	
	else{
	    while(temp!=NULL){
	    	
	    	printf("%d ",temp->data);
	    	temp = temp->next;
	    }
	}
}
void printf_bst(bst* bst_)
{
   if (bst_ != NULL) 
    { 
        printf_bst(bst_->right);
        printf("%d ",bst_->data );
        printf_bst(bst_->left);  
    } 
}
void sort_stack(stack * stack_)
{
	int count, i; 
	stack * temp;
	stack * temp2 = NULL; 
	
	if (stack_ == NULL) 
    	return; 
    
    while(count)
    {

    	count = 0; 
        temp = stack_;

          while (temp->next != temp2) 
        { 
            if (temp->data < temp->next->data) 
            {  
                swap(temp, temp->next); 
                count = 1; 
            } 
            temp = temp->next; 
        } 
        temp2 = temp; 
    }
     
}
void sort_queue(queue *queue_) 
{ 
    int swapped, i; 
    queue *temp; 
    queue *temp2 = NULL; 
    if (queue_ == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        temp = queue_; 
  
        while (temp->next != temp2) 
        { 
            if (temp->data < temp->next->data) 
            {  
                swap2(temp, temp->next); 
                swapped = 1; 
            } 
            temp = temp->next; 
        } 
        temp2 = temp; 
    } 
    while (swapped); 
}
void swap(stack *a,stack *b) 
{ 	
	int temp;
	char * tempchar;
    
    temp = a->data; 
    a->data = b->data; 
    b->data = temp;
}
void swap2(queue * a,queue * b) 
{ 	
	int temp;
	char * tempchar;
    
    temp = a->data; 
    a->data = b->data; 
    b->data = temp;
}
void ordered_print(stack * stack_, queue * queue_, bst * bst_)
{	
	printf("-------------------------------------------------------------------------\n");
	float time_stack, time_queue , time_bst ;
	clock_t start_stack, end_stack, start_queue, end_queue, start_bst, end_bst;
	start_stack = clock();
	sort_stack(stack_);
	printf_stack(stack_);
	end_stack = clock();
	time_stack =((double) end_stack - start_stack);
	start_queue = clock();
	sort_queue(queue_);
	printf_queue(queue_);
	end_queue = clock();
	time_queue =((double) end_queue - start_queue);
	start_bst = clock();
	printf("\nBst   : ");
	printf_bst(bst_);
	end_bst = clock();
	time_bst =((double) end_bst - start_bst);
	printf("\n\nThe Performance result reports should be seem as following:\n");
	printf("\nStructures     Stack        Queue      Bst \n");
	printf("\nExe.Time       %.2lf         %.2lf      %.2lf \n",time_queue/60,time_stack/60,time_bst/60);
	printf("-------------------------------------------------------------------------\n");
}

void search(stack * stack_, queue * queue_, bst * bst_, int val_to_search)
{

	int count=0;
	int arr[10000];
	int arr2[10000];
	int k =0,i;
	stack * temp =NULL;
	queue * temp2 = NULL;
	temp = stack_;
	temp2 = queue_;
	float time_stack, time_queue , time_bst ;
	clock_t start_stack, end_stack, start_queue, end_queue, start_bst, end_bst;
	
	start_stack = clock();
	for (i = 0; temp != NULL; ++i)
	{
		if(temp->data == val_to_search)
		{
			count +=1;
			arr[k]=i+1;
			k++;
		}
		temp = temp->next;
	}
	printf("\n\nSearching element in Stack..\n");
	printf("%d result founded on ",count );
	for (i = 0; i < count ; ++i)
	{
		printf("%d. ",arr[i]);
	}
	printf("step\n");
	end_stack = clock();
	time_stack =((double) end_stack - start_stack);
	

	k=0;
	count = 0;

	
	start_queue = clock();
	for (i = 0; temp2 != NULL; ++i)
	{
		if(temp2->data == val_to_search)
		{
			count +=1;
			arr2[k]=i+1;
			k++;
		}
		temp2 = temp2->next;
	}
	printf("\nSearching element in Queue..\n");
	printf("%d result founded on ",count );
	for (i = 0; i < count ; ++i)
	{
		printf("%d. ",21-arr2[i]);
	}
	printf("step\n");
	end_queue = clock();
	time_queue =((double) end_queue - start_queue);
	
	start_bst = clock();
	printf("\nSearching element in Bst..\n");
	static int sayac;
	search_bst(bst_,val_to_search);
	printf("%d result founded on ",count);
	end_bst = clock();
	time_bst =((double) end_bst - start_bst);
	printf("\n\nThe Performance result reports should be seem as following:\n");
	printf("\nStructures     Stack        Queue      Bst \n");
	printf("\nExe.Time       %.2lf         %.2lf      %.2lf \n",time_queue/60,time_stack/60,time_bst/60);
	printf("-------------------------------------------------------------------------\n");
}
int count;
bst * search_bst(bst* bst_, int data)
{ 
   	count += 1;
    if (bst_ == NULL || bst_->data == data)
    {
       return bst_;
       	count += 1; 
    }
    if (bst_->data < data)
    {
       return search_bst(bst_->right, data);
       	count += 1;
  	}
  	else
    	return search_bst(bst_->left, data); 
    return bst_;
}

void special_traverse(stack * stack_, queue * queue_, bst * bst_)
{
	float time_stack, time_queue , time_bst ;
	clock_t start_stack, end_stack, start_queue, end_queue, start_bst, end_bst;
	start_stack = clock();
	stack_traverse(&stack_);
	printf_stack(stack_);
	end_stack = clock();
	time_stack =((double) end_stack - start_stack);

	start_queue = clock();
	queue_traverse(&queue_);
	printf_queue(queue_);
	end_queue = clock();
	time_queue =((double) end_queue - start_queue);
	printf("\nbst : ");

	start_bst = clock();
	printf_treverse_bst(bst_);
	end_bst = clock();
	time_bst =((double) end_bst - start_bst);
	printf("\nThe Performance result reports should be seem as following:\n");
	printf("\nStructures     Stack        Queue      Bst \n");
	printf("\nExe.Time       %.2lf         %.2lf      %.2lf \n",time_queue/60,time_stack/60,time_bst/60);

}
void stack_traverse(stack ** stack_)
{
    stack *temp, *prev;
 
    if (*stack_ == NULL)
    {
        printf("Stack does not exist\n");
    }
    else if ((*stack_)->next->next == NULL)
    {
        (*stack_)->next->next = *stack_;
        *stack_ = (*stack_)->next;
        (*stack_)->next->next = NULL;
    }
    else
    {
        prev = *stack_;
        temp = (*stack_)->next;
        *stack_ = (*stack_)->next->next;
        prev->next = NULL;
        while ((*stack_)->next != NULL)
        {
            temp->next = prev;
            prev = temp;
            temp = *stack_;
            *stack_ = (*stack_)->next;
        }
        temp->next = prev;
        (*stack_)->next = temp;
    }
}
void queue_traverse(queue ** queue_)
{
    queue *temp, *prev;
 
    if (*queue_ == NULL)
    {
        printf("queue does not exist\n");
    }
    else if ((*queue_)->next->next == NULL)
    {
        (*queue_)->next->next = *queue_;
        *queue_ = (*queue_)->next;
        (*queue_)->next->next = NULL;
    }
    else
    {
        prev = *queue_;
        temp = (*queue_)->next;
        *queue_ = (*queue_)->next->next;
        prev->next = NULL;
        while ((*queue_)->next != NULL)
        {
            temp->next = prev;
            prev = temp;
            temp = *queue_;
            *queue_ = (*queue_)->next;
        }
        temp->next = prev;
        (*queue_)->next = temp;
    }
}
void printf_treverse_bst(bst* bst_)
{
   if (bst_ != NULL) 
    { 
        printf_bst(bst_->left);
        printf("%d ",bst_->data );
        printf_bst(bst_->right);  
    } 
}


