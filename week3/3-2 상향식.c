#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

int H[100];
int n = 0;	//배열의 마지막 유효 인덱스

void downHeap(int i);
void printHeap();
void BuildHeap();
void rBuildHeap();

void main()
{
	scanf("%d", &n);

	for (int i = 1; i <= n; i++)
	{
		scanf("%d", H + i);
	}

	for (int i = 1; i <= n; i++)
	{
		rBuildHeap(i);
	}
	printHeap();

}

void rBuildHeap(int i)
{
	if (i > n)
		return;
	rBuildHeap(2 * i);
	rBuildHeap(2 * i + 1);
	downHeap(i);
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

void printHeap()
{
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", H[i]);
	}
	printf("\n");
}