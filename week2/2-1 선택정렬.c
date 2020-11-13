#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

void main()
{
	int size;
	int* arr = NULL;
	int maxind;
	int i, j;
	int temp;

	scanf("%d", &size);
	arr = (int*)malloc(size * sizeof(int));

	for (i = 0; i < size; i++)
		scanf("%d", arr + i);

	for (i = 0; i < size; i++)
	{
		maxind = 0;

		for (j = 0; j < size - i; j++)
		{
			if (arr[maxind] < arr[j])
				maxind = j;
		}
		temp = arr[size - i - 1];
		arr[size - i - 1] = arr[maxind];
		arr[maxind] = temp;
	}

	for (i = 0; i < size; i++)
		printf(" %d", arr[i]);

	free(arr);

}