#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct node {
    int data;
    struct node* next;
}node;

int M;
node* arr;

int h(int x)
{
    return x % M;
}

void initBucketArray()
{
    for (int i = 0; i < M; i++)
        (arr + i)->next = NULL;
    return;
}

void insertItem(int x)
{
    int key = h(x);
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = x;
    new_node->next = NULL;

    // 해당 키의 리스트가 아예없다면
    if ((arr + key)->next == NULL)
    {
        (arr + key)->next = new_node;
    }
    else
    {
        new_node->next = (arr + key)->next;
        (arr + key)->next = new_node;
    }
    return;
}

void findElement(int x)
{
    int cnt = 0;
    int key = h(x);
    node* temp = (arr + key)->next;

    while (temp != NULL)
    {
        cnt++;
        if (temp->data == x)
        {
            printf("%d\n", cnt);
            return;
        }
        temp = temp->next;
    }
    printf("0\n");
    return;
}

void removeElement(int x)
{
    int cnt = 0;
    int key = h(x);
    node* pre_temp = (arr + key);
    node* temp = (arr + key)->next;

    while (temp != NULL)
    {
        cnt++;
        if (temp->data == x)
        {
            pre_temp->next = temp->next;
            free(temp);
            printf("%d\n", cnt);
            return;
        }
        pre_temp = pre_temp->next;
        temp = temp->next;
    }
    printf("0\n");
    return;
}

void printTable()
{
    node* temp;
    for (int i = 0; i < M; i++)
    {
        temp = (arr + i)->next;
        while (temp != NULL)
        {
            printf(" %d", temp->data);
            temp = temp->next;
        }
    }
    printf("\n");
    return;
}

void main()
{
    char c;
    int x;
    scanf("%d", &M);
    arr = (node*)malloc(sizeof(node) * M);
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
        case 'd':
            scanf("%d", &x);
            removeElement(x);
            break;
        case 'p':
            printTable();
            break;
        }
    }
}