#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

int H[100];
int n = 0;	//배열의 마지막 유효 인덱스

void insertitem(int key);
void removeMax();
void upHeap(int n);
void downHeap();
void printHeap();

void main()
{
	char order;
	int key;

	while (1)
	{
		scanf("%c", &order);

		if (order == 'i')
		{
			scanf("%d", &key);
			insertitem(key);
		}

		else if (order == 'd')
		{
			removeMax();
		}

		else if (order == 'p')
		{
			printHeap();
		}

		else
			break;

		getchar();
	}
}

void insertitem(int key)
{
	n = n + 1;
	H[n] = key;
	upHeap(n);
	printf("0\n");
}

void removeMax()
{
	int temp;
	temp = H[1];
	H[1] = H[n];
	n = n - 1;
	downHeap(1);
	printf("%d\n", temp);
}

void upHeap(int i)
{
	int temp;

	if (i == 1)
		return;

	if (H[i] > H[i / 2])
	{
		temp = H[i / 2];
		H[i / 2] = H[i];
		H[i] = temp;
		upHeap(i / 2);
	}
	else
		return;
}

void downHeap(int i)
{
	int temp;

	if (i * 2 > n)
		return;

	if (H[i * 2] > H[i * 2 + 1])
	{
		temp = H[i];
		H[i] = H[i * 2];
		H[i * 2] = temp;
		downHeap(i * 2);
	}
	else
	{
		temp = H[i];
		H[i] = H[i * 2 + 1];
		H[i * 2 + 1] = temp;
		downHeap(i * 2 + 1);
	}

}

void printHeap()
{
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", H[i]);
	}
	printf("\n");
}