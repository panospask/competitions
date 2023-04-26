#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1<<pos))

using namespace std;

int n, x;
vector<int> a;
vector<int> b;
vector<int> sum_a;
vector<int> sum_b;

void generate_subsets(vector<int>& a, vector<int>& store)
{
    int n = (1<<a.size());
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int s = 0; s < n; s++) {
        if (dp[s] == -1)
            continue;
        store.push_back(dp[s]);

        for (int i = 0; i < a.size(); i++)
            if (!CHECK_BIT(s, i)) {
                dp[s | (1<<i)] = dp[s] + a[i];
                if (dp[s | (1<<i)] > 1e9)
                    dp[s | (1<<i)] = -1;
            }
    }
}

int main(void)
{
    scanf("%d %d", &n, &x);
    a.resize(n / 2);
    b.resize(n / 2 + n % 2);
    for (int i = 0; i < n / 2; i++)
        scanf("%d", &a[i]);
    for (int i = n / 2; i < n; i++)
        scanf("%d", &b[i - n/2]);

    generate_subsets(a, sum_a);
    sort(sum_a.begin(), sum_a.end());
    generate_subsets(b, sum_b);
    sort(sum_b.begin(), sum_b.end());

    long long ans = 0;
    for (auto val : sum_a) {
        if (val > x)
            continue;

        int comp = x - val;
        ans += upper_bound(sum_b.begin(), sum_b.end(), comp) - lower_bound(sum_b.begin(), sum_b.end(), comp);
    }

    printf("%lld\n", ans);
    return 0;
}