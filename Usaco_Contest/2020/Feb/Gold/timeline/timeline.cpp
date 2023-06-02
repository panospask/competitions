#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

int n, m, c;
vector<int> earliest;
vector<vector<pi>> adj_list;
vector<int> topsort;
vector<int> dp;
vector<int> indeg;

void make_topsort(void)
{
    queue<int> q;

    for (int i = 0; i < n; i++)
        if (indeg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        topsort.pb(cur);

        for (auto neigh : adj_list[cur]) {
            indeg[neigh.f]--;
            if (indeg[neigh.f] == 0)
                q.push(neigh.f);
        }
    }
}

int main(void)
{
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);

    scanf("%d %d %d", &n, &m, &c);

    earliest.resize(n);
    adj_list.resize(n);
    indeg.assign(n, 0);

    for (int i = 0; i < n; i++)
        scanf("%d", &earliest[i]);


    for (int i = 0; i < c; i++) {
        int u, v, x;
        scanf("%d %d %d", &u, &v, &x);
        u--; v--;

        adj_list[u].pb(mp(v, x));
        indeg[v]++;
    }

    make_topsort();


    dp.assign(n, 0);
    for (int i = 0; i < n; i++) {
        int cur = topsort[i];

        dp[cur] = max(dp[cur], earliest[cur]);

        for (auto neigh : adj_list[cur]) {
            dp[neigh.f] = max(dp[neigh.f], dp[cur] + neigh.s);
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", dp[i]);

    return 0;
}