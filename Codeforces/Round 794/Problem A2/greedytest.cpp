#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        int n;
        scanf("%d", &n);
        int a[n];
        int sum = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            sum += a[i];
        }

        bool can = false;
        for (int i = 0; i < n && !can; i++) {
            if ((float) (sum - a[i]) / (n - 1) == a[i]) 
                can = true;
        }

        if (can)
            printf("YES\n");
        else 
            printf("NO\n");
    }
}