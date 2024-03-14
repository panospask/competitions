#include <bits/stdc++.h>

using namespace std;

int cards[200005];
int shuffles[200005];

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &cards[i]);
        
        int topcard = 0;
        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; i++) {
            scanf("%d", &shuffles[i]);
            topcard += shuffles[i];
            topcard %= n;
        }

        printf("%d\n", cards[topcard]);
    }
}