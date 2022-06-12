#include <bits/stdc++.h>

using namespace std;

int start[300000], finish[300000], arrive[300000];
int n;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++)  
            scanf("%d", &arrive[i]);
        
        for (int i = 0; i < n; i++)
            scanf("%d", &finish[i]);

        start[0] = arrive[0];
        for (int i = 0; i < n; i++)
            start[i] = max(arrive[i], finish[i - 1]);

        for (int i = 0; i < n; i++)
            printf("%d ", finish[i] - start[i]);
        printf("\n");
    }

    return 0;
}