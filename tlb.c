#include <stdio.h>
#include <time.h>

void tlb(int n, int trials, int target) 
{
    time_t now;
    time(&now);

    struct tm *local = localtime(&now);

    printf("The current time is: %s", asctime(local));

    int *pages = (int*) malloc(n * sizeof(int));

    for(int i = 0; i < n; i++)
    {
        
    }
}