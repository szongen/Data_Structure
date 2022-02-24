#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_t;
#define N 128

typedef struct {
	data_t data[N];
	int last;
}sqlist,*sqlink;


int list_clear(sqlink L);
int list_empty(sqlink L);
int list_length(sqlink L);
int list_length(sqlink L);
int list_locate(void);

sqlink list_create(){
	sqlink L;

	L = (sqlink)malloc(sizeof(sqlist));
	if(L == NULL)
	{
		printf("list malloc failed\n");
		return L;
	}


	memset(L,0,sizeof(sqlink));
	L->last = -1;


	return L;
}

/**
 * @brief 
 * 
 * @param L 
 * @return int  0-success -1-failed 
 */
int list_clear(sqlink L)
{
	if(L == NULL)
	{
		return -1;
	}
	memset(L,0,sizeof(sqlink));
	L->last = -1;
}

int main(void)
{
	
} 
