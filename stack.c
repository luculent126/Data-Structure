#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 6
#define MAX_SIZE 100

// 구조체 설정
typedef struct element
{
   short r;
   short c;
} element;

typedef struct stackType
{
   element data[MAX_SIZE];
   int top;
} stackType;

// 초기화 함수
void init_stack(stackType* s)
{
   s->top = -1;
}

// 공백함수
int is_empty(stackType* s)
{
   return (s->top == -1);
}

// 포화함수
int is_full(stackType* s)
{
   return (s->top == MAZE_SIZE - 1);
}

// push(삽입)함수
void push(stackType* s, element item)
{
   if (is_full(s))
   {
      fprintf(stderr, "stack full error\n");
      return;
   }
   else
   {
      s->data[++(s->top)] = item;
   }
}

// pop(삭제)함수
element pop(stackType* s)
{
   if (is_empty(s))
   {
      fprintf(stderr, "stack empty error\n");
      exit(1);
   }
   else
      return s->data[(s->top)--];
}