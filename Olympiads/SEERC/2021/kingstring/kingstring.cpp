#include <bits/stdc++.h>

using namespace std;

int N;
string s, t;

// dp[i]: The first position P s.t for all j >= P it holds that s[i..j] <= t[i..j]
vector<int> dp;

int main(void)
{
    cin >> N >> s >> t;

    dp.resize(N + 1);
    dp[N] = N;

    long long ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (s[i] == t[i]) {
            dp[i] = dp[i + 1];
        }
        else if (s[i] < t[i]) {
            dp[i] = i;
        }
        else {
            dp[i] = N;
        }

        ans += N - dp[i];
    }

    printf("%lld\n", ans);

    return 0;
}