#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int n, k;
vector<int> b;
vector<int> dist;
vector<vector<bool>> vis;
vector<bool> used;
vector<vector<int>> cows;
vector<vector<int>> acceptable;

int main(void)
{
    // freopen("telephone.in", "r", stdin);
    // freopen("telephone.out", "w", stdout);

    scanf("%d %d", &n, &k);
    b.resize(n);
    cows.resize(k);
    acceptable.resize(k);
    dist.resize(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        b[i]--;

        cows[b[i]].pb(i);;
    }

    for (int b1 = 0; b1 < k; b1++) {
        for (int b2 = 0; b2 < k; b2++) {
            int a;
            scanf("%1d", &a);
            if (a)
                acceptable[b1].pb(b2);
        }
    }

    priority_queue<pi, vector<pi>, greater<pi>> q;
    int ans = -1;
    dist.assign(n, INT_MAX);
    dist[0] = 0;
    q.push(mp(0, 0));
    used.resize(n, false);
    vis.assign(k, vector<bool>(k, false));

    while (!q.empty()) {
        int v = q.top().second; q.pop();

        if (used[v])
            continue;

        if (v == n -1) {
            ans = dist[v];
            break;
        }

        for (auto breed : acceptable[b[v]]) {
            // Place them in queue based on dist from v
            int f = lower_bound(cows[breed].begin(), cows[breed].end(), v) - cows[breed].begin() - 1;
            for (int i = f; i >= 0; i--) {
                int cur = cows[breed][i];
                if (cur == v)
                    continue;

                int d = dist[v] + abs(cur - v);
                if (d < dist[cur]) {
                    dist[cur] = d;
                    q.push(mp(dist[cur], cur));
                }
                else
                    break;
            }
            for (int i = f + 1; i < cows[breed].size(); i++) {
                int cur = cows[breed][i];
                if (cur == v)
                    continue;

                int d = dist[v] + abs(cur - v);
                if (d < dist[cur]) {
                    dist[cur] = d;
                    q.push(mp(dist[cur], cur));
                }
                else
                    break;
            }
        }

        used[v] = true;
    }

    printf("%d\n", ans);
    return 0;
}