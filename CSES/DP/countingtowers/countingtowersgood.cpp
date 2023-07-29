#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = (int)1e9 + 7;
const int MAXN = 1e6;

int N;
vector<pi> q;
vector<int> ans;

void solve(void)
{
    N = MAXN;

    int diff = 1;
    int curp = 0;
    int tot = 1;
    int cur_must = 1, cur = 0;
    int must_tot = 1;
    for (int i = 1; i <= N; i++) {
        cur_must += cur;
        if (cur_must > MOD)
            cur_must -= MOD;
        cur = diff + cur_must;
        if (cur > MOD)
            cur -= MOD;

        while (q[curp].first == i) {
            ans[q[curp].second] = cur;
            curp++;
        }

        diff = ((ll)4 * cur - (ll)3 * cur_must) % MOD;
        if (diff < 0)
            diff += MOD;
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    q.resize(t);
    ans.resize(t);
    for (int i = 0; i < t; i++) {
        scanf("%d", &q[i].first);
        q[i].second = i;
    }
    sort(q.begin(), q.end());
    solve();

    for (int i = 0; i < t; i++)
        printf("%d\n", ans[i]);

    return 0;
}