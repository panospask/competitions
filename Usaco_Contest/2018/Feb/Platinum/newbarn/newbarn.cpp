#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int MAXUP = 20;

int N, Q;
vector<int> ancestor[MAXUP];
vector<int> rep;
vector<int> dep;
vector<pi> diameter;

int jump(int a, int b)
{
    for (int up = 0; up < MAXUP; up++) {
        if (b & (1 << up))
            a = ancestor[up][a];
    }

    return a;
}

int calc_dist(int v, int u)
{
    if (rep[v] != rep[u])
        return -1;

    if (dep[v] < dep[u])
        swap(u, v);

    int ans = dep[v] - dep[u];
    v = jump(v, dep[v] - dep[u]);
    if (u == v)
        return ans;

    for (int up = MAXUP - 1; up >= 0; up--) {
        int uv = ancestor[up][v];
        int uu = ancestor[up][u];

        if (uv != uu) {
            v = uv;
            u = uu;
            ans += 2 * (1 << up);
        }
    }

    return ans + 2;
}

void update_ancestors(int v, int p)
{
    diameter.push_back({v, v});
    rep.push_back(0);
    dep.push_back(0);
    rep[v] = p != 0 ? rep[p] : v;
    dep[v] = p != 0 ? dep[p] + 1 : 0;

    ancestor[0].push_back(p);
    for (int up = 1; up < MAXUP; up++) {
        ancestor[up].push_back(ancestor[up - 1][ancestor[up - 1][v]]);
    }

    int r = rep[v];
    int d1 = calc_dist(v, diameter[r].first);
    int d2 = calc_dist(v, diameter[r].second);

    if (d1 > d2) {
        if (d1 > calc_dist(diameter[r].first, diameter[r].second)) {
            diameter[r].second = v;
        }
    }
    else {
        if (d2 > calc_dist(diameter[r].first, diameter[r].second)) {
            diameter[r].first = v;
        }
    }
}

int getmax(int v)
{
    int r = rep[v];
    return max(calc_dist(v, diameter[r].first), calc_dist(v, diameter[r].second));
}

int main(void)
{
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    scanf("%d", &Q);

    diameter.assign(1, {0, 0});
    rep.assign(1, 0);
    N = 1;
    dep.assign(1, 0);
    for (int up = 0; up < MAXUP; up++)
        ancestor[up].push_back(0);

    while (Q--) {
        char op;
        scanf(" %c", &op);

        if (op == 'B') {
            int p;
            scanf("%d", &p);
            if (p == -1)
                p++;

            update_ancestors(N++, p);
        }
        else {
            int v;
            scanf("%d", &v);

            int ans = getmax(v);

            printf("%d\n", ans);
        }
    }

    return 0;
}