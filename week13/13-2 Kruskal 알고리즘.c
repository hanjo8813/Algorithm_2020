#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#pragma warning(disable: 4996)

// Kruskal 알고리즘 : 인접리스트로 구현.

typedef struct vertex
{
	int name;
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

typedef struct Sack
{
	int s_index;
	struct Sack* s_next;
}Sack;

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

void arr_selection_sort(int* arr)
{
	int maxind;
	int temp;
	for (int i = 0; i < m; i++)
	{
		maxind = 0;
		for (int j = 0; j < m - i; j++)
		{
			int a = arr[maxind];
			int b = arr[j];
			// 배열은 정점 인덱스만 담고있으니 간선 가중치를 불러와서 비교
			if (G.e_arr[a].weight < G.e_arr[b].weight)
				maxind = j;
		}
		temp = arr[m - i - 1];
		arr[m - i - 1] = arr[maxind];
		arr[maxind] = temp;
	}
}

void Kruskal_MST()
{
	int sum = 0;	// 가중치의 합
	int e_num = 0;	// 추가된 간선의 수

	// 정점 인덱스 당 Sack(배낭) 구조체 '주소' 배열 초기화
	Sack** s_arr = (Sack**)malloc(sizeof(Sack*) * n);
	for (int i = 0; i < n; i++)
	{
		s_arr[i] = malloc(sizeof(Sack) * n);
		s_arr[i]->s_index = i;
		s_arr[i]->s_next = NULL;
	}
	// 간선 인덱스를 담는 배열 생성
	int* arr = malloc(sizeof(int) * m);
	for (int i = 0; i < m; i++)
		arr[i] = i;

	// 가중치를 기준으로 정렬
	arr_selection_sort(arr);

	// 가중치 낮은 간선부터 순회
	for (int i = 0; i < m; i++)
	{
		if (e_num == n - 1)
			break;

		edge e = G.e_arr[arr[i]];
		int o_index = e.o_name-1;
		int d_index = e.d_name-1;

		// 두 정점의 Sack이 다르다면 (묶여있지 않다면)
		if (s_arr[o_index] != s_arr[d_index])
		{
			// 해당 간선의 가중치를 더해주고
			printf(" %d", e.weight);
			sum += e.weight;
			e_num++;

			// o sack 뒤에다가 d sack 붙여서 일단 합치기
			Sack* temp = s_arr[o_index];
			while (1)
			{
				if (temp->s_next == NULL)
					break;
				temp = temp->s_next;
			}
			temp->s_next = s_arr[d_index];

			// new_s(합쳐진 sack)의 포함 정점 sack이 모두 new_s를 가리키게 한다.
			Sack* new_s = s_arr[o_index];
			temp = new_s;
			while (1)
			{
				s_arr[temp->s_index] = new_s;
				if (temp->s_next == NULL)
					break;
				temp = temp->s_next;
			}
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
	Kruskal_MST();
}