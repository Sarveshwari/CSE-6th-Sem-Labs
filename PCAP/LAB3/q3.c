#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

int nonvowel(char *str, int len)
{ 
    int count=0;
    for(int i=0; i<len; i++)
    {
        if(str[i]=='a' ||str[i]=='e' ||str[i]=='i' ||str[i]=='o' ||str[i]=='u' ||str[i]=='A' ||str[i]=='E' ||str[i]=='I' ||str[i]=='O' ||str[i]=='U')
        count++;
    }
    str[len]='\0';
    return count;
}

int main( int argc, char *argv[])
{
    int rank, size, totalcount, div, count, N;
    int processcount[10];
    char str[300];
    char c[100];


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0)
    {
        N=size;
        printf("Enter a string:");
        scanf("%s", str);
        div=(strlen(str))/N;

    }

   MPI_Bcast(&div, 1, MPI_INT, 0 , MPI_COMM_WORLD);

    MPI_Scatter(str, div, MPI_CHAR,c ,div, MPI_CHAR, 0, MPI_COMM_WORLD);

    count=nonvowel(c, div);

    printf("Process %d -> %s had received %d nonvowels\n", rank, c, count);


    MPI_Gather(&count,1, MPI_INT, processcount,1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Reduce(&count, &totalcount, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if( rank == 0)
    {
        printf("The total number of non vowels are %d\n", totalcount);
    }

    MPI_Finalize();
    return 0;




}
