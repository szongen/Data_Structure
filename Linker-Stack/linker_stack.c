#include <stdio.h>
#include <stdlib.h>

typedef int data_t;
typedef struct node
{

    data_t data;
    struct node *next;
} listnode, *linkstack;

linkstack stack_create();
int stack_push(linkstack s, data_t value);
data_t stack_pop(linkstack s);
int stack_empty(linkstack s);
data_t stack_top(linkstack s);
linkstack stack_free(linkstack s);

int main()
{
    linkstack s;
    s = stack_create();
    if (s == NULL)
    {
        return -1;
    }
    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_push(s, 40);
    stack_push(s, 50);
#if 0 
    while (!stack_empty(s))
    {
        printf("pop:%d\n",stack_pop(s));
    }
#endif 
    s = stack_free(s);
    
}

linkstack stack_create()
{
    linkstack s;
    s = (linkstack)malloc(sizeof(listnode));
    if (s == NULL)
    {
        printf("malloc is failed\n");
        return;
    }
    s->data = 0;
    s->next = NULL;
    return s;
}
int stack_push(linkstack s, data_t value)
{
    linkstack p;
    if (s == NULL)
    {
        printf("s is null\n");
        return -1;
    }
    p = (linkstack)malloc(sizeof(listnode));
    if (p == NULL)
    {
        printf("malloc p is failed\n");
        return -1;
    }
    p->data = value;
    p->next = s->next;
    s->next = p;

    return 0;
}

data_t stack_pop(linkstack s)
{
    linkstack p;
    data_t t;
    if (s == NULL)
    {
        printf("s is null\n");
        return -1;
    }
    p = s->next;
    s->next = p->next;
    t = p->data;
    free(p);
    p = NULL;
    return t;
}

int stack_empty(linkstack s)
{
    if (s == NULL)
    {
        printf("s is null\n");
        return -1;
    }
    return (s->next == NULL ? 1 : 0);
}

data_t stack_top(linkstack s)
{
        if (s == NULL)
    {
        printf("s is null\n");
        return -1;
    }
    return s->next->data;
}

linkstack stack_free(linkstack s)
{
    linkstack p;
    if (s == NULL)
    {
        printf("s is null\n");
        return NULL;
    }
    while (s!=NULL)
    {
        p = s;
        s = s->next;
        printf("free:%d\n",p->data);
        free(p);
    }
    return NULL;
}
