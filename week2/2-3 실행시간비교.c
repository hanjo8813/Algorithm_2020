#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <Windows.h>
#pragma warning(disable: 4996)

// 선택정렬
void selection_sort(int* pA, int psize)
{
	int maxind;
	int i, j;
	int temp;

	for (i = 0; i < psize; i++)
	{
		maxind = 0;

		for (j = 0; j < psize - i; j++)
		{
			if (pA[maxind] < pA[j])
				maxind = j;
		}
		temp = pA[psize - i - 1];
		pA[psize - i - 1] = pA[maxind];
		pA[maxind] = temp;
	}
}

// 삽입정렬
void insertion_sort(int* pB, int psize)
{
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


// 역순정렬
void reverse_sort(int* pP, int psize)
{
	int maxind;
	int i, j;
	int temp;

	for (i = 0; i < psize; i++)
	{
		maxind = i;
		for (j = i; j < psize; j++)
		{
			if (pP[j] > pP[maxind])
				maxind = j;
		}
		temp = pP[i];
		pP[i] = pP[maxind];
		pP[maxind] = temp;
	}
}

void main()
{
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, end, diff;
	int size;
	int* A = NULL;
	int* B = NULL;
	int i;

	srand(time(NULL));

	scanf("%d", &size);
	A = (int*)malloc(size * sizeof(int));
	B = (int*)malloc(size * sizeof(int));

	// 난수로 배열 초기화
	for (i = 0; i < size; i++)
	{
		A[i] = rand();
		B[i] = rand();
	}

	/*
	// 2번 : 미리 정렬해놓기
	selection_sort(A, size);
	selection_sort(B, size);
	*/

	// 3번 : 미리 역순 정렬해놓기
	reverse_sort(A, size);
	reverse_sort(B, size);

	// A-선택정렬 시간계산
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	selection_sort(A, size);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("A-선택정렬 : %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));


	// B-삽입정렬 시간계산
	QueryPerformanceFrequency(&ticksPerSec);
	QueryPerformanceCounter(&start);
	insertion_sort(B, size);
	QueryPerformanceCounter(&end);
	diff.QuadPart = end.QuadPart - start.QuadPart;
	printf("B-삽입정렬 : %.12f sec\n\n", ((double)diff.QuadPart / (double)ticksPerSec.QuadPart));

}