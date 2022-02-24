#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int datatype;

#define N 128

typedef struct
{
    datatype data[N];
    int front;
    int rear;
} sequeue;

sequeue *queue_create(void);
int enqueue(sequeue *sq, datatype x);
datatype dequeue(sequeue *sq);
int queue_empty(sequeue *sq);
int queue_full(sequeue *sq);
int queue_clear(sequeue *sq);
sequeue queue_free(sequeue *sq);

int main(int argc, char const *argv[])
{
    sequeue *sq;
    sq = queue_create();
    if (sq == NULL)
    {
        printf("sq is null\n");
        return -1;
    }

    enqueue(sq, 10);
    enqueue(sq, 100);
    enqueue(sq, 1000);
    while (!queue_empty(sq))
    {
        printf("deque:%d\n", dequeue(sq));
    }

    return 0;
}

sequeue *queue_create(void)
{
    sequeue *sq;
    if ((sq = (sequeue *)malloc(sizeof(sequeue))) == NULL)
    {
        printf("malloc failed \n");
        return NULL;
    }
    memset(sq->data, 0, sizeof(sq->data));
    sq->front = sq->rear = 0;
    return sq;
}

int enqueue(sequeue *sq, datatype x)
{
    if (sq == NULL)
    {
        printf("sq is NULL \n");
        return -1;
    }
    if ((sq->rear + 1) % N == sq->front)
    {
        printf("sequeue is full\n");
        return -1;
    }

    sq->data[sq->rear] = x;
    sq->rear = (sq->rear + 1) % N;
    return 0;
}
datatype dequeue(sequeue *sq)
{
    datatype ret;
    if (sq == NULL)
    {
        printf("sq is NULL \n");
        return -1;
    }

    ret = sq->data[sq->front];

    sq->front = (sq->front + 1) % N;

    return ret;
}
int queue_empty(sequeue *sq)
{
    if (sq == NULL)
    {
        printf("sq is NULL \n");
        return -1;
    }
    return (sq->front == sq->rear ? 1 : 0);
}
int queue_full(sequeue *sq)
{
    if (sq == NULL)
    {
        printf("sq is NULL \n");
        return -1;
    }
    if (((sq->rear + 1) % N) == sq->front)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int queue_clear(sequeue *sq)
{
    if(sq == NULL)
    {
        printf("sq is NULL \n");
        return -1;
    }
}
sequeue queue_free(sequeue *sq)
{
}
