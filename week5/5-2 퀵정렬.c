#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

int* arr;

int mid(int a, int b, int c)
{
	if (a >= b)
	{
		if (b >= c)
			return b;
		else if (a <= c)
			return a;
		else
			return c;
	}
	else if (a >= c)
		return a;
	else if (b >= c)
		return c;
	else
		return b;
}

void inPlaceQuickSort(int* arr, int l, int r)
{
	if (l >= r)
		return;
	int pivot = inPlacePartition(arr, l, r);
	inPlaceQuickSort(arr, l, pivot - 1);
	inPlaceQuickSort(arr, pivot + 1, r);
}

int inPlacePartition(int* arr, int l, int r)
{
	// r-l ������ ������ �� ���� �� �߾Ӱ� ���ϱ�.
	srand(time(NULL));
	int a = rand() % (r - l + 1) + l;
	int b = rand() % (r - l + 1) + l;
	int c = rand() % (r - l + 1) + l;
	int pivot_index = mid(a, b, c);
	int pivot = arr[pivot_index];
	int temp;

	// pivot �ε��� ���� �迭�� �� �ڷ� ����.
	temp = arr[r];
	arr[r] = arr[pivot_index];
	arr[pivot_index] = temp;

	// �־��� ������ �迭�� LT-EQ-GT ������ �����Ѵ�.
	int i = l;
	int j = r - 1;
	while (i <= j)
	{
		while (i <= j && arr[i] <= pivot)
			i = i + 1;
		while (j >= i && arr[j] >= pivot)
			j = j - 1;
		if (i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	// �ߺ� pivot�� ���� ���� ������ ��������..
	temp = arr[i];
	arr[i] = arr[r];
	arr[r] = temp;

	return i;
}

void main()
{
	int N;
	scanf("%d", &N);
	arr = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", arr + i);
	}

	inPlaceQuickSort(arr, 0, N - 1);

	for (int i = 0; i < N; i++)
	{
		printf("%d ", arr[i]);
	}
}
