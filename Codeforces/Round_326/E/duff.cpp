#include <bits/stdc++.h>
#define pb push_back

using namespace std;

struct State {
    int anc;
    vector<int> mins;
};

const int MAXLOG = 20;
const int MAXA = 10;

int N, M, Q;
vector<vector<int>> adj_list;
vector<int> dep;
vector<State> ancestor[MAXLOG];

vector<int> make_mins(vector<int> a, vector<int> b, int cut)
{
    vector<int> c;
    int p1 = 0, p2 = 0;
    while (p1 < a.size() && p2 < b.size() && p1 + p2 < cut) {
        if (a[p1] < b[p2])
            c.pb(a[p1++]);
        else
            c.pb(b[p2++]);
    }
    while (p1 < a.size() && p1 + p2 < cut) {
        c.pb(a[p1++]);
    }
    while (p2 < b.size() && p1 + p2 < cut) {
        c.pb(b[p2++]);
    }

    return c;
}

State jump(int a, int lvl, int cut)
{
    State cur;
    cur.anc = a;
    cur.mins.clear();

    for (int up = 0; up < MAXLOG; up++)
        if ((1 << up) & lvl) {
            cur.mins = make_mins(cur.mins, ancestor[up][cur.anc].mins, cut);
            cur.anc = ancestor[up][cur.anc].anc;
        }

    return cur;
}

vector<int> getpath(int a, int b, int cut)
{
    if (dep[a] < dep[b])
        swap(a, b);

    State s = jump(a, dep[a] - dep[b], cut);
    vector<int> res = s.mins;
    a = s.anc;

    if (a == b) {
        return make_mins(res, ancestor[0][a].mins, cut);
    }

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int aa = ancestor[up][a].anc;
        int ab = ancestor[up][b].anc;

        if (aa != ab) {
            res = make_mins(res, ancestor[up][a].mins, cut);
            res = make_mins(res, ancestor[up][b].mins, cut);
            a = aa;
            b = ab;
        }
    }

    res = make_mins(res, ancestor[0][a].mins, cut);
    res = make_mins(res, ancestor[0][b].mins, cut);
    res = make_mins(res, ancestor[0][ancestor[0][a].anc].mins, cut);

    return res;
}

void dfs(int node)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == ancestor[0][node].anc)
            continue;

        ancestor[0][neigh].anc = node;
        dep[neigh] = dep[node] + 1;
        dfs(neigh);
    }
}

void calculate_ancestors(void)
{
    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N + 1);
        for (int i = 0; i <= N; i++) {
            int u = ancestor[up - 1][i].anc;
            ancestor[up][i].anc = ancestor[up - 1][u].anc;
            ancestor[up][i].mins = make_mins(ancestor[up - 1][i].mins, ancestor[up - 1][u].mins, MAXA);
        }
    }
}

int main(void)
{
    scanf("%d %d %d", &N, &M, &Q);

    adj_list.resize(N);
    dep.resize(N);
    ancestor[0].resize(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }
    for (int i = 0; i < M; i++) {
        int v;
        scanf("%d", &v);

        ancestor[0][--v].mins.pb(i);
    }

    ancestor[0][0].anc = N;
    ancestor[0][N].anc = N;
    dep[0] = 0;
    dfs(0);
    calculate_ancestors();

    while (Q--) {
        int v, u, a;
        scanf("%d %d %d", &v, &u, &a);
        v--; u--;

        vector<int> ans = getpath(v, u, a);

        printf("%d", (int)ans.size());
        for (auto v : ans)
            printf(" %d", v + 1);
        printf("\n");
    }
}