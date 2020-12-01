#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#pragma warning(disable: 4996)

// Prim-Jarnik 알고리즘 : 인접리스트로 구현.

typedef struct vertex
{
	int name;
	int distance;
	struct edge* parent;
	struct incidence* v_inc;
}vertex;

typedef struct edge
{
	int weight;
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

void insertIncidence(incidence* inc, edge* new_e)
{
	incidence* new_inc = (incidence*)malloc(sizeof(incidence));
	new_inc->inc_edge = new_e;

	if (inc->inc_next == NULL)
		new_inc->inc_next = NULL;
	else
		new_inc->inc_next = inc->inc_next;

	inc->inc_next = new_inc;
}

void connect_VEI(edge* new_e, int o_name, int d_name)
{
	insertIncidence(G.v_arr[o_name - 1].v_inc, new_e);
	insertIncidence(G.v_arr[d_name - 1].v_inc, new_e);
}

void Q_selection_sort(int* queue, int new_n)
{
	int maxind;
	int temp;
	for (int i = 0; i < new_n; i++)
	{
		maxind = 0;
		for (int j = 0; j < new_n - i; j++)
		{
			int a = queue[maxind];
			int b = queue[j];
			// 큐는 정점 인덱스만 담고있으니 정점의 dis 불러와서 비교
			if (G.v_arr[a].distance < G.v_arr[b].distance)
				maxind = j;
		}
		temp = queue[new_n - i - 1];
		queue[new_n - i - 1] = queue[maxind];
		queue[maxind] = temp;
	}
}

void Prim_Jarnik_MST()
{
	int sum = 0;	// 가중치의 합

	// 시작 정점을 1로 지정
	G.v_arr[0].distance = 0;
	// 정점 인덱스를 담는 큐 생성
	int* queue = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		queue[i] = i;
	int q_last_index = n-1;

	// 정점 distance 기준으로 오름차순 정렬
	Q_selection_sort(queue, q_last_index+1);
	
	// 큐가 빌 때까지 
	while (queue[0] != -1)
	{
		// deque
		vertex* u = &(G.v_arr[queue[0]]);
		printf(" %d", u->name);
		sum += u->distance;

		// deque 후 한칸씩 좌로 이동
		for (int i = 0; i < q_last_index; i++)
			queue[i] = queue[i + 1];
		queue[q_last_index] = -1;
		q_last_index--;

		// 정점 u의 인접정점 검사
		incidence* temp = u->v_inc->inc_next;
		while (temp != NULL)
		{
			// 인접 정점인덱스 찾기..
			int z_index;
			if (u->name == temp->inc_edge->o_name)
				z_index = temp->inc_edge->d_name - 1;
			else if(u->name == temp->inc_edge->d_name)
				z_index = temp->inc_edge->o_name - 1;

			// 큐에 해당 인접 정점 있는지 검사하기
			int sign = 0;
			for (int i = 0; i < n; i++)
			{
				if (z_index == queue[i])
				{
					sign = 1;
					break;
				}
			}
			// 정점이랑 간선!
			vertex* z = &(G.v_arr[z_index]);
			edge* e = temp->inc_edge;

			// 큐에 해당 인접 정점이 남아있고, 해당 정점의 dis가 간선 가중치보다 크다면?
			if (sign == 1 && e->weight < z->distance)
			{
				// dis와 parent 변경후 재정렬
				z->distance = e->weight;
				z->parent = e;
				Q_selection_sort(queue, q_last_index+1);
			}
			temp = temp->inc_next;
		}
	}
	printf("\n%d", sum);
}

void main()
{
	scanf("%d %d", &n, &m);

	// n개 정점배열 할당 + 초기화
	G.v_arr = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++)
	{
		G.v_arr[i].name = i + 1;
		G.v_arr[i].distance = INT_MAX;		// 최대값으로 초기화.
		G.v_arr[i].parent = NULL;
		G.v_arr[i].v_inc = (incidence*)malloc(sizeof(incidence));
		G.v_arr[i].v_inc->inc_edge = NULL;
		G.v_arr[i].v_inc->inc_next = NULL;
	}
	// m개 간선배열 할당+초기화
	G.e_arr = (edge*)malloc(sizeof(edge) * m);
	for (int i = 0; i < m; i++)
	{
		int o_name, d_name, weight;
		scanf("%d %d %d", &o_name, &d_name, &weight);
		G.e_arr[i].o_name = o_name;
		G.e_arr[i].d_name = d_name;
		G.e_arr[i].weight = weight;
		connect_VEI(&(G.e_arr[i]), o_name, d_name);
	}
	// 최소신장트리 생성하기
	Prim_Jarnik_MST();
}