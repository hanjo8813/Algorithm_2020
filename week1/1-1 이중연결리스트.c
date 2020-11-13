#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

int cnt = 1;
typedef struct DNode {
    struct DNode* llist;
    char item;
    struct DNode* rlist;
}Node;

typedef struct List {
    char order;
    int pos;
    char item;
}list;

Node* SearchList(Node* L, int n)
{
    Node* temp;
    int i;
    temp = L;
    for (i = 0; i < n - 1; i++)
    {
        temp = temp->rlist;
    }
    return temp;
}

void Add(Node* pre, char item)
{
    Node* newNode;
    newNode = (Node*)malloc(sizeof(Node));
    newNode->item = item;

    newNode->llist = pre;
    newNode->rlist = pre->rlist;
    pre->rlist->llist = newNode;
    pre->rlist = newNode;
    cnt++;
}

void Delete(Node* pre)
{
    Node* old;
    old = pre->rlist;
    pre->rlist = old->rlist;
    old->rlist = pre;
    cnt--;
}

int get_entry(Node* pre)
{
    return pre->rlist->item;
}

void print(Node* L)
{
    Node* temp;
    temp = L->rlist;
    while (temp->rlist != NULL)
    {
        printf("%c", temp->item);
        temp = temp->rlist;
    }
    printf("\n");
}

void main()
{
    //   list_h *L = create();
    Node* pre = NULL, * H = NULL, * T = NULL;
    list* lists = NULL;
    int N, i;
    scanf("%d", &N);
    lists = (list*)malloc(N * sizeof(list));
    H = (Node*)malloc(sizeof(Node));
    T = (Node*)malloc(sizeof(Node));
    H->rlist = T;
    T->llist = H;
    T->rlist = NULL;
    for (i = 0; i < N; i++)
    {
        scanf("\n%c", &lists[i].order);
        switch (lists[i].order)
        {
        case 'A':
            scanf("%d %c", &lists[i].pos, &lists[i].item);
            break;
        case 'D':
            scanf("%d", &lists[i].pos);
            break;
        case 'P':
            break;
        case 'G':
            scanf("%d", &lists[i].pos);
        }
    }
    for (i = 0; i < N; i++)
    {
        switch (lists[i].order)
        {
        case 'A':
            if (lists[i].pos > cnt)
            {
                printf("invalid position\n");
                break;
            }
            else
            {
                pre = SearchList(H, lists[i].pos);
                Add(pre, lists[i].item);
            }
            break;
        case 'D':
            if (lists[i].pos >= cnt)
            {
                printf("invalid position\n");
                break;
            }
            else
                pre = SearchList(H, lists[i].pos);
            Delete(pre);
            break;
        case 'G':
            if (lists[i].pos >= cnt)
            {
                printf("invalid position\n");
                break;
            }
            else
            {
                pre = SearchList(H, lists[i].pos);
                printf("%c\n", get_entry(pre));
            }

            break;
        case 'P':
            print(H);
            break;
        }
    }
    free(lists);
}