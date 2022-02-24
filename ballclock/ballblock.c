#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

typedef struct node
{
    datatype data;
    struct node *next;
} listnode, *linklist;

typedef struct
{
    linklist front;
    linklist rear;
} linkqueue;

linkqueue *queue_create();
int enqueue(linkqueue *lq, datatype x);
datatype dequeue(linkqueue *lq);
int queue_empty(linkqueue *lq);
int queue_clear(linkqueue *lq);
linkqueue *queue_free(linkqueue *lq);

typedef int data_t;
typedef struct
{
    data_t *data;
    int maxlen;
    int top;
} sqstack;

sqstack *stack_create(int len);
int stack_push(sqstack *s, data_t value);
int stack_empty(sqstack *s);
int stack_full(sqstack *s);
data_t stack_pop(sqstack *s);
data_t stack_top(sqstack *S);
int stack_clear(sqstack *s);
int stack_free(sqstack *s);

int check(linkqueue *lq)
{
    linklist p;
    if (lq == NULL)
    {
        printf("lq is null\n");
        return -1;
    }
    p = lq->front->next;
    while (p && p->next)
    {
        if (p->data < p->next->data)
        {
            p = p->next;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    linkqueue *lq;
    sqstack *s_hour, *s_five, *s_min;
    int i, min;
    int value;
    lq = queue_create();
    if (lq == NULL)
    {

        return -1;
    }
    for (i = 1; i <= 27; i++)
    {
        enqueue(lq, i);
    }
    if ((s_hour = stack_create(11)) == NULL)
    {
        return -1;
    }
    if ((s_five = stack_create(11)) == NULL)
    {
        return -1;
    }
    if ((s_min = stack_create(4)) == NULL)
    {
        return -1;
    }
    while (1)
    {
        min++;
        if (!queue_empty(lq))
        {
            value = dequeue(lq);
            if (!stack_full(s_min))
            {
                stack_push(s_min, value);
            }
            else
            {
                while ((!stack_empty(s_min)))
                {
                    enqueue(lq, stack_pop(s_min));
                }
                if (!stack_full(s_five))
                {
                    stack_push(s_five, value);
                }
                else
                {
                    while (!stack_empty(s_five))
                    {
                        enqueue(lq, stack_pop(s_five));
                    }
                    if (!stack_full(s_hour))
                    {
                        stack_push(s_hour, value);
                    }
                    else
                    {
                        while (!stack_empty(s_hour))
                        {
                            enqueue(lq, stack_pop(s_hour));
                        }
                        enqueue(lq, value);
                        if (check(lq) == 1)
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
    printf("total:%d\n",min);
    printf("dequeue:");
    while (!queue_empty(lq))
    {
        printf("%d ", dequeue(lq));
    }
    printf("\n");
    queue_clear(lq);
    lq = queue_free(lq);
    enqueue(lq, 50);

    return 0;
}

linkqueue *queue_create()
{
    linkqueue *lq;
    lq = (linkqueue *)malloc(sizeof(linkqueue));
    if (lq == NULL)
    {
        printf("malloc linkqueue failed\n");
        return NULL;
    }
    lq->front = lq->rear = (linklist)malloc(sizeof(listnode));

    if (lq->front == NULL)
    {
        printf("malloc node failed\n");
        return NULL;
    }

    lq->front->data = 0;
    lq->front->next = NULL;
    return lq;
}

int enqueue(linkqueue *lq, datatype x)
{
    linklist p;
    if (lq == NULL)
    {
        printf("lq is null\n");
        return -1;
    }
    if ((p = (linklist)malloc(sizeof(listnode))) == NULL)
    {
        printf("malloc node failed\n");
        return -1;
    }
    p->data = x;
    p->next = NULL;
    lq->rear->next = p;
    lq->rear = p;
    return 0;
}
datatype dequeue(linkqueue *lq)
{
    linklist p;
    if (lq == NULL)
    {
        printf("lq is null\n");
        return -1;
    }
    p = lq->front;
    lq->front = p->next;
    free(p);
    p = NULL;
    return lq->front->data;
}
int queue_empty(linkqueue *lq)
{
    linklist p;
    if (lq == NULL)
    {
        printf("lq is null\n");
        return -1;
    }
    return (lq->front == lq->rear ? 1 : 0);
}
int queue_clear(linkqueue *lq)
{
    linklist p;

    if (lq == NULL)
    {
        printf("lq is null\n");
        return -1;
    }
    while (lq->front->next)
    {
        p = lq->front;
        lq->front = p->next;
        printf("clear:%d\n", p->data);
        free(p);
        p = NULL;
    }
    return 0;
}
linkqueue *queue_free(linkqueue *lq)
{
    linklist p;
    if (lq == NULL)
    {
        printf("lq is null\n");
        return NULL;
    }
    while (lq->front)
    {
        p = lq->front;
        lq->front = p->next;
        printf("free:%d\n", p->data);
        free(p);
    }
    free(lq);
    return 0;
}

sqstack *stack_create(int len)
{
    sqstack *s;
    if ((s = (sqstack *)malloc(sizeof(sqstack))) == NULL)
    {
        printf("malloc sqstack failed \n");
        return NULL;
    }

    if ((s->data = (data_t *)malloc(len * sizeof(data_t))) == NULL)
    {
        printf("malloc data failed\n");
        free(s);
        return NULL;
    }

    memset(s->data, 0, len * sizeof(data_t));
    s->maxlen = len;
    s->top = -1;

    return s;
}

int stack_push(sqstack *s, data_t value)
{
    if (s == NULL)
    {
        printf("S is null\n");
        return -1;
    }
    if (s->top == (s->maxlen - 1))
    {
        printf("stack is full\n");
        return -1;
    }

    s->top++;
    s->data[s->top] = value;

    return 0;
}
/**
 * @brief
 *
 * @param s
 * @return int 1 is empty ;0 is not empty
 */
int stack_empty(sqstack *s)
{
    if (s == NULL)
    {
        printf("S is null\n");
        return -1;
    }
    return (s->top == -1 ? 1 : 0);
}
/**
 * @brief
 *
 * @param s
 * @return int full is 1 not full is 0
 */
int stack_full(sqstack *s)
{
    if (s == NULL)
    {
        printf("S is null\n");
        return -1;
    }
    return (s->top == s->maxlen - 1 ? 1 : 0);
}
data_t stack_pop(sqstack *s)
{
    s->top--;
    return (s->data[s->top + 1]);
}

data_t stack_top(sqstack *s)
{
    return (s->data[s->top]);
}
int stack_clear(sqstack *s)
{
    if (s == NULL)
    {
        printf("s is null\n");
        return -1;
    }
    s->top = -1;
    return 0;
}
int stack_free(sqstack *s)
{
    if (s == NULL)
    {
        printf("S is null\n");
        return -1;
    }
    if (s->data != NULL)
    {
        free(s->data);
    }
    free(s);
    return 0;
}