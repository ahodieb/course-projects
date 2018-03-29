#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef Node* ptrToNode;
struct Node{int Data;ptrToNode Next;};
// New Q
ptrToNode newQ(){ptrToNode L = new(Node);L->Next = NULL;return L;}
// Enque Function
void Enque(ptrToNode Q,int Data)
{
    ptrToNode p = Q,tmp;
    while(p->Next!=NULL) p=p->Next;
    tmp = new(Node);
    tmp->Next = p->Next;
    p->Next = tmp;
    tmp->Data = Data;
}
// DeQ function
int Deque (ptrToNode Q)
{
    int out  = -1;
    if(Q->Next!=NULL)
    {
        ptrToNode p = Q->Next;
        Q->Next = p->Next;
        out = p->Data;
        free(p);
    }
    return out;
}
// Sorting co Functions
int get10(int i)
{
    int mult = 1;
    for(int x = 0;x<i;x++) mult *=10;
    return mult;
}
int getDigit(int x,int y)
{
    int mult = get10(y-1);
    return ((x%(mult*10))/(mult));
}
// Reading File for Numbers.
void readFile(ptrToNode Q,int *maxDigits,int* Number)
{
    char fileName[FILENAME_MAX];
    FILE *Input;

    do
    {
        printf("\n- Enter a valid input path : ");
        scanf("%s",fileName);
        Input = fopen(fileName,"r");
    }while(Input==NULL);

    printf("\n- Proccesing file...\n");

    fscanf(Input,"- Numbers to Sort : %d\n\n",Number);

    for(int i = 0;i<*Number;i++)
    {
        int x;
        fscanf(Input,"- %d\n",&x);
        Enque(Q,x);
    }

    fscanf(Input,"\n- Max Digits : %d\n",maxDigits);
    fclose(Input);
    printf("- Done.\n");
}
//Save
void Save(ptrToNode Q)
{
    char fileName[FILENAME_MAX];
    FILE *Output;
    do
    {
        printf("\n- Enter a valid output path : ");
        scanf("%s",fileName);
        Output = fopen(fileName,"w");
    }while(Output==NULL);

    printf("\n- Saveing Output...");
    while(Q->Next!=NULL)
    {
        fprintf(Output,"- %d\n",Deque(Q));
    }

    fclose(Output);
    printf("\n- Done.");
}
//Initialize Bins.
void initialize(ptrToNode L[])
{
    for(int i = 0;i<10;i++) L[i] = newQ();
}

void tprint(ptrToNode L)
{
    ptrToNode p = L;
    bool empty = true;
    while(p->Next != NULL)
    {
            empty = false;
        p=p->Next;
        printf("\n- %d",p->Data);
    }
    if(empty) printf ( "\n- Empty");
}
int main()
{
    ptrToNode L[10];
    int maxDigits,Number,i = 1,current,digit;
    ptrToNode  Q = newQ();

    readFile(Q,&maxDigits,&Number);

    printf("\n- Initializing Bins...");
    printf("\n- Done.\n");
    initialize(L);

    printf("\n- Sorting...");

    for(i=1;i<=maxDigits;i++)
    {
        printf("\n- Step %d of %d",i,maxDigits);
        while(Q->Next!= NULL)
        {
            current = Deque(Q);
            digit = getDigit(current,i);
            //- Debug printf("\nEnqu %d into %d",current,digit);
            Enque(L[digit],current);
        }
        for (int j = 0;j<10;j++)
        {
            while(L[j]->Next !=NULL)
            {
                current = Deque(L[j]);
                //- Debug printf("\nEnqu from L[%d] : %d",j,current);
                Enque(Q,current);
            }
        }
        printf("\n- Done.\n");
    }
    printf("\n- Sorted.\n");
    Save(Q);

   return 0;
}
