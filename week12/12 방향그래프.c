#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct vertex
{
	char name;
	int inDegree;	//진입차수
	struct incidence* outEdges;
	struct incidence* inEdges;
}vertex;

typedef struct edge
{
	int o_index;
	int d_index;
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
int n;	//정점수
int m;	//간선수

int index(char c_name)
{
	for (int i = 0; i < n; i++)
	{
		if (c_name == G.v_arr[i].name)
			return i;
	}
}

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

void connect_VEI(edge* new_e, int o_index, int d_index)
{
	// origin 정점에 진출 인접리스트 추가
	insertIncidence(G.v_arr[o_index].outEdges, new_e);

	// destination 정점에 진입 인접리스트 추가
	insertIncidence(G.v_arr[d_index].inEdges, new_e);
	G.v_arr[d_index].inDegree += 1;	// 진입 차수 +1
}

void topologicalSort()
{
	// 정점배열의 인덱스를 담을 큐 생성
	int* queue = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		queue[i] = -1;
	int q_last_index = 0;
	// 정점 배열을 돌려서 인접차수가 0인 정점인덱스를 큐에 저장.
	for (int i = 0; i < n; i++)
	{
		if (G.v_arr[i].inDegree == 0)
		{
			// enqueue
			queue[q_last_index] = i;
			q_last_index++;
		}
	}
	// 위상 순위대로 정점이름을 담을 배열 생성
	int t = 0;
	char* degree_rank = malloc(sizeof(char) * n);
	
	while (queue[0] != -1)
	{
		vertex* u = &(G.v_arr[queue[0]]);
		// dequeue
		for (int i = 0; i < q_last_index; i++)
		{
			queue[i] = queue[i + 1];
		}
		q_last_index--;

		// 해당 위상순위에 해당하는 정점이름 저장
		degree_rank[t] = u->name;
		t++;

		// 주인공 정점의 인접 정점을 모두 순회
		incidence* temp = u->outEdges->inc_next;
		while (temp!=NULL)
		{
			int w_index = temp->inc_edge->d_index;
			// 다음 검사할 정점의 주소
			vertex* w = &(G.v_arr[w_index]);
			// 진입차수를 -1 한다.
			w->inDegree -= 1;
			// 다음 정점의 진입차수가 0이라면? -> enqueue
			if(w->inDegree == 0)
			{
				queue[q_last_index] = w_index;
				q_last_index++;
			}
			temp = temp->inc_next;
		}
	}

	if (t < n)
		printf("0\n");
	else
	{
		for (int i = 0; i < t; i++)
			printf("%c ", degree_rank[i]);
	}
}

void main()
{
	char v_name, o_name, d_name;
	// n개 정점 배열 생성/초기화
	scanf("%d", &n);
	getchar();
	G.v_arr = (vertex*)malloc(sizeof(vertex) * n);
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &v_name);
		getchar();
		G.v_arr[i].name = v_name;
		G.v_arr[i].inDegree = 0;
		G.v_arr[i].inEdges = (incidence*)malloc(sizeof(incidence));
		G.v_arr[i].inEdges->inc_edge = NULL;
		G.v_arr[i].inEdges->inc_next = NULL;
		G.v_arr[i].outEdges = (incidence*)malloc(sizeof(incidence));
		G.v_arr[i].outEdges->inc_edge = NULL;
		G.v_arr[i].outEdges->inc_next = NULL;
	}
	// m개 간선 배열 생성 
	scanf("%d", &m);
	getchar();
	G.e_arr = (edge*)malloc(sizeof(edge) * m);
	for (int i = 0; i < m; i++)
	{
		scanf("%c %c", &o_name, &d_name);
		getchar();
		int o_index = index(o_name);
		int d_index = index(d_name);
		G.e_arr[i].o_index = o_index;
		G.e_arr[i].d_index = d_index;
		connect_VEI(&(G.e_arr[i]), o_index, d_index);
	}

	topologicalSort();
}