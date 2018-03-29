#include "LinkedLists.h"

int main()
{
    int choise  = 0;
    ptrToNode L = newList();
    while (choise != 9)
    {
        cout <<"1 - Insert a new Node in the begining.\n";
        cout <<"2 - Insert a new Node in the End.\n";
        cout <<"3 - Insert a new Node after a certain Node.\n";
        cout <<"4 - Delete a node (mode 1).\n";
        cout <<"5 - Delete a node (mode 2).\n";
        cout <<"6 - Print List.\n";
        cout <<"7 - Fill List automaticly.\n";
        cout <<"8 - Count Nodes.\n";
        cout <<"9 - Exit.\n";
        cout <<"10 - Expermntal Memory Test";

        cin >> choise;

        switch(choise)
        {
            case 1:
            {
             cout <<"\n\nInsert a number : ";
             int x ;
             cin >> x;
             insertNode(L,Begining,x);
             cout <<"\nNode Inserted";
            }
            break;

            case 2:
            {
               cout <<"\n\nInsert a number : ";
             int x ;
             cin >> x;
             insertNode(L,End,x);
             cout <<"\nNode Inserted";
            }
            break;

            case 3:
            {
               cout <<"\n\nInsert a number to insert after  : ";
             int x ,y;
             cin >> x;
             cout <<"\n\nInsert a number : ";
             cin >> y;
             insertNode(search(L,x),Begining,y);
             cout <<"\nNode Inserted";
            }
            break;

            case 4:
            {
                cout <<"\n\nInsert a number : ";
             int x ;
             cin >> x;
             ptrToNode q = search(L,x);
             if(q!=NULL)
             delNode(L,q);
            }
            break;

            case 5:
            {
             cout <<"\n\nInsert a number : ";
             int x ;
             cin >> x;
             delNode(L,x);
            }
            break;

            case 6:
            {
                printList(L,"-  ","   -\n");
            }
            break;

            case 7 :
            {
                cout <<"\n\nInsert a number : ";
                int x ;
                cin >> x;
                fillList(L,x);
            }
            break;

            case 8 :
            {
                cout <<"\n\nNumber of Nodes : "<< CountNodes(L) <<endl;
            }
            break;
            case 10 :
            {
                ptrToNode p = new (Node);
                while (p!=NULL)
                {
                    p->Next = L->Next;
                    L->Next = p;
                    p= new(Node);
                }
                cout << "out of memory";
            }
            break;

        }
    }
    return 0;
}
