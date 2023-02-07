#include <bits/stdc++.h>
#define MAXN 100

using namespace std;

int n;
int original_spot[MAXN];
int sorted_spot[MAXN];

int main(void)
{
    freopen("outofplace.in", "r", stdin);
    freopen("outofplace.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &original_spot[i]);
        sorted_spot[i] = original_spot[i];
    }

    sort(sorted_spot, sorted_spot + n);

    int diffs = 0;
    for (int i = 0; i < n; i++) {
        if (original_spot[i] != sorted_spot[i])
            diffs++;
    }

    printf("%d\n", diffs - 1);
    return 0;
}