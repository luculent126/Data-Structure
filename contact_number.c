// 이진 탐색 트리를 사용한 연락처 프로그램
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define MAX_WORD_SIZE 100
#define MAX_MEANING_SIZE 200

// 데이터 형식
typedef struct 
{
	char word[MAX_WORD_SIZE];		// 이름
	char meaning[MAX_MEANING_SIZE]; // 전화번호
} element;

// 노드의 구조
typedef struct TreeNode 
{
	element key;
	struct TreeNode *left, *right;
} TreeNode;

// 만약 e1 < e2 이면 -1 반환
// 만약 e1 == e2 이면 0 반환
// 만약 e1 > e2 이면 1 반환
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}

// 노드 개수
int node_count(TreeNode *node)
{
	int count = 0;
	if (node != NULL)
		count = 1 + node_count(node->left) + node_count(node->right);
	return count;
}

// 출력함수
void display(TreeNode *p)
{
	if (p != NULL) 
	{
		// 중위 순회 사용
		display(p->left);
		printf("count: %d, %s's phone number: %s \n", node_count(p), p->key.word, p->key.meaning);
		display(p->right);
	}
}

// 탐색함수
TreeNode *search(TreeNode *root, element key)
{
	TreeNode *p = root;
	while (p != NULL) 
	{
		if (compare(key, p->key) == 0)
			return p;
		else if (compare(key, p->key) < 0)
			p = search(p->left, key);
		else if (compare(key, p->key) > 0)
			p = search(p->right, key);
	}
	return p; 	// 탐색에 실패했을 경우 NULL 반환
}

// 새로운 노드 만드는 함수
TreeNode *new_node(element item)
{
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

// 삽입함수
TreeNode *insert_node(TreeNode *node, element key)
{
	// 트리가 공백이면 새로운 노드를 반환한다. 
	if (node == NULL) 
        return new_node(key);

	// 그렇지 않으면 순환적으로 트리를 내려간다. 
	if (compare(key, node->key)<0)
		node->left = insert_node(node->left, key);
	else if (compare(key, node->key)>0)
		node->right = insert_node(node->right, key);
	else if (compare(key, node->key)==0)
		node->key = key;
	// 루트 포인터를 반환한다. 
	return node;
}

// 삭제 함수 중 3번째 경우를 위해서 작성
TreeNode *max_value_node(TreeNode *node)
{
	TreeNode *current = node;
	// 맨 왼쪽 단말 노드를 찾으러 내려감
	while (current->right != NULL)
		current = current->right;
	return current;
}

// 종료 함수
void quit()
{
	exit(1);
}

// 이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 
// 새로운 루트 노드를 반환한다. 
TreeNode *delete_node(TreeNode *root, element key)
{
	if (root == NULL) 
        return root;

	// 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
	else if (compare(key, root->key)<0)
		root->left = delete_node(root->left, key);
	// 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
	else if (compare(key, root->key)>0)
		root->right = delete_node(root->right, key);
	// 키가 루트와 같으면 이 노드를 삭제하면 됨
	else 
	{
		// 첫 번째나 두 번째 경우
		if (root->left == NULL) 
		{
			TreeNode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) 
		{
			TreeNode *temp = root->left;
			free(root);
			return temp;
		}
		// 세 번째 경우
		TreeNode *temp = max_value_node(root->right);

		// 중외 순회시 후계 노드를 복사한다. 
		root->key = temp->key;
		// 중외 순회시 후계 노드를 삭제한다. 
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

//
void help()
{
	printf("\ninsert(i), search(s), print(p), delete(d), quit(q): ");
}

// 이진 탐색 트리를 사용하는 영어 사전 프로그램 
int main(void)
{
	char command;
	element e;
	TreeNode *root = NULL;
	TreeNode *tmp;

	do {
		help();
		command = getchar();
		getchar();		// 엔터키 제거
		switch (command) {
		case 'i':
			printf("name:");
			gets(e.word);
			printf("phone-number:");
			gets(e.meaning);
			root = insert_node(root, e);
			break;
		case 'd':
			printf("name:");
			gets(e.word);
			root=delete_node(root, e);
			break;
		case 'p':
			display(root);
			printf("\n");
			break;
		case 's':
			printf("name:");
			gets(e.word);
			tmp = search(root, e);
			if (tmp != NULL)
				printf("%s's phone-number:%s\n", tmp->key.word, tmp->key.meaning);
			break;
		case 'q':
			quit();
		}

	} while (command != 'q');
	
	return 0;
}