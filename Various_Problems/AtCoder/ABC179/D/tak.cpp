#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
constexpr int MOD = 998244353;

int N, K;
vector<pi> segments;
vector<int> num_contained;

// dp[i]: Number of ways to go from cell 0 to cell i
vector<int> dp;
vector<int> change;

void add(int& a, int b)
{
    a = a + b;
    if (a >= MOD) {
        a -= MOD;
    }
    if (a < 0) {
        a += MOD;
    }
}

int main(void)
{
    scanf("%d %d", &N, &K);

    dp.assign(N + 1, 0);
    change.assign(N + 1, 0);

    num_contained.assign(N + 1, 0);
    for (int i = 0; i < K; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--;
        num_contained[l]++;
        num_contained[r]--;
    }
    for (int i = 1; i <= N; i++) {
        num_contained[i] = num_contained[i] + num_contained[i - 1];
    }

    int cur_l = -1;
    for (int i = 0; i <= N; i++) {
        if (num_contained[i] && cur_l == -1) {
            cur_l = i;
        }
        else if (!num_contained[i] && cur_l != -1) {
            segments.pb(mp(cur_l + 1, i + 1));
            cur_l = -1;
        }
    }

    dp[0] = 1;
    for (int i = 0; i < N; i++) {
        add(change[i + 1], change[i]);
        add(dp[i], change[i]);

        for (int j = 0; j < segments.size(); j++) {
            add(change[min(i + segments[j].first, N)], dp[i]);
            add(change[min(i + segments[j].second, N)], -dp[i]);
        }
    }

    printf("%d\n", dp[N - 1]);
}