#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXLOG = 18;

struct State {
    int anc;

    int total;
    int bottom_max;
    int top_max;
    int val;
};

int N, Q;
vector<int> dep;
vector<State> ancestor[MAXLOG][2];

State merge(State& a, State& b)
{
    State c;
    c.anc = b.anc;

    c.total = a.total + b.total;

    c.val = max(a.val, b.val);
    c.val = max(c.val, a.top_max + b.bottom_max);

    c.top_max = max(b.top_max, b.total + a.top_max);
    c.bottom_max = max(a.bottom_max, a.total + b.bottom_max);

    return c;
}

State jump(int a, int lvl, int v)
{
    State cur = {a, 0, 0, 0, 0};
    for (int up = 0; up < MAXLOG; up++)
        if ((1 << up) & lvl) {
            cur = merge(cur, ancestor[up][v][a]);
            a = cur.anc;
        }

    return cur;
}

int lcamax(int a, int b, int v)
{
    if (dep[a] < dep[b])
        swap(a, b);

    State s1 = jump(a, dep[a] - dep[b], v);
    State s2 = {b, 0, 0, 0, 0};
    a = s1.anc;

    if (a == b) {
        s1 = merge(s1, ancestor[0][v][a]);
        return s1.val;
    }

    for (int up = MAXLOG - 1; up >= 0; up--) {
        int n_a = ancestor[up][v][a].anc;
        int n_b = ancestor[up][v][b].anc;

        if (n_a != n_b) {
            s1 = merge(s1, ancestor[up][v][a]);
            s2 = merge(s2, ancestor[up][v][b]);
            a = n_a;
            b = n_b;
        }
    }

    s1 = merge(s1, ancestor[0][v][a]);
    s2 = merge(s2, ancestor[0][v][b]);

    int l = s1.anc;

    int res = max(s1.val, s2.val);
    res = max(res, s1.top_max + s2.top_max + ancestor[0][v][l].total);

    return res;
}

void calculate_ancestor(int i)
{
    for (int up = 1; up < MAXLOG; up++) {
        for (int v = 0; v < 2; v++) {
            ancestor[up][v].push_back(merge(ancestor[up - 1][v][i], ancestor[up - 1][v][ancestor[up - 1][v][i].anc]));
        }
    }
}

int solve(void)
{
    dep.clear();
    for (int up = 0; up < MAXLOG; up++)
        for (int v = 0; v < 2; v++)
            ancestor[up][v].clear();

    scanf("%d", &Q);

    N = 1;
    dep.push_back(0);
    ancestor[0][0].push_back({0, 1, 1, 1, 1});
    ancestor[0][1].push_back({0, -1, 0, 0, 0});
    calculate_ancestor(0);

    while (Q--) {
        char op;
        scanf(" %c", &op);

        if (op == '+') {
            int p, v;
            scanf("%d %d", &p, &v);
            p--;

            dep.push_back(dep[p] + 1);
            int r = max(v, 0);
            int t = max(-v, 0);
            ancestor[0][0].push_back({p, v, r, r, r});
            ancestor[0][1].push_back({p, -v, t, t, t});

            calculate_ancestor(N++);
        }
        else {
            int u, v, k;
            scanf("%d %d %d", &u, &v, &k);
            u--; v--;

            int mod = 0;
            if (k < 0)
                mod = 1;

            int res = lcamax(u, v, mod);
            if (res >= abs(k))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }

    return 0;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}