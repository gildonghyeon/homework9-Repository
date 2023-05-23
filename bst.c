/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	printf("----2022041025 길동현----\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	// 트리가 비어 있지 않다면, 트리에서 할당된 모든 노드를 제거한다.
	if(*h != NULL)
		freeBST(*h);

	// 헤드 노드를 생성한다.
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	// 루트
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}




void inorderTraversal(Node* ptr)
{
	if(ptr) {
		// 왼쪽 서브트리를 중위 순회한다.
		inorderTraversal(ptr->left);
		// 현재 노드를 출력한다.
		printf(" [%d] ", ptr->key);
		// 오른쪽 서브트리를 중위 순회한다.
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		// 현재 노드를 출력한다.
		printf(" [%d] ", ptr->key);
		// 왼쪽 서브트리를 전위 순회한다.
		preorderTraversal(ptr->left);
		// 오른쪽 서브트리를 전위 순회한다.
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		// 왼쪽 서브트리를 후위 순회한다.
		postorderTraversal(ptr->left);
		// 오른쪽 서브트리를 후위 순회한다.
		postorderTraversal(ptr->right);
		// 현재 노드를 출력한다.
		printf(" [%d] ", ptr->key);
	}
}



int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		// 헤드의 왼쪽 자식이 없으면 새 노드를 연결한다.
		head->left = newNode;
		return 1;
	}

	// head->left는 루트 노드 
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		// 키와 일치하는 노드가 이미 존재하면 그냥 반환한다.
		if(ptr->key == key) return 1;

		// 자식 노드로 이동하며 부모를 parentNode에 저장한다. 
		parentNode = ptr;

		//키 비교, 현재 노드의 키가 입력된 키보다 크면 새 노드는 오른쪽 서브트리에 삽입되어야 한다. 그렇지 않으면 왼쪽 서브트리에 삽입되어야 한다.
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	//새 노드를 부모에 연결한다 
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	// head->left는 루트 노드
	Node* ptr = head->left;


	// 자식 노드로 이동하며 부모를 parentNode에 저장한다 
	Node* parentNode = head;

	while(ptr != NULL) {

		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {

				// 루트 노드인 경우 
				if(parentNode == head)
					head->left = NULL;

				// 왼쪽 노드인 경우 또는 오른쪽 노드인 경우 
				if(parentNode->left == ptr)
					parentNode->left = NULL; 
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		// 부모 노드를 유지한다
		parentNode = ptr;

		// 키 비교, 현재 노드의 키가 입력된 키보다 크면 오른쪽 서브트리로 이동해야 하고 그렇지 않으면 왼쪽 서브트리로 이동해야 한다.
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	printf("the node [%d] is not a leaf \n", key);

	return 1;
}


Node* searchRecursive(Node* ptr, int key)
{
	// 만약 ptr가 NULL이면 탐색 실패, NULL 반환
	if(ptr == NULL)
		return NULL;

	// ptr의 키 값과 찾고자 하는 key를 비교하여 이동
	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);

	// 만약 ptr의 키 값이 key와 같다면 해당 노드 반환
	return ptr;
}

Node* searchIterative(Node* head, int key)
{
	// 루트 노드
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		// ptr의 키 값과 찾고자 하는 key를 비교
		if(ptr->key == key)
			return ptr;

		// key가 현재 노드의 키 값보다 크면 오른쪽으로 이동, 작으면 왼쪽으로 이동
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	// 탐색 실패, NULL 반환
	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		// 왼쪽 서브트리 해제
		freeNode(ptr->left);
		// 오른쪽 서브트리 해제
		freeNode(ptr->right);
		// 노드 해제
		free(ptr);
	}
}

int freeBST(Node* head)
{
	// 트리가 비어있는 경우, head 노드만 해제하고 반환
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	// 루트 노드
	Node* p = head->left;

	// 모든 노드 해제
	freeNode(p);

	// 헤드 노드 해제
	free(head);
	return 1;
}





