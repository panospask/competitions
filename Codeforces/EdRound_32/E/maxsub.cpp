#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) (val & (1<<pos))

using namespace std;

int n, m;
int n1, n2;

vector<int> a;

vector<int> sums;
vector<int> dp;
vector<int> a1;
vector<int> a2;

int main(void)
{
    scanf("%d %d", &n, &m);

    n1 = n / 2;
    n2 = n - n1;

    a1.resize(n1);
    a2.resize(n2);

    for (int i = 0; i < n1; i++) {
        scanf("%d", &a1[i]);
    }

    dp.resize((1 << n1));
    dp[0] = 0;
    for (int s = 0; s < 1 << n1; s++) {
        sums.push_back(dp[s]);
        for (int i = 0; i < n1; i++) {
            if (!CHECK_BIT(s, i)) {
                dp[s + (1<<i)] = (dp[s] + a1[i]) % m;
            }
        }
    }
    sort(sums.begin(), sums.end());

    int ans = 0;
    for (int i = 0; i < n2; i++) {
        scanf("%d", &a2[i]);
    }
    dp.resize((1 << n2));
    dp[0] = 0;
    for (int s = 0; s < 1 << n2; s++) {

        int pos = lower_bound(sums.begin(), sums.end(), m - dp[s]) - sums.begin();
        pos--;
        if (pos == -1)
            pos = sums.size() - 1;

        ans = max(ans, sums[pos] + dp[s]);

        for (int i = 0; i < n2; i++) {
            if (!CHECK_BIT(s, i)) {
                dp[s + (1<<i)] = (dp[s] + a2[i]) % m;
            }
        }
    }

    printf("%d\n", ans);

    return 0;
}