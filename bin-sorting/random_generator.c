#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Custom Random Generating Function
int genRand(int from,int to)
{
    int num = 0;
    int range = to-from+1;
    if (range>0)    num = rand()%range;
    return (num + from);
}
// Function To Count Digits
int countDigits(int x)
{
    int d =1,mult =10;
    while((x/mult) != 0)
    {d++; mult*=10;}
    return d;
}

int main()
{
    char fileName[FILENAME_MAX];
    int from,to,number,rnd,maxDigits=0;
    FILE *Output;

    do
    {
        printf("\n- Enter a valid output path : ");
        scanf("%s",fileName);
        Output = fopen(fileName,"w");
    }while(Output==NULL);

    printf("\n- Random Numbers from : ");
    scanf("%d",&from);
    printf("\n- Random Numbers to : ");
    scanf("%d",&to);
    printf("\n- Random Numbers to be generated : ");
    scanf("%d",&number);

    printf("\n- Generating Numbers...");

    srand(time(NULL));

    fprintf(Output,"- Numbers to Sort : %d\n\n",number);

    for(int i = 0;i<number;i++)
    {
        int x = genRand(from,to);
        int d = countDigits(x);
        if(maxDigits<d)maxDigits = d;
        fprintf(Output,"- %d\n",x);
    }

    fprintf(Output,"\n- Max Digits : %d\n",maxDigits);

    fclose(Output);

    printf("\n- Done.");

    return 0;
}
