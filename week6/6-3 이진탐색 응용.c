#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#pragma warning(disable: 4996)

int rFE(int A, int B, char* str, int index)
{
	int M = (A + B) / 2;
	if (index == strlen(str))
		return M;
	if (str[index] == 'Y')
		return rFE(M + 1, B, str, index + 1);
	else
		return rFE(A, M, str, index + 1);
}

void main()
{
	int A, B, N;
	char* str;
	scanf("%d %d %d", &A, &B, &N);
	str = (char*)malloc(sizeof(char) * N);
	scanf("%s", str);
	int answer = rFE(A, B, str, 0);
	printf("%d", answer);
}