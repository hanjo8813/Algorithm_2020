#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

int H[100];
int n = 0;	//배열의 마지막 유효 인덱스

void insertitem();
void upHeap();
void downHeap();
void printHeap();
void BuildHeap();
void inPlaceHeapSort();

void main()
{
	int size;
	int key;
	scanf("%d", &size);

	for (int i = 1; i <= size; i++)
	{
		scanf("%d", &key);
		insertitem(key);
	}
	inPlaceHeapSort();
	printHeap(size);
}

void inPlaceHeapSort()
{
	int temp;
	for (int i = n; i >= 1; i--)
	{
		temp = H[1];
		H[1] = H[n];
		H[n] = temp;
		n--;
		BuildHeap();
	}
}

void insertitem(int key)
{
	n = n + 1;
	H[n] = key;
	upHeap(n);
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

void BuildHeap()
{
	for (int i = n / 2; i > 0; i--)
		downHeap(i);
}

void downHeap(int i)
{
	int greater;
	int temp;

	if (2 * i > n)
		return;
	greater = 2 * i;
	if (greater + 1 <= n)
		if (H[greater] < H[greater + 1])
			greater++;
	if (H[i] >= H[greater])
		return;
	temp = H[i];
	H[i] = H[greater];
	H[greater] = temp;

	downHeap(greater);
}

void printHeap(int size)
{
	for (int i = 1; i <= size; i++)
		printf(" %d", H[i]);
}