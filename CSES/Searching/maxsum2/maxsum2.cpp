#include <bits/stdc++.h>

using namespace std;

int n;
int a, b;
vector<long long int> pref_sum;
// max_in_range[i] is the maximum prefix sum in the range [i... (i+b-a)]
vector<long long int> max_in_range;
multiset<long long int> cur_maximum;

int main(void)
{
    scanf("%d %d %d", &n, &a, &b);
    long long int cur_total = 0;
    int val;
    pref_sum.resize(n + 2);
    max_in_range.resize(n + 2);

    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        pref_sum[i] = cur_total + val;
        cur_total = pref_sum[i];
    }
    pref_sum[n] = LONG_LONG_MIN;

    int len = b-a+1;
    for (int i = 0; i < len; i++)
        cur_maximum.insert(pref_sum[i]);

    for (int i = 0; i < n; i++) {
        max_in_range[i] = *cur_maximum.rbegin();

        // Move forward by 1 slot
        cur_maximum.erase(cur_maximum.find(pref_sum[i]));
        if (i + len < n) {
            cur_maximum.insert(pref_sum[i+len]);
        }
    }

    long long ans = LONG_LONG_MIN;
    for (int i = 0; i <= n - a; i++) {
        long long int rm;
        if (i == 0)
            rm =0;
        else
            rm = pref_sum[i-1];

        ans = max(ans, max_in_range[i+a-1] - rm);
    }
    printf("%lld\n", ans);
    return 0;
}