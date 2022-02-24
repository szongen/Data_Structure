#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int data_t;

typedef struct node
{
	data_t data;
	struct node *next;

} listnode, *linklist;

linklist list_create();
int list_tail_insert(linklist H, data_t value); // head
int list_insert(linklist H, data_t value, int pos);
linklist list_get(linklist H, int pos);
int list_delete(linklist H, int pos);
linklist list_free(linklist H);
int list_show(linklist H);
void test_insert(linklist H);
void test_get(linklist H);
int list_reverse(linklist H);
linklist list_adjmax(linklist H, data_t *value);
void test_adjmax(linklist H);
int list_merge(linklist H1, linklist H2);

int main()
{
	linklist H1, H2;
	int i;
	int a[] = {1, 4, 6, 8, 40};
	int b[] = {2, 4, 16, 18, 30};
	H1 = list_create();
	if (H1 == NULL)
	{
		return;
	}

	H2 = list_create();
	if (H2 == NULL)
	{
		return;
	}
	for (i = 0; i < sizeof(a) / sizeof(int); i++)
	{
		list_tail_insert(H1, a[i]);
	}

	for (i = 0; i < sizeof(b) / sizeof(int); i++)
	{
		list_tail_insert(H2, b[i]);
	}
	list_show(H1);
	list_show(H2);
	list_merge(H1,H2);
	printf("merge\n");
	list_show(H1);
	list_free(H1);
	list_free(H2);

	/*

		linklist H, p;
		int value;

		H = list_create();
		if (H == NULL)
		{
			return -1;
		}
		printf("input:");
		while (1)
		{
			scanf("%d", &value);
			if (value == -1)
			{
				printf("break success\n");
				break;
				printf("break failed\n");
			}
			list_tail_insert(H, value);
			printf("input:");
		}
		list_show(H);
		//	test_get(H);
		// test_insert(H);
		// list_reverse(H);
		// test_adjmax(H);
		list_show(H);
		H = list_free(H);
		return 0;

	*/
}

linklist list_create()
{
	linklist H;

	H = (linklist)malloc(sizeof(listnode));
	if (H == NULL)
	{
		printf("malloc failed \n");
		return H;
	}
	H->data = 0;
	H->next = NULL;
	return H;
}

int list_tail_insert(linklist H, data_t value)
{
	linklist p, q;
	if (H == NULL)
	{
		printf("H is null\n");
		return -1;
	}
	if ((p = (linklist)malloc(sizeof(listnode))) == NULL)
	{
		printf("malloc failed \n");
		return -1;
	}

	p->data = value;
	p->next = NULL;
	q = H;
	while (q->next != NULL)
	{
		q = q->next;
	}
	q->next = p;

	return 0;
}

int list_show(linklist H)
{
	linklist p;
	if (H == NULL)
	{
		printf("H is null\n");
		return -1;
	}
	printf("data:");
	p = H;
	while (p->next != NULL)
	{
		printf("%d,", p->next->data);
		p = p->next;
	}
	printf("\n");
}

int list_insert(linklist H, data_t value, int pos)
{
	linklist p;
	linklist q;
	if (H == NULL)
	{
		printf("H is invalid\n");
		return -1;
	}
	p = list_get(H, pos - 2);
	if (p == NULL)
	{
		return -1;
	}
	q = (linklist)malloc(sizeof(listnode));

	q->data = value;
	q->next = NULL;

	q->next = p->next;
	p->next = q;
	return 0;
}

linklist list_get(linklist H, int pos)
{
	int i;
	linklist p;
	if (H == NULL)
	{
		printf("H is NULL\n");
		return NULL;
	}
	if (pos <= -1)
	{
		return H;
	}
	p = H;
	i = -1;
	while (i < pos)
	{
		p = p->next;
		if (p == NULL)
		{
			printf("pos is invalid\n");
			return NULL;
		}
		i++;
	}

	return p;
}

int list_delete(linklist H, int pos)
{
	linklist p, q;
	if (H == NULL)
	{
		printf("H is NULL\n");
		return -1;
	}
	p = list_get(H, pos - 2);
	if (p == NULL)
	{
		return -1;
	}
	if (p->next == NULL)
	{
		printf("delete pos is valid\n");
		return -1;
	}
	q = p->next;
	p->next = q->next;
	printf("free :%d\n", q->data);
	free(q);
	return 0;
}

linklist list_free(linklist H)
{
	linklist p;
	if (H == NULL)
	{
		printf("free list is empty\n");
		return NULL;
	}
	p = H;
	printf("free:");
	while (H != NULL)
	{
		p = H;
		H = H->next;
		printf("%d ,", p->data);
		free(p);
	}
	printf("\n");
	return NULL;
}

void test_get(linklist H)
{
	linklist p;
	p = list_get(H, 2);
	if (p != NULL)
	{
		printf("value:%d\n", p->data);
	}
}

void test_insert(linklist H)
{
	list_insert(H, 100, 2);
	list_show(H);
}

int list_reverse(linklist H)
{
	linklist p, q;
	if (H == NULL)
	{
		printf("reverse H is empty\n");
		return -1;
	}

	if ((H->next == NULL) || (H->next == NULL))
	{
		printf("reverse H next is empty\n");
		return -1;
	}

	p = H->next->next;
	H->next->next = NULL;

	while (p != NULL)
	{
		q = p;
		p = p->next;

		q->next = H->next;
		H->next = q;
	}

	return 0;
}

linklist list_adjmax(linklist H, data_t *value)
{
	linklist p, q;
	int sum;
	printf("list_adjmax\n");
	if (H == NULL)
	{
		printf("H is empty1\n");
		return NULL;
	}
	if (H->next == NULL)
	{
		printf("H is empty2\n");
		return NULL;
	}
	if (H->next->next == NULL)
	{
		*value = H->data + H->next->data;
		printf("H is empty3\n");
		return H->next;
	}
	p = H->next;
	sum = p->data + p->next->data;
	q = p;
	while (p->next != NULL)
	{
		if ((p->data + p->next->data) > sum)
		{
			sum = (p->data + p->next->data);
			q = p;
		}
		p = p->next;
	}

	*value = sum;
	return q;
}

void test_adjmax(linklist H)
{
	int sum;
	linklist p;
	p = list_adjmax(H, &sum);
	if ((p != NULL) && (p != H))
	{
		printf("adjmax=%d,sum = %d\n", p->data, sum);
	}
	else
	{
		printf("p is empty");
	}
}

int list_merge(linklist H1, linklist H2)
{
	linklist p, q,r;
	if (H1 == NULL || H2 == NULL)
	{
		printf("H1 and H2 is empty\n");
		return -1;
	}
	p = H1->next;
	q = H2->next;
	H1->next = NULL;
	H2->next = NULL;
	r = H1;
	while (p && q)
	{
		if(p->data <= q->data)
		{
			H1->next = p;
			p = p->next;
			H1 = H1->next;
			H1 ->next =NULL;
		}
		else if(p->data > q->data)
		{
			H1->next = q;
			q = q->next;	
			H1 = H1->next;
			H1 ->next =NULL;
		}
	}
	if(q == NULL)
	{
		H1->next = p;
	}
	else {
		H1->next = q;
	}
	return 0;

}
