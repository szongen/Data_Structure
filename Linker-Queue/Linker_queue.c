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

int main(int argc, char const *argv[])
{
    /* code */

    linkqueue *lq;
    lq = queue_create();
    if (lq == NULL)
    {

        return -1;
    }
    enqueue(lq, 10);
    enqueue(lq, 20);
    enqueue(lq, 30);
    enqueue(lq, 40);
    enqueue(lq, 50);

    // while (!queue_empty(lq))
    // {
    //     printf("dequeue :%d\n", dequeue(lq));
    // }
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
    while(lq->front->next){
        p = lq->front;
        lq->front = p->next;
        printf("clear:%d\n",p->data);
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
