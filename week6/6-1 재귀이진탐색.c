#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

int* arr;

int rFE(int K, int r, int l)
{
	int mid = (l + r) / 2;
	if (r > l)
		return r - 1;

	if (arr[mid] == K)
		return mid;
	else if (arr[mid] < K)
		return rFE(K, mid + 1, l);
	else
		return rFE(K, r, mid - 1);
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
	int index = rFE(K, 0, N - 1);
	printf("%d", index);
}
