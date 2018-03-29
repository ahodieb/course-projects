#include <iostream>
#include <stdlib.h>
#include <time.h>
#define empty -1

using namespace std;


struct TNode;
typedef TNode * Tree;
struct TNode
{
    int Element;
    Tree Right;
    Tree Left;
};

/////////////////////// Stack////////////////////////
struct Node;
typedef Node *ptrToNode;
struct Node{Tree Element;ptrToNode Next;};


ptrToNode NewStack()
{
    ptrToNode S = new(Node);
    S->Element = NULL;
    S->Next = NULL;
    return S;
}
bool Sempty(ptrToNode S)
{
    return (S->Next == NULL);
}
void push(ptrToNode S,Tree x)
{
    ptrToNode r = new(Node);
    r->Next = S->Next;
    r->Element = x;
    S->Next = r;
}
Tree pop(ptrToNode S)
{
    ptrToNode tmp = S->Next;
    S->Next = S->Next->Next;
    Tree f = tmp->Element;
    free(tmp);
    return f;
}
//////////////////////////////////////////////


Tree Insert (Tree T,int x)
{
    if(T == NULL)
    {
        T = new (TNode);
        T->Element = x;
        T->Left = NULL;
        T->Right = NULL;
    }
    else if (T->Element > x)
    {
        T->Left =  Insert(T->Left,x);
    }
    else if (T->Element < x)
    {
        T->Right = Insert (T->Right,x);
    }
    return T;
}

bool Search(Tree T,int x)
{
    bool found = false;
    if(T!= NULL)
    {
        if(T->Element == x)
        {
            found = true;
        }
        else if (T->Element > x)
        {
            found = Search(T->Left,x);
        }
        else if (T->Element < x)
        {
            found = Search(T->Right,x);
        }
    }
    return found;
}


int getMax(Tree T)
{
    int out = empty;
    if(T != NULL)
    {
        if(T->Right == NULL)
        out = T->Element;
        else out = getMax(T->Right);
    }
    return out;
}


int getMin(Tree T)
{
    int out = empty;
    if(T != NULL)
    {
        if(T->Left == NULL)
        out = T->Element;
        else out = getMax(T->Left);
    }
    return out;
}

void print_Rec(Tree T)
{
    if(T!= NULL)
    {
        print_Rec(T->Left);
        cout << "- "<<T->Element<<endl;
        print_Rec(T->Right);
    }
    //else printf("- Empty.\n");
}
void print_Itr(Tree T)
{
    ptrToNode S = NewStack();
    while(true)
    {
        if(T != NULL)
        {
            push(S,T);
            T = T->Left;
        }
        else
        {
            if(Sempty(S))return;
            T=pop(S);
            cout<< "- "<<T->Element<<endl;
            T= T->Right;
        }
    }
}

//////////////////// Tests
void printbool(bool x)
{
    if (x)cout <<"\nTrue.\n";
    else cout << "\nFalse.\n";
}

int genRand(int from,int to)
{
    int num = 0;
    int range = to-from+1;
    if (range>0)    num = rand()%range;
    return (num + from);
}
Tree RTT(Tree T,int from1,int to1,int from2,int to2)
{
    int val = genRand(from1,to1);
    cout<<"- Number of Generted Values : "<<val<<endl;
    for(int i =0;i<val;i++)
    {
        int f = genRand(from2,to2);
        T=Insert(T,f);
        //printbool(Search(T,f));
    }
    return T;
}
//////////////////////////

int main()
{
    int choice = 8;
    Tree T = NULL;

    do
    {
        cout <<"--------------------------------\n";
        cout <<"--------------------------------\n";
        cout <<"- 1 . Insert a number.\n";
        cout <<"- 2 . Search for a number.\n";
        cout <<"- 3 . Get Max.\n";
        cout <<"- 4 . Get Min.\n";
        cout <<"- 5 . Creat A Random Tree (For Testing).\n";
        cout <<"- 6 . Print Tree  (Recrusivly).\n";
        cout <<"- 7 . Print Tree  (Itration).\n";
        cout <<"- 8 . Exit.\n";
        cout <<"--------------------------------\n";
        cout <<"--------------------------------\n\n";

        cout << "- ";
        cin >> choice;

        switch(choice)
        {
            case 1 :
            {

                system ("clear");// system("cls");//For Windows;
                int input;
                cout <<"- Number to insert : ";
                cin >> input;
                cout << "- Inserting number in The Tree...";
                T = Insert(T,input);
                cout << "\n- Done.\n\n";
            }break;

            case 2 :
            {
                system("clear");
                bool found = false;
                int input;
                cout <<"\n- Number to Search : ";
                cin >> input;
                cout << "- Searching for the  number in The Tree...";
                found = Search(T,input);
                if(found)cout <<"\n- Number : "<<input<< " was found.\n\n";
                else cout <<"\n- Number : " <<input << " was not found !\n\n";
            }break;

            case 3 :
            {
                system("clear");
                cout << "- Getting Max...\n";
                int val = getMax(T);
                cout<<"- Max Number : "<< val<<endl<<endl;
            }break;

            case 4 :
            {
                system("clear");
                cout << "- Getting Min...\n";
                int val = getMax(T);
                cout<<"- Min Number : "<< val<<endl<<endl;
            }break;
            case 5 :
            {
                system("clear");
                cout << "- Creating A Random Test Tree...\n";
                T = RTT(T,10,20,0,100);
                cout << "\n- Done.\n\n";
            }break;

            case 6 :
            {
                system("clear");
                cout <<"- Printing Tree (Recursion)....\n";
                print_Rec(T);
                cout << "\n- Done.\n\n";
            }break;

            case 7 :
            {
                system("clear");
                cout <<"- Printing Tree (Itration)....\n";
                print_Itr(T);
                cout << "\n- Done.\n\n";
            }break;
            case 8:
            {
            }break;
            default : cout << "\n- Invalaid !\n\n";
        }


    }while(choice != 8);
}
