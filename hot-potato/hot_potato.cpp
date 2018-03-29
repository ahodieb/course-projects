// Code By: Abdallah Mohamed - Id: 7103755 - Computer Engineering.
//Presented To : Dr Samah Sonbl / Eng. Mohamed Abd El Slam.

#include <iostream>

using namespace std;

// Node Construction.
struct Node;
typedef Node* PtrToNode;
struct Node
{
    int Data;
    PtrToNode Next;

};

// Function to creat new cirular linked list.
PtrToNode newCList()
{
    PtrToNode L = new Node();
    //Cicrular empty list points towards itself.
    L->Next = L;
    return(L);
}
//Function to Insert A new Node in the begining of the list.
void InsertNode(PtrToNode L,int Data)
{
    PtrToNode p = new (Node);
    p->Next = L->Next;
    L->Next = p;
    p->Data = Data;
}
//Function to Print List elemnts.
void printList(PtrToNode L)
{
    if (L->Next != L)
    {
        PtrToNode p = L;
        // Condition to escape the circualar loop.
        while (p->Next != L)
        {
            p=p->Next;
            cout<< p->Data<<endl;
        }
    }
}
//The Main function of the game.
void Play(PtrToNode L,int m,bool dE)
{
    PtrToNode p = L;
    PtrToNode q = p->Next;

    //Complex condition that is satisfied only if one node is left in the List.
    while (!(L->Next != L && L->Next->Next ==L))
    {
        for (int i =0;i<m;i++)
        {
            p=p->Next;
            q=q->Next;
            //Precution not to get the Header of the linked list removed.
            if (q == L)i--;
        }
        PtrToNode r = q;
        p->Next = q->Next;
        q=q->Next;
        //This conditon to correct some logical errors that might happin.
        if (q == L)
        {
            q=q->Next;
            p=p->Next;
        }
        if (dE)cout <<endl<<"Player no. : " <<r->Data<< " Was elmenated."<<endl;
        free (r);
    }
}
// Function to check the playing continuty and print the interface;
bool cPlaying ()
{
    cout<<endl<<"Do you want to play agin (y/n): ";
    char choice;
    cin >> choice ;
    if (choice == 'y'||choice == 'Y')
    {
        cout <<endl<<endl;
        return(true);
    }
    return (false);
}
// Function to check the displaying of elemination sequance and print the interface;
bool DisplayE ()
{
    cout<<endl<<"Do you want to print the elemination sequance."<<endl<<"It might increase the run time. (y/n): ";
    char choice;
    cin >> choice ;
    if (choice == 'y'||choice == 'Y')
    {
        cout <<endl<<endl;
        return(true);
    }
    return (false);
}
//The Program main Function
int main()
{
    bool C_play = false;

    do
    {
        PtrToNode L = newCList();
        int m,n;
        cout<<"Enter number of players : ";
        cin >> n;
        cout<< endl<<"Enter number of turns : ";
        cin >>m;
        bool dE = DisplayE();

        for (int i =n;i>0;i--)
        {
            InsertNode(L,i);
        }
        Play(L,m,dE);
        cout <<endl<< "Winner is : ";
        printList(L);

        C_play = cPlaying();
    }
    while (C_play);

    return (0);
}
