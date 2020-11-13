#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct vertex
{
	int name;
}vertex;

typedef struct edge
{
	int weight;
	struct vertex* origin;
	struct vertex* destination;
}edge;

typedef struct graph
{
	struct vertex v[6];
}graph;

edge* a_Matrix[6][6];	// �������

graph G;
int n = 6;	//���� ��

void insertVE(int name1, int name2, int weight)
{
	// �ش� ������ ������� �ε���
	int index1 = name1 - 1;
	int index2 = name2 - 1;
	// �̸��� �ε����� �´� ���� �ҷ��ͼ� �����ͷ� ��ȯ
	vertex* v1 = &(G.v[index1]);
	vertex* v2 = &(G.v[index2]);

	// ����-���� �����ϱ�
	edge* new_e = (edge*)malloc(sizeof(edge));
	new_e->weight = weight;
	new_e->origin = v1;
	new_e->destination = v2;

	// ���� ��İ� ���� ����
	// �밢������ ��Ī�� �ǰ� �ִ´�
	a_Matrix[index1][index2] = new_e;
	a_Matrix[index2][index1] = new_e;
	return;
}

void modifyGraph(int name1, int name2, int weight)
{
	// �Է¹��� name�� ���� �迭�� �����ϴ°�?
	// ���� �迭 �� �˻��Ѵ�,
	int a = NULL, b = NULL;
	for (int i = 0; i < n; i++)
	{
		if (G.v[i].name == name1)
			a = G.v[i].name;
		if (G.v[i].name == name2)
			b = G.v[i].name;
	}
	// 1. ���� �ϳ��� ������ϸ�?
	if (a == NULL || b == NULL)
	{
		printf("-1\n");
		return;
	}
	// �ش� ������ ������� �ε���
	int index1 = name1 - 1;
	int index2 = name2 - 1;

	// 2. ����� �ϴµ� �־��� w = 0 �̶��? --> ���� ���� ����
	if (weight == 0)
	{
		//��������
		free(a_Matrix[index1][index2]);
		//������� �ٲ��ֱ�
		a_Matrix[index1][index2] = NULL;
		a_Matrix[index2][index1] = NULL;
		return;
	}

	// 3. �� ������ ������ �ִٸ�? --> ����ġ ����
	if (a_Matrix[index1][index2] != NULL)
	{
		a_Matrix[index1][index2]->weight = weight;
		return;
	}

	// 4. ���ٸ�? -> �� ���� ���� �̾��ֱ�
	insertVE(name1, name2, weight);
}

void searchVertex(int name)
{
	for (int i = 0; i < n; i++)
	{
		// �Է¹��� ������ �����Ѵٸ�
		if (G.v[i].name == name)
		{
			// ��������� �� ����������(�� ���� �� ���� ������)
			for (int i = 0; i < n; i++)
			{
				edge* e = a_Matrix[name - 1][i];

				if (e != NULL)
					printf(" %d %d", i + 1, e->weight);
			}
			printf("\n");
			return;
		}
	}
	// �� ���Ҵµ� ����?
	printf("-1\n");
	return;
}

void main()
{
	for (int i = 0; i < n; i++)
	{
		// �׷��� G�� ���� �迭�� �̸� �־��ֱ�
		G.v[i].name = i + 1;
		for (int j = 0; j < n; j++)
		{
			// ������� �ΰ����� �ʱ�ȭ
			a_Matrix[i][j] = NULL;
		}
	}
	insertVE(1, 2, 1);
	insertVE(1, 3, 1);
	insertVE(1, 4, 1);
	insertVE(1, 6, 2);
	insertVE(2, 3, 1);
	insertVE(3, 5, 4);
	insertVE(5, 5, 4);
	insertVE(5, 6, 3);

	char c;
	int name, name1, name2, weight;
	while (1)
	{
		scanf("%c", &c);
		if (c == 'q')
			break;
		switch (c)
		{
		case 'a':
			scanf("%d", &name);
			searchVertex(name);
			break;
		case 'm':
			scanf("%d %d %d", &name1, &name2, &weight);
			modifyGraph(name1, name2, weight);
			break;
		}
	}
}