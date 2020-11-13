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

edge* a_Matrix[6][6];	// 인접행렬

graph G;
int n = 6;	//정점 수

void insertVE(int name1, int name2, int weight)
{
	// 해당 정점의 인접행렬 인덱스
	int index1 = name1 - 1;
	int index2 = name2 - 1;
	// 이름의 인덱스에 맞는 정점 불러와서 포인터로 변환
	vertex* v1 = &(G.v[index1]);
	vertex* v2 = &(G.v[index2]);

	// 간선-정점 연결하기
	edge* new_e = (edge*)malloc(sizeof(edge));
	new_e->weight = weight;
	new_e->origin = v1;
	new_e->destination = v2;

	// 인접 행렬과 간선 연결
	// 대각선으로 대칭이 되게 넣는다
	a_Matrix[index1][index2] = new_e;
	a_Matrix[index2][index1] = new_e;
	return;
}

void modifyGraph(int name1, int name2, int weight)
{
	// 입력받은 name이 정점 배열에 존재하는가?
	// 정점 배열 다 검사한다,
	int a = NULL, b = NULL;
	for (int i = 0; i < n; i++)
	{
		if (G.v[i].name == name1)
			a = G.v[i].name;
		if (G.v[i].name == name2)
			b = G.v[i].name;
	}
	// 1. 둘중 하나라도 존재안하면?
	if (a == NULL || b == NULL)
	{
		printf("-1\n");
		return;
	}
	// 해당 정점의 인접행렬 인덱스
	int index1 = name1 - 1;
	int index2 = name2 - 1;

	// 2. 존재는 하는데 주어진 w = 0 이라면? --> 연결 간선 삭제
	if (weight == 0)
	{
		//간선삭제
		free(a_Matrix[index1][index2]);
		//인접행렬 바꿔주기
		a_Matrix[index1][index2] = NULL;
		a_Matrix[index2][index1] = NULL;
		return;
	}

	// 3. 두 정점의 간선이 있다면? --> 가중치 변경
	if (a_Matrix[index1][index2] != NULL)
	{
		a_Matrix[index1][index2]->weight = weight;
		return;
	}

	// 4. 없다면? -> 두 정점 간선 이어주기
	insertVE(name1, name2, weight);
}

void searchVertex(int name)
{
	for (int i = 0; i < n; i++)
	{
		// 입력받은 정점이 존재한다면
		if (G.v[i].name == name)
		{
			// 인접행렬을 다 돌려버린다(행 고정 후 열만 돌리기)
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
	// 다 돌았는데 없다?
	printf("-1\n");
	return;
}

void main()
{
	for (int i = 0; i < n; i++)
	{
		// 그래프 G의 정점 배열에 이름 넣어주기
		G.v[i].name = i + 1;
		for (int j = 0; j < n; j++)
		{
			// 인접행렬 널값으로 초기화
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