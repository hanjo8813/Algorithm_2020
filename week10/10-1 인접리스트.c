#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct vertex
{
	int name;
	struct incidence* v_inc;
}vertex;

typedef struct edge
{
	int weight;
	struct vertex* origin;
	struct vertex* destination;
}edge;

typedef struct incidence
{
	struct edge* inc_edge;
	struct incidence* inc_next;
}incidence;

typedef struct graph
{
	struct vertex v[6];
}graph;

graph G;
int n = 6;	//정점 수

void insertIncidence(vertex* v1, vertex* v2, edge* e)
{
	incidence* new_i = (incidence*)malloc(sizeof(incidence));
	new_i->inc_edge = e;
	new_i->inc_next = NULL;

	incidence* pre_temp = NULL;
	incidence* temp = v1->v_inc;

	// v2가 연결된 간선 e를 가리키는 노드를 v1의 인접리스트에 추가하는게 목적
	// 1. v1 정점의 인접리스트를 가져와서 순회한다
	// 2. 인접리스트가 가리키는 간선들을 검사하면 v1정점과 연결된 다른 정점 정보를 알수있음
	// 3. 그 정점 정보를 v2와 비교한다 --> v2가 더 작다면 그 노드 전에 삽입하기.
	// 4. 그러면 v1과 연결된 정점의 오름차순으로 인접리스트가 생성된다!
	while (1)
	{
		if (pre_temp != NULL)
		{
			int new_v = v2->name;
			int my_v;
			if (v1->name == temp->inc_edge->destination->name)
			{
				my_v = temp->inc_edge->origin->name;
			}
			else if (v1->name == temp->inc_edge->origin->name)
			{
				my_v = temp->inc_edge->destination->name;
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

void insertVE(int name1, int name2, int weight)
{
	// 이름에 맞는 정점 불러와서 포인터로 변환
	vertex* v1 = &(G.v[name1 - 1]);
	vertex* v2 = &(G.v[name2 - 1]);

	// 간선-정점 연결하기
	edge* new_e = (edge*)malloc(sizeof(edge));
	new_e->weight = weight;
	new_e->origin = v1;
	new_e->destination = v2;

	// 인접 리스트 연결
	insertIncidence(v1, v2, new_e);
	// 루프가 아닌경우
	if (v1 != v2)
		insertIncidence(v2, v1, new_e);
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

	// 둘중 하나라도 존재안하면?
	if (a == NULL || b == NULL)
	{
		printf("-1\n");
		return;
	}

	// 존재는 하는데 가중치 0 이라면? --> 연결 간선 삭제
	if (weight == 0)
	{
		incidence* temp1 = G.v[name1 - 1].v_inc->inc_next;
		incidence* pre_temp1 = G.v[name1 - 1].v_inc;

		if (a == b)
		{
			while (temp1 != NULL)
			{
				if (name1 == temp1->inc_edge->destination->name &&
					name1 == temp1->inc_edge->origin->name)
				{
					free(temp1->inc_edge);
					pre_temp1->inc_next = temp1->inc_next;
					free(temp1);
					return;
				}
				pre_temp1 = temp1;
				temp1 = temp1->inc_next;
			}
		}

		else {
			while (temp1 != NULL)
			{
				incidence* temp2 = G.v[name2 - 1].v_inc->inc_next;
				incidence* pre_temp2 = G.v[name2 - 1].v_inc;
				while (temp2 != NULL)
				{
					// name1의 간선 노드와 name2의 간선 노드가 같다?
					if (temp1->inc_edge == temp2->inc_edge)
					{
						free(temp1->inc_edge);
						pre_temp1->inc_next = temp1->inc_next;
						pre_temp2->inc_next = temp2->inc_next;
						free(temp1);
						free(temp2);
						return;
					}
					pre_temp2 = temp2;
					temp2 = temp2->inc_next;
				}
				pre_temp1 = temp1;
				temp1 = temp1->inc_next;
			}
			return;
		}
	}

	// 두 정점의 간선이 있다면? -> 가중치 변경
	if (a == b)
	{
		incidence* temp1 = G.v[name1 - 1].v_inc->inc_next;
		while (temp1 != NULL)
		{
			if (name1 == temp1->inc_edge->destination->name &&
				name1 == temp1->inc_edge->origin->name)
			{
				temp1->inc_edge->weight = weight;
				return;
			}
			temp1 = temp1->inc_next;
		}
	}
	else
	{
		incidence* temp1 = G.v[name1 - 1].v_inc->inc_next;
		while (temp1 != NULL)
		{
			incidence* temp2 = G.v[name2 - 1].v_inc->inc_next;
			while (temp2 != NULL)
			{
				if (temp1->inc_edge == temp2->inc_edge)
				{
					temp1->inc_edge->weight = weight;
					return;
				}
				temp2 = temp2->inc_next;
			}
			temp1 = temp1->inc_next;
		}
	}
	// 없다면? -> 두 정점 간선 이어주기
	insertVE(name1, name2, weight);
}

void searchVertex(int name)
{
	for (int i = 0; i < n; i++)
	{
		// 정점이 존재할때
		if (G.v[i].name == name)
		{
			// 해당 정점의 incidence 리스트를 다 돌려본다
			incidence* temp = G.v[i].v_inc->inc_next;
			while (temp != NULL)
			{
				// incidence 리스트가 가리키는 간선은 origin과 destination을 가진다
				// 해당 정점이 origin일 경우 -> 인접 정점은 des
				if (&(G.v[i]) == temp->inc_edge->origin)
				{
					printf(" %d", temp->inc_edge->destination->name);
					printf(" %d", temp->inc_edge->weight);
				}
				// 해당 정점이 des일 경우 -> 인접 정점은 origin
				else if (&(G.v[i]) == temp->inc_edge->destination)
				{
					printf(" %d", temp->inc_edge->origin->name);
					printf(" %d", temp->inc_edge->weight);
				}
				temp = temp->inc_next;
			}
			printf("\n");
			return;
		}
	}
	// 다 돌렸는데 정점 존재 X
	printf("-1\n");
	return;
}

void main()
{
	// 그래프 G의 정점 배열에 값 채워넣기
	for (int i = 0; i < n; i++)
	{
		G.v[i].name = i + 1;
		G.v[i].v_inc = (incidence*)malloc(sizeof(incidence));
		G.v[i].v_inc->inc_edge = NULL;
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