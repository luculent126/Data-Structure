#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

int count;
typedef int element;
typedef struct
{
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// 에러함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 초기화함수
void init_queue(QueueType *q)
{
    q->front = q->rear = 0 && count == 0;
}

// 공백함수
int is_empty(QueueType *q)
{
    return (q->front == q->rear && count == 0);
}

// 포화함수
int is_full(QueueType *q)
{
    return (q->front == q->rear && count == MAX_QUEUE_SIZE);
}

// 큐 출력함수
void queue_print(QueueType *q)
{
    printf("QUEUE(front=%d rear=%d count=%d) = ", q->front, q->rear, count);
    if (!is_empty(q))
    {
        int i = q->front;
        do
        {
            i = (i + 1) % (MAX_QUEUE_SIZE);
            printf("%d | ", q->data[i]);
            if (i == q->rear)
                break;
        }
        while (i != q->front);
    }
    printf("\n");
}

// enqueue(삽입)함수
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error ('queue is full');
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
    count = count + 1;
}

// dequeue(삭제)함수
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("queue is empty.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    count = count - 1;
    return q->data[q->front];
}

// peek함수
element peek(QueueType *q)
{
    if (is_empty(q))
        error("queue is empty.");
        count = count - 1;
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}