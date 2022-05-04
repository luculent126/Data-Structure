#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 설정
typedef struct
{
    char name[100];
} element;

typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

// 에러함수
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 첫번째 노드 삽입함수
ListNode* insert_first(ListNode *head, element value)
{
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = value;
    p->link = head;
    head = p;
    return head;
}

// 삭제함수 선언
ListNode delete(ListNode *head, ListNode *pre)
{
    ListNode *removed;
    removed = pre->link;

    while (removed != NULL)
    {
        pre->link = removed->link;
        free(removed);
    }
}

// 연결리스트 출력함수
void print_list(ListNode *head)
{
    for (ListNode *p = head; p != NULL; p = p->link)
        printf("%s-> ", p->data.name);
    printf("NULL\n");
}