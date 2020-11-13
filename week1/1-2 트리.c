#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef int element;

typedef struct link { //이중연결리스트
    element data;
    int id;
    struct link* left;
    struct link* right;
}Link;

Link* InsertRootNode(Link* pdata, element data, element leftdata, element rightdata)
{
    Link* temp = pdata;
    if (data != 0)
    {
        temp = (Link*)malloc(sizeof(Link));
        temp->data = data;
    }
    if (leftdata != 0)
    {
        temp->left = InsertRootNode(temp, leftdata, 0, 0);
    }
    else
    {
        temp->left = NULL;
    }
    if (rightdata != 0)
    {
        temp->right = InsertRootNode(temp, rightdata, 0, 0);
    }
    else
    {
        temp->right = NULL;
    }
    return temp;
}

Link* travel(Link* p, int data)
{
    Link* temp = NULL;
    Link* result;
    int check = 0;

    if (p != NULL)
    {
        if (p->data == data)
        {
            check++;
            temp = p;
            return temp;
        }
        result = travel(p->left, data);
        if (result != NULL)
            return result;
        result = travel(p->right, data);
        if (result != NULL)
            return result;
    }

    else
    {
        check++;
        return NULL;
    }

    if (check == 0)
        return NULL;
}

int main() {

    int i, j;
    int n;
    Link* p;
    Link* root;
    element x, y, z;
    char way[100];

    scanf("%d", &n);
    scanf("%d %d %d", &x, &y, &z);

    root = InsertRootNode(NULL, x, y, z);

    for (i = 1; i < n; i++)
    {
        scanf("%d %d %d", &x, &y, &z);
        p = travel(root, x);
        InsertRootNode(p, 0, y, z);
    }
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        p = root;
        scanf("%s", way);
        printf(" %d", root->data);
        for (j = 0; j < strlen(way); j++) {
            if (way[j] == 'L')
            {
                printf(" %d", p->left->data);
                p = p->left;
            }
            else
            {
                printf(" %d", p->right->data);
                p = p->right;
            }
        }
        printf("\n");

    }

    return 0;

}