#include <bits/stdc++.h>
#define MAXN 300
#define mp make_pair

using namespace std;

struct sit {
    long long int value;
    int day;

    sit(void) {
        value = 0;
        day = 1e9;
    }
    sit(long long v, int d) {
        value = v;
        day = d;
    }
};
typedef struct sit Sit;

bool operator < (Sit a, Sit b)
{
    if (a.value == b.value)
        return a.day > b.day;

    return a.value < b.value;
}

Sit operator + (Sit a, Sit b)
{
    return Sit(a.value + b.value, a.day + b.day);
}

//dp[l][r][k]: The maximum amount of water the beetle can lose from l to r and what direction it is in
long long dp[MAXN + 2][MAXN + 2][2];
int x[MAXN + 2];
vector<int> l_x;
vector<int> r_x;
int n, m;

int main(void)
{
    scanf("%d %d", &n, &m);
    l_x.push_back(0);
    r_x.push_back(0);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &x[i]);
        if (x[i] < 0)
            l_x.push_back(x[i]);
        else    
            r_x.push_back(x[i]);
    }

    sort(l_x.begin(), l_x.end());
    reverse(l_x.begin(), l_x.end());
    sort(r_x.begin(), r_x.end());

    long long ans = 0;

    dp[0][0][0] = dp[0][0][1] = 0;
    for (int len = 0; len <= n; len++) {
        for (int l = 0; l < l_x.size(); l++)
            for (int r = 0; r < r_x.size(); r++)
                dp[l][r][0] = dp[l][r][1] = LONG_LONG_MIN;

        dp[0][0][0] = dp[0][0][1] = 0;
        for (int l = 0; l < l_x.size(); l++)
            for (int r = 0; r < r_x.size(); r++) {
                if (l + r == len) {
                    ans = max(ans, max(dp[l][r][0], dp[l][r][1]));
                }
                else if (l + r > len) {
                    continue;
                }
                // Times we will use the current distance
                int times_used = (len - l - r);

                // Move to a new left drop
                if (l < l_x.size() - 1) {
                    if (dp[l][r][0] != LONG_LONG_MIN) {
                        dp[l+1][r][0] = max(dp[l+1][r][0], m + dp[l][r][0] - times_used * abs(l_x[l] - l_x[l+1]));
                    }
                    if (dp[l][r][1] != LONG_LONG_MIN) {
                        dp[l+1][r][0] = max(dp[l+1][r][0], m + dp[l][r][1] - times_used * abs(l_x[l+1] - r_x[r]));
                    }
                }

                // Move to a new right drop
                if (r < r_x.size() - 1) {
                    if (dp[l][r][0] != LONG_LONG_MIN) {
                        dp[l][r+1][1] = max(dp[l][r+1][1], m + dp[l][r][0] - times_used * abs(l_x[l] - r_x[r+1]));
                    }
                    if (dp[l][r][1] != LONG_LONG_MIN) {
                        dp[l][r+1][1] = max(dp[l][r+1][1], m + dp[l][r][1] - times_used * abs(r_x[r+1] - r_x[r]));
                    }
                }
            }
    }

    printf("%lld\n", ans);
    return 0;
}