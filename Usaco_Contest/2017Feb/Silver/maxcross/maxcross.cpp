#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

bool isbroken[MAXN + 5];
int ttl_fix[MAXN + 5];
int n, k, b;

int main(void)
{
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);

    scanf("%d %d %d", &n, &k, &b);
    int broken_id;
    for (int i = 1; i <= b; i++) {
        scanf("%d", &broken_id);
        isbroken[broken_id] = true;
    }
    ttl_fix[0] = 0;
    for (int i = 1; i <= n; i++)
        ttl_fix[i] = ttl_fix[i - 1] + isbroken[i];

    int minans = INT_MAX;
    for (int i = k; i <= n; i++) {
        minans = min(minans, ttl_fix[i] - ttl_fix[i - k]);
    } 

    printf("%d\n", minans);
    return 0;
}