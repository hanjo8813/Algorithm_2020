#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

typedef struct Node {
	int data;
	struct Node* next;
}Node;

Node* merge(Node* L1, Node* L2)
{
	Node* p, * list;

	if (L1->data < L2->data)
	{
		p = L1;
		L1 = L1->next;
	}
	else
	{
		p = L2;
		L2 = L2->next;
	}

	list = p;

	while (L1 != NULL && L2 != NULL)
	{
		if (L1->data < L2->data)
		{
			p->next = L1;
			L1 = L1->next;
		}
		else
		{
			p->next = L2;
			L2 = L2->next;
		}
		p = p->next;
	}
	if (L1 != NULL)
		p->next = L1;
	else
		p->next = L2;

	return list;
}

Node* mg_partition(Node* list, int k)
{
	Node* L2;
	for (int i = 0; i < k - 1; i++)
	{
		list = list->next;
	}
	L2 = list->next;
	list->next = NULL;
	return L2;
}

Node* mergeSort(Node* list, int N)
{
	if (N == 1)
		return list;
	int k = N / 2;

	// 리스트 분할
	Node* L1, * L2;
	L1 = list;
	L2 = mg_partition(list, k);
	// 재귀로
	L1 = mergeSort(L1, k);
	L2 = mergeSort(L2, N - k);
	// 통치-합병
	return merge(L1, L2);
}

void main()
{
	int N;
	Node* p, * list;
	list = (Node*)malloc(sizeof(Node));
	p = list;

	scanf("%d", &N);
	for (int i = 0; i < N;i++)
	{
		scanf("%d", &p->data);
		if (i == N - 1)
		{
			p->next = NULL;
			break;
		}
		p->next = malloc(sizeof(Node));
		p = p->next;
	}

	list = mergeSort(list, N);

	for (int i = 0; i < N; i++)
	{
		printf("%d ", list->data);
		list = list->next;
	}
}
