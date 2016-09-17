#include <stdio.h>
#define NMAX 10

int binsearch(int x, int v[], int n);

int main()
{
    int x, n;
    int v[NMAX];
    
    for (x = 0; x < NMAX; x++)
        v[x] = x*x;
    x = 9;
    
    n = binsearch(x, v, NMAX);
    printf("%d\n", n);
    
}

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n-1;
    int mid;
    
    while (v[mid = (low + high)/2] != x && low <= high) {
        printf("%6d,%6d,%6d\n", low, mid, high);
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return v[mid] == x ? mid : -1;
    
    return -1;
}
