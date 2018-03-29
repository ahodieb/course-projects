#ifndef LinkedLists_H
#define LinkedLists_H

#include "libs.h"
using namespace std;

struct Node;
typedef Node* ptrToNode;
typedef int LDataType;
struct Node{LDataType Data;ptrToNode Next;};

enum Position {Begining,End};

ptrToNode newList(){ptrToNode L = new(Node);L->Next = NULL;return (L);}

ptrToNode insertNode(ptrToNode L,Position P,int Data)
{
    ptrToNode p= new (Node);
    p->Data = Data;

    if(P == Begining)
    {
        p->Next = L->Next;
        L->Next = p;
    }

    else
    {
        ptrToNode q = L;
        while (q->Next!= NULL)
        {
            q=q->Next;
        }

        q->Next = p;
        p->Next = NULL;
        }
    return p;
}


void fillList(ptrToNode L,int nNodes){for(int i = nNodes;i>0;i--)insertNode(L,Begining,i);}

void printList(ptrToNode L,char front[],char back[])
{
    ptrToNode p = L;
    while(p->Next!=NULL)
    {
        p=p->Next;
        cout<<front<<p->Data<<back;
    }
}
int CountNodes(ptrToNode L)
{
    ptrToNode p = L;
    int x = 0;
    while(p->Next!=NULL)
    {
        p=p->Next;
        x++;
    }
    return x;
}

ptrToNode search(ptrToNode L,int x)
{
    ptrToNode p = L;

    while(p->Next !=NULL)
    {
        p=p->Next;
        if(p->Data == x) return (p);
    }
    return (NULL);
}

ptrToNode getPre(ptrToNode L,ptrToNode p)
{
    ptrToNode q = L;
    while(q->Next !=p && q->Next != NULL)
    {
        q=q->Next;
    }
    return q;
}
int delNode(ptrToNode L,ptrToNode p)
{
    ptrToNode q = getPre(L,p);
    q->Next = p->Next;
    int x = p->Data;
    ptrToNode tmp = p;
    p = p->Next;
    free (tmp);
    return x;
}
void delNode (ptrToNode L,int x)
{
    ptrToNode p =L;
    ptrToNode q = L->Next;
    while (p->Next !=NULL)
    {
        if(q->Data == x)
        {
            p->Next = q->Next;
            free(q);
            return;
        }
        p=p->Next;
        q = q->Next;
    }
}


#endif
