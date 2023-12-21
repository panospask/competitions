#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXVAL = 100;

int N, K;
vector<vector<pi>> kids;
vector<pi> par;

int total, maxtime;

// Returns how much time will pass in order to go to latest node that depends
// on it
int dfs(int node)
{
    int curmax = 0;

    for (auto kid : kids[node]) {
        curmax = max(curmax, dfs(kid.first));
    }

    if (node == 0) {
        return 0;
    }

    curmax += par[node].second;

    if (curmax > maxtime) {
        curmax = 0;
        total++;
    }

    return curmax;
}

bool viable(int m)
{
    maxtime = m;
    total = 1;

    dfs(0);
    return total <= K;
}

int main(void)
{
    freopen("filiki.in", "r", stdin);
    freopen("filiki.out", "w", stdout);

    scanf("%d %d", &N, &K);

    par.resize(N);
    kids.resize(N);

    for (int i = 1; i < N; i++) {
        int p, t;
        scanf("%d %d", &p, &t);
        p--;

        kids[p].pb(mp(i, t));
        par[i] = mp(p, t);
    }

    int l = -1;
    int r = N * MAXVAL;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (viable(mid)) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    printf("%d\n", r);

    return 0;
}