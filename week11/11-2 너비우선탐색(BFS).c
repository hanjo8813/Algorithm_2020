#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct vertex
{
	int name;
	int v_visit;
}vertex;

typedef struct edge
{
	int e_visit;
	int o_name;
	int d_name;
}edge;

typedef struct graph
{
	struct vertex* v_arr;
	struct edge* e_arr;
}graph;

edge **(*a_Matrix);	// 간선의 포인터를 담을 인접행렬

graph G;
int n;	//정점 수
int m;	//간선 수	
int s;	//순회 시작 정점
int last_index = 0;

void init_Graph()
{
	// n개의 정점 배열 동적할당/초기화
	G.v_arr = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++)
	{
		G.v_arr[i].name = i + 1;
		G.v_arr[i].v_visit = NULL;
	}
	// m개의 정점 배열 동적할당/초기화
	G.e_arr = (edge*)malloc(sizeof(edge) * m);
	for (int i = 0; i < m; i++)
	{
		G.e_arr[i].e_visit = NULL;
		G.e_arr[i].o_name = NULL;
		G.e_arr[i].d_name = NULL;
	}
	// n x n 의 인접행렬 동적할당 / 초기화
	a_Matrix = malloc(sizeof(edge**) * n);
	for (int i = 0; i < n; i++)
	{
		a_Matrix[i] = malloc(sizeof(edge*) * n);
		for (int j = 0; j < n; j++)
		{
			a_Matrix[i][j] = NULL;
		}
	}
}

void insertVE(int name1, int name2)
{
	// 정점-간선을 연결
	G.e_arr[last_index].o_name = name1;
	G.e_arr[last_index].d_name = name2;

	// 연결하려는 정점과 간선의 주소를 불러온다
	int index1 = name1 - 1;
	int index2 = name2 - 1;
	vertex* v1 = &(G.v_arr[index1]);
	vertex* v2 = &(G.v_arr[index2]);
	edge* new_e = &(G.e_arr[last_index]);

	// 인접행렬-간선 연결
	a_Matrix[index1][index2] = new_e;
	a_Matrix[index2][index1] = new_e;

	// 간선 배열의 마지막 인덱스를 한칸 옮긴다
	last_index++;
}

void BFS(int name)
{
	// 입력받은 시작정점 세팅
	int index = name - 1;
	G.v_arr[index].v_visit = 1;

	// 인접 정점을 담는 큐 동적할당과 널로 초기화, 첫번째엔 시작정점.
	int* queue = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		queue[i] = NULL;
	queue[0] = name;
	int q_last_index = 1;

	// 너비우선탐색 시작.
	while (queue[0] != NULL)
	{
		printf("%d\n", queue[0]);
		int my_name = queue[0];
		int my_index = my_name - 1;
		q_last_index--;
		// 큐에서 맨 앞을 뺐을 때 한칸씩 좌로 이동.
		for (int i = 0; i < n; i++)
		{
			if (queue[i] == NULL)
			{
				queue[i - 1] = NULL;
				break;
			}
			queue[i] = queue[i + 1];
		}
		// 큐에서 뺀 정점의 인접 정점을 조사
		for (int j = 0; j < n; j++)
		{
			if (a_Matrix[my_index][j] == NULL)
				continue;
			// 다음 인접 정점.
			int next_name;
			if (my_name == a_Matrix[my_index][j]->d_name)
			{
				next_name = a_Matrix[my_index][j]->o_name;
			}
			else if (my_name == a_Matrix[my_index][j]->o_name)
			{
				next_name = a_Matrix[my_index][j]->d_name;
			}
			// 다음으로 갈 인접정점이 첫 방문이라면?
			if (G.v_arr[next_name - 1].v_visit == NULL)
			{
				// 큐에 해당 인접정점 저장
				queue[q_last_index] = next_name;
				q_last_index++;
				// 정점에 방문표시
				G.v_arr[next_name - 1].v_visit = 1;
				// 간선에 방문표시 (Tree)
				a_Matrix[my_index][j]->e_visit = 1;
				a_Matrix[j][my_index]->e_visit = 1;
			}
			else  // 간선에 방문표시 (Cross)
			{
				a_Matrix[my_index][j]->e_visit = 2;
				a_Matrix[j][my_index]->e_visit = 2;
			}
		}
	}
}

void main()
{
	scanf("%d %d %d", &n, &m, &s);
	init_Graph();

	// 정점과 간선 연결
	for (int i = 0; i < m; i++)
	{
		int name1, name2;
		scanf("%d %d", &name1, &name2);
		insertVE(name1, name2);
	}
	// 너비우선탐색
	BFS(s);
}