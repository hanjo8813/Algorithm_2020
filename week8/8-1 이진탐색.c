#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

typedef struct node* nodeP;
typedef struct node {
    int key;
    nodeP parent;
    nodeP l_child;
    nodeP r_child;
}node;

int isExternal(node* p)
{
    // p의 노드가 외부노드 두개를 가질경우 경우 1 반환
    if (p->l_child == NULL && p->r_child == NULL)
        return 1;
    else
        return 0;
}

node* treeSearch(node* p, int key)
{
    if (isExternal(p))
        return p;

    if (key == p->key)
        return p;

    // 키보다 작다? > 왼쪽노드로
    else if (key < p->key)
        return treeSearch(p->l_child, key);

    else
        return treeSearch(p->r_child, key);
}

int findElement(node* p, int key)
{
    node* temp = treeSearch(p, key);

    // 다 돌려봤는데 결과가 외부노드다? > 찾는 키 없음
    if (isExternal(temp))
        return -1;
    else
        return temp->key;
}

void insertItem(node* root, int key)
{
    node* temp = treeSearch(root, key);

    // 내부노드이다? -> 키값이 중복된다 -> 추가못해
    if (isExternal(temp) == 0)
        return;

    // 중복값 없이 외부노드까지 왔다면 거기에 좌우노드 추가
    node* Lnode = (node*)malloc(sizeof(node));
    node* Rnode = (node*)malloc(sizeof(node));

    temp->key = key;
    temp->l_child = Lnode;
    temp->r_child = Rnode;

    Lnode->parent = temp;
    Rnode->parent = temp;

    Lnode->l_child = NULL;
    Lnode->r_child = NULL;

    Rnode->l_child = NULL;
    Rnode->r_child = NULL;
    return;
}

void reduceExternal(node* z)
{
    node* w = z->parent;
    node* w_parent = w->parent;
    node* other_child = NULL;

    // z가 w의 왼쪽 자식이라면
    if (w->l_child == z)
        other_child = w->r_child;
    else if (w->r_child == z)
        other_child = w->l_child;

    // z말고 다른 자식이 내부노드일때
    // w가 왼쪽 자식일때
    if (w_parent->l_child == w)
        w_parent->l_child = other_child;
    else if (w_parent->r_child == w)
        w_parent->r_child = other_child;

    other_child->parent = w_parent;

    free(w);
    free(z);
}

node* inOrderSucc(node* w)
{
    w = w->r_child;

    if (isExternal(w))
        return;

    while (1)
    {
        if (isExternal(w))
        {
            w = w->parent;
            break;
        }
        w = w->l_child;
    }
    return w;
}

int removeElement(node* p, int key)
{
    node* w = treeSearch(p, key);

    // 삭제할 키 없음
    if (isExternal(w))
        return -1;

    // 삭제할 노드인 w의 왼쪽 노드를 z라하면
    int e = w->key;
    node* z = w->l_child;

    // z가 내부노드일때 -> w가 낑겨있을경우 z를 오른쪽 노드로 바꾼다
    if (isExternal(z) == 0)
        z = w->r_child;

    if (isExternal(z))
        reduceExternal(z);
    else
    {
        node* y = inOrderSucc(w);
        z = y->l_child;
        w->key = y->key;
        reduceExternal(z);
    }

    return e;
}

void printTree_preorder(node* p)
{
    // 외부노드까지 와버린 경우
    if (isExternal(p))
        return;
    printf(" %d", p->key);
    printTree_preorder(p->l_child);
    printTree_preorder(p->r_child);
}

void main()
{
    char command;
    int key, removekey;
    node* root = (node*)malloc(sizeof(node));
    root->parent = NULL;
    root->l_child = NULL;
    root->r_child = NULL;

    while (1)
    {
        scanf("%c", &command);

        if (command == 'i')
        {
            scanf("%d", &key);
            insertItem(root, key);
        }

        else if (command == 'd')
        {
            scanf("%d", &key);
            removekey = removeElement(root, key);
            if (removekey == -1)
                printf("X\n");
            else
                printf("%d\n", removekey);
        }

        else if (command == 's')
        {
            scanf("%d", &key);
            if (findElement(root, key) == -1)
                printf("X\n");
            else
                printf("%d\n", findElement(root, key));
        }

        else if (command == 'p')
        {
            printTree_preorder(root);
            printf("\n");
        }

        else if (command == 'q')
        {
            break;
        }
    }
}