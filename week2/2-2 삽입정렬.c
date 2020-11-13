#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable: 4996)

// »ðÀÔÁ¤·Ä
void insertion_sort(int* pB, int psize)
{
	int minind;
	int i, j;
	int temp;

	for (i = 1; i < psize; i++)
	{
		temp = pB[i];

		j = i - 1;
		while ((j >= 0) && (pB[j] > temp))
		{
			pB[j + 1] = pB[j];
			j = j - 1;
		}
		pB[j + 1] = temp;
	}
}

void main()
{
	int size;
	int* A = NULL;
	int i;

	scanf("%d", &size);
	A = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++)
		scanf("%d", A + i);

	insertion_sort(A, size);

	for (i = 0; i < size; i++)
		printf(" %d", A[i]);
}