#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct vertex
{
	int name;
	int v_visit;
	struct incidence* v_inc;
}vertex;

typedef struct edge
{
	int e_visit;
	int o_name;
	int d_name;
}edge;

typedef struct incidence
{
	struct edge* inc_edge;
	struct incidence* inc_next;
}incidence;

typedef struct graph
{
	struct vertex* v_arr;
	struct edge* e_arr;
}graph;

graph G;
int n;	//정점 수
int m;	//간선 수	
int s;	//순회 시작 정점
int last_index = 0;

void init_Graph()
{
	// n개의 정점 배열 선언/초기화 + 정점당 인접리스트 동적할당 및 초기화
	G.v_arr = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++)
	{
		G.v_arr[i].name = i + 1;
		G.v_arr[i].v_visit = NULL;
		G.v_arr[i].v_inc = (incidence*)malloc(sizeof(incidence));
		G.v_arr[i].v_inc->inc_edge = NULL;
		G.v_arr[i].v_inc->inc_next = NULL;
	}
	// m개의 정점 배열 선언/초기화
	G.e_arr = (edge*)malloc(sizeof(edge) * m);
	for (int i = 0; i < m; i++)
	{
		G.e_arr[i].e_visit = NULL;
		G.e_arr[i].o_name = NULL;
		G.e_arr[i].d_name = NULL;
	}
}

void insertIncidence(vertex* v1, vertex* v2, edge* e)
{
	incidence* new_i = (incidence*)malloc(sizeof(incidence));
	new_i->inc_edge = e;
	new_i->inc_next = NULL;

	incidence* pre_temp = NULL;
	incidence* temp = v1->v_inc;

	while (1)
	{
		if (pre_temp != NULL)
		{
			int new_v = v2->name;
			int my_v;
			if (v1->name == temp->inc_edge->d_name)
			{
				my_v = temp->inc_edge->o_name;
			}
			else if (v1->name == temp->inc_edge->o_name)
			{
				my_v = temp->inc_edge->d_name;
			}
			if (new_v < my_v)
			{
				temp = pre_temp;
				break;
			}
		}
		if (temp->inc_next == NULL)
			break;
		pre_temp = temp;
		temp = temp->inc_next;
	}
	if (temp->inc_next == NULL)
	{
		temp->inc_next = new_i;
		return;
	}
	else
	{
		new_i->inc_next = temp->inc_next;
		temp->inc_next = new_i;
		return;
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

	// 정점-인접리스트-간선 연결
	insertIncidence(v1, v2, new_e);
	insertIncidence(v2, v1, new_e);

	// 간선 배열의 마지막 인덱스를 한칸 옮긴다
	last_index++;
}

void DFS(int name)
{
	int index = name - 1;
	// 해당 정점을 이미 방문했다면
	if (G.v_arr[index].v_visit != NULL)
		return;
	// 첫 방문이라면 방문표시해주고 해당 정점 출력
	G.v_arr[index].v_visit = 1;
	printf("%d\n", G.v_arr[index].name);

	// 해당 정점의 모든 인접리스트를 순회한다.
	incidence* temp = G.v_arr[index].v_inc->inc_next;
	while (temp != NULL)
	{
		int next_name;	// 인접 정점
		// incidence 리스트가 가리키는 간선은 origin과 destination을 가진다
		// 해당 정점이 origin일 경우 -> 인접 정점은 des
		if (G.v_arr[index].name == temp->inc_edge->o_name)
		{
			next_name = temp->inc_edge->d_name;
		}
		else if (G.v_arr[index].name == temp->inc_edge->d_name)
		{
			next_name = temp->inc_edge->o_name;
		}
		// 다음으로 갈 인접정점이 첫 방문이라면?
		if (G.v_arr[next_name - 1].v_visit == NULL)
		{
			// 간선에 1 부여, 즉 Tree 간선이 됨.
			temp->inc_edge->e_visit = 1;
			DFS(next_name);
		}
		// 재방문이라면?
		else
		{
			// 간선에 2 부여, 즉 Back 간선이 됨.
			temp->inc_edge->e_visit = 2;
		}
		temp = temp->inc_next;
	}
	return;
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

	// 깊이우선탐색
	DFS(s);
}