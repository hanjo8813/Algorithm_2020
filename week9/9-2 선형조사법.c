#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

int M;
int* arr;

int h(int x)
{
    return x % M;
}

int getNextBucket(int key, int i)
{
    return (key + i) % M;
}

void initBucketArray()
{
    for (int i = 0; i < M; i++)
        arr[i] = 0;
    return;
}

void insertItem(int x)
{
    int key = h(x);
    int b, i = 0;
    while (i < M)
    {
        b = getNextBucket(key, i);
        if (arr[b] == NULL)
        {
            arr[b] = x;
            for (int j = 0; j < i; j++)
                printf("C");
            printf("%d\n", b);
            return;
        }
        i++;
    }
    return;
}

void findElement(int x)
{
    int i = h(x);
    while (arr[i] != NULL)
    {
        if (arr[i] == x)
        {
            printf("%d %d\n", i, x);
            return;
        }
        else
        {
            i++;
            i = h(i);
        }
    }
    printf("-1\n");
}

void main()
{
    char c;
    int n, x;
    scanf("%d %d", &M, &n);
    arr = (int*)malloc(sizeof(int) * M);
    initBucketArray();

    while (1)
    {
        scanf("%c", &c);
        if (c == 'e')
            break;
        switch (c)
        {
        case 'i':
            scanf("%d", &x);
            insertItem(x);
            break;
        case 's':
            scanf("%d", &x);
            findElement(x);
            break;
        }
    }
}