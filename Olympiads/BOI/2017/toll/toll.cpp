#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int n, k, m, o;
vector<vector<pi>> adj_list;
vector<vector<pi>> rev_list;
vector<int> ans;
vector<vector<ll>> lefty;
vector<vector<ll>> righty;
vector<pi> initial;

void divide(int lx, int rx, vector<int>& queries)
{
    if (!queries.size())
        return;

    if (rx - lx <= k)
        return;

    int sz = rx - lx;
    int mid = lx;
    while (mid - lx < (rx - lx) / 2)
        mid += k;

    for (int i = mid - k; i < mid; i++) {
        for (int j = 0; j < k; j++)
            lefty[i][j] = INT_MAX;
        lefty[i][i % k] = 0;
    }
    for (int i = mid - k - 1; i >= lx; i--) {
        for (int j = 0; j < k; j++)
            lefty[i][j] = INT_MAX;
        for (auto& neigh : adj_list[i])
            for (int j = 0; j < k; j++)
                lefty[i][j] = min(lefty[i][j], lefty[neigh.first][j] + neigh.second);
    }

    for (int i = mid; i < mid + k && i < rx; i++) {
        for (int j = 0; j < k; j++)
            righty[i][j] = INT_MAX;
        righty[i][i % k] = 0;
    }
    for (int i = mid + k; i < rx; i++) {
        for (int j = 0; j < k; j++)
            righty[i][j] = INT_MAX;
        for (auto& neigh : rev_list[i])
            for (int j = 0; j < k; j++)
                righty[i][j] = min(righty[i][j], righty[neigh.first][j] + neigh.second);
    }

    vector<int> q1, q2;
    for (auto& q : queries) {
        if (initial[q].first < mid) {
            if (initial[q].second < mid)
                q1.push_back(q);
            else {
                long long dist = INT_MAX;
                int v1 = initial[q].first, v2 = initial[q].second;
                for (int i = 0; i < k; i++) {
                    int node = mid - k + i;
                    for (auto neigh : adj_list[node])
                        dist = min(dist, lefty[v1][i] + neigh.second + righty[v2][neigh.first % k]);
                }

                ans[q] = (dist == INT_MAX ? -1 : dist);
            }
        }
        else
            q2.push_back(q);
    }

    divide(lx, mid, q1);
    divide(mid, rx, q2);
}

int main(void)
{
    scanf("%d %d %d %d", &k, &n, &m, &o);
    adj_list.resize(n);
    rev_list.resize(n);
    ans.assign(o, -1);
    initial.resize(o);
    lefty.resize(n, vector<ll>(k));
    righty.resize(n, vector<ll>(k));

    for (int i = 0; i < m; i++) {
        int a, b, t;
        scanf("%d %d %d", &a, &b, &t);

        adj_list[a].pb(mp(b ,t));
        rev_list[b].pb(mp(a, t));
    }

    vector<int> everything(o);
    for (int q = 0; q < o; q++) {
        int l, r;
        everything[q] = q;
        scanf("%d %d", &l, &r);
        initial[q] = mp(l, r);
    }

    divide(0, n, everything);

    for (int i = 0; i < o; i++)
        printf("%d\n", ans[i]);

    return 0;
}