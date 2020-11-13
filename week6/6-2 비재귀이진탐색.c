#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

int* arr;

int FE(int K, int r, int l)
{
	int mid;
	while (1)
	{
		mid = (l + r) / 2;
		if (r > l)
		{
			mid = r;
			break;
		}
		if (arr[mid] == K)
			break;
		else if (arr[mid] < K)
			r = mid + 1;
		else
			l = mid - 1;
	}
	return mid;
}

void main()
{
	int N, K;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int) * N);
	scanf("%d", &K);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", arr + i);
	}
	int index = FE(K, 0, N - 1);
	printf("%d", index);
}
