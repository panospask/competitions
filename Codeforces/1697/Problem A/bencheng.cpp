#include <bits/stdc++.h>

using namespace std;

int dist[105];
long long int pref_sum[105];
int n, m;

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        scanf("%d %d", &n, &m);

        scanf("%d", &dist[0]);
        pref_sum[0] = dist[0];
        for (int i = 1; i < n; i++) {
            scanf("%d", &dist[i]);
            pref_sum[i] = pref_sum[i - 1] + dist[i];
        }   

        printf("%lld\n", max(0ll, pref_sum[n - 1] - m));
    }

    return 0;
}