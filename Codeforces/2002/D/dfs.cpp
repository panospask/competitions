#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, Q;
vector<int> a;
vector<int> pos;
vector<vector<int>> kids;
vector<bool> good;
vector<int> subtree;

int PAIRS = 0;
int rem;

bool test(int x)
{
    int p1 = pos[2 * x + 1];
    int p2 = pos[2 * x + 2];
    int sz = subtree[2 * x + 1];
    bool par = false;

    if (min(p1, p2) == 0) {
        return false;
    }

    return a[min(p1, p2) - 1] == x && abs(p1 - p2) == sz;
}

void recalc(int x)
{
    if (x >= PAIRS) {
        return;
    }

    bool cur = test(x);

    rem += good[x] - cur;

    good[x] = cur;
}

void dfs(int node)
{
    subtree[node] = 1;
    for (auto neigh : kids[node]) {
        dfs(neigh);
        subtree[node] += subtree[neigh];
    }
}

void solve(void)
{
    scanf("%d %d", &N, &Q);

    PAIRS = (N - 1) / 2;
    a.resize(N);
    pos.resize(N);
    kids.assign(N, vector<int>());
    subtree.resize(N);

    rem = PAIRS;
    good.assign(PAIRS, false);

    for (int i = 1; i < N; i++) {
        int p;
        scanf("%d", &p);
        p--;

        kids[p].pb(i);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        a[i]--;

        pos[a[i]] = i;
    }

    dfs(0);

    for (int i = 0; i < PAIRS; i++) {
        if (test(i)) {
            good[i] = true;
            rem--;
        }
    }

    while (Q--) {
        int i, j;
        scanf("%d %d", &i, &j);
        i--; j--;

        int v1 = a[i];
        int v2 = a[j];

        swap(a[i], a[j]);
        swap(pos[v1], pos[v2]);

        recalc((v1 - 1) / 2);
        recalc((v2 - 1) / 2);
        recalc(v1);
        recalc(v2);

        if (!rem && a[0] == 0) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}