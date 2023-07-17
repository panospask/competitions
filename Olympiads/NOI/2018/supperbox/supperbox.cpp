#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXS = 2001;

struct Query {
    int a, b;
    int s;
    int id;
};
bool operator < (const Query& a, const Query& b)
{
    return mp(a.a, a.b) < mp(b.a, b.b);
}

int n;
vector<vector<ll>> dp;
vector<Query> queries;
vector<ll> ans;
vector<pi> a;
int q;

void d_c(int l, int r, vector<int>& ids)
{
    if (l == r - 1) {
        for (auto i : ids) {
            ans[queries[i].id] = queries[i].s >= a[l].first ? a[l].second : 0;
        }

        return;
    }

    int mid = (l + r) / 2;
    dp[mid - 1].assign(MAXS, 0);
    for (int i = 0; i + a[mid - 1].first < MAXS; i++)
        dp[mid - 1][i + a[mid - 1].first] = a[mid - 1].second;

    for (int i = mid - 2; i >= l; i--) {
        dp[i].clear();
        dp[i][0] = 0;
        for (int j = 1; j < MAXS; j++) {
            dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);

            if (j - a[i].first >= 0)
                dp[i][j] = max(dp[i][j], dp[i + 1][j - a[i].first] + a[i].second);
        }
    }

    dp[mid].assign(MAXS, 0);
    for (int i = 0; i + a[mid].first < MAXS; i++)
        dp[mid][i + a[mid].first] = a[mid].second;
    for (int i = mid + 1; i < r; i++) {
        dp[i][0] = 0;
        for (int j = 1; j < MAXS; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

            if (j - a[i].first >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - a[i].first] + a[i].second);
        }
    }

    vector<int> id1, id2;

    for (auto v : ids) {
        if (queries[v].b <= mid) {
            id1.push_back(v);
        }
        else if (queries[v].a >= mid) {
            id2.push_back(v);
        }
        else {
            ll res = 0;
            int a = queries[v].a;
            int b = queries[v].b - 1;
            for (int i = 0; i <= queries[v].s; i++) {
                res = max(res, dp[a][i] + dp[b][queries[v].s - i]);
            }
            ans[queries[v].id] = res;
        }
    }

    d_c(l, mid, id1);
    d_c(mid, r, id2);
}

int main(void)
{
    scanf("%d", &n);

    dp.resize(n, vector<ll>(MAXS));

    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a[i].first, &a[i].second);
    }

    scanf("%d", &q);
    ans.resize(q);
    vector<int> initial;
    for (int i = 0; i < q; i++) {
        int a, b, x;
        scanf("%d %d %d", &a, &b, &x);
        a--;

        queries.push_back({a, b, x, i});
        initial.push_back(i);
    }
    sort(queries.begin(), queries.end());

    d_c(0, n, initial);

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}