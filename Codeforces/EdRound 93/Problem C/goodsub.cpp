#include <bits/stdc++.h>
#define MAXN 100000

using namespace std;

int ttl_sum_rel_to_length[MAXN + 5];
int num[MAXN + 5];
int t, n;
unordered_map<int, int> valcount;

int main(void)
{
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        valcount.clear();
        scanf("%d", &n);
        ttl_sum_rel_to_length[0] = 0;
        valcount[0]++;
        for (int i = 1; i <= n; i++) {
            scanf("%1d", &num[i]);
            ttl_sum_rel_to_length[i] = ttl_sum_rel_to_length[i - 1] + num[i] - 1;
            valcount[ttl_sum_rel_to_length[i]]++;
        }

        long long int ans = 0;
        for (auto val : valcount) {
            ans += (val.second) * (long long int)(val.second - 1) / 2; 
        }

        printf("%lld\n", ans);
    }

    return 0;
}