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
int n = 6;	//���� ��

void insertIncidence(vertex* v1, vertex* v2, edge* e)
{
	incidence* new_i = (incidence*)malloc(sizeof(incidence));
	new_i->inc_edge = e;
	new_i->inc_next = NULL;

	incidence* pre_temp = NULL;
	incidence* temp = v1->v_inc;

	// v2�� ����� ���� e�� ����Ű�� ��带 v1�� ��������Ʈ�� �߰��ϴ°� ����
	// 1. v1 ������ ��������Ʈ�� �����ͼ� ��ȸ�Ѵ�
	// 2. ��������Ʈ�� ����Ű�� �������� �˻��ϸ� v1������ ����� �ٸ� ���� ������ �˼�����
	// 3. �� ���� ������ v2�� ���Ѵ� --> v2�� �� �۴ٸ� �� ��� ���� �����ϱ�.
	// 4. �׷��� v1�� ����� ������ ������������ ��������Ʈ�� �����ȴ�!
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
	// �̸��� �´� ���� �ҷ��ͼ� �����ͷ� ��ȯ
	vertex* v1 = &(G.v[name1 - 1]);
	vertex* v2 = &(G.v[name2 - 1]);

	// ����-���� �����ϱ�
	edge* new_e = (edge*)malloc(sizeof(edge));
	new_e->weight = weight;
	new_e->origin = v1;
	new_e->destination = v2;

	// ���� ����Ʈ ����
	insertIncidence(v1, v2, new_e);
	// ������ �ƴѰ��
	if (v1 != v2)
		insertIncidence(v2, v1, new_e);
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

	// ���� �ϳ��� ������ϸ�?
	if (a == NULL || b == NULL)
	{
		printf("-1\n");
		return;
	}

	// ����� �ϴµ� ����ġ 0 �̶��? --> ���� ���� ����
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
					// name1�� ���� ���� name2�� ���� ��尡 ����?
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

	// �� ������ ������ �ִٸ�? -> ����ġ ����
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
	// ���ٸ�? -> �� ���� ���� �̾��ֱ�
	insertVE(name1, name2, weight);
}

void searchVertex(int name)
{
	for (int i = 0; i < n; i++)
	{
		// ������ �����Ҷ�
		if (G.v[i].name == name)
		{
			// �ش� ������ incidence ����Ʈ�� �� ��������
			incidence* temp = G.v[i].v_inc->inc_next;
			while (temp != NULL)
			{
				// incidence ����Ʈ�� ����Ű�� ������ origin�� destination�� ������
				// �ش� ������ origin�� ��� -> ���� ������ des
				if (&(G.v[i]) == temp->inc_edge->origin)
				{
					printf(" %d", temp->inc_edge->destination->name);
					printf(" %d", temp->inc_edge->weight);
				}
				// �ش� ������ des�� ��� -> ���� ������ origin
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
	// �� ���ȴµ� ���� ���� X
	printf("-1\n");
	return;
}

void main()
{
	// �׷��� G�� ���� �迭�� �� ä���ֱ�
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