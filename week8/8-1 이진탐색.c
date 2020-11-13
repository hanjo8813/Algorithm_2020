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
    // p�� ��尡 �ܺγ�� �ΰ��� ������� ��� 1 ��ȯ
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

    // Ű���� �۴�? > ���ʳ���
    else if (key < p->key)
        return treeSearch(p->l_child, key);

    else
        return treeSearch(p->r_child, key);
}

int findElement(node* p, int key)
{
    node* temp = treeSearch(p, key);

    // �� �����ôµ� ����� �ܺγ���? > ã�� Ű ����
    if (isExternal(temp))
        return -1;
    else
        return temp->key;
}

void insertItem(node* root, int key)
{
    node* temp = treeSearch(root, key);

    // ���γ���̴�? -> Ű���� �ߺ��ȴ� -> �߰�����
    if (isExternal(temp) == 0)
        return;

    // �ߺ��� ���� �ܺγ����� �Դٸ� �ű⿡ �¿��� �߰�
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

    // z�� w�� ���� �ڽ��̶��
    if (w->l_child == z)
        other_child = w->r_child;
    else if (w->r_child == z)
        other_child = w->l_child;

    // z���� �ٸ� �ڽ��� ���γ���϶�
    // w�� ���� �ڽ��϶�
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

    // ������ Ű ����
    if (isExternal(w))
        return -1;

    // ������ ����� w�� ���� ��带 z���ϸ�
    int e = w->key;
    node* z = w->l_child;

    // z�� ���γ���϶� -> w�� ����������� z�� ������ ���� �ٲ۴�
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
    // �ܺγ����� �͹��� ���
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