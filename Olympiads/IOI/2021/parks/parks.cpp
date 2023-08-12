#include "parks.h"
#include "map"
#include "unordered_map"
#include <bits/stdc++.h>

#define f first
#define s second
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int MAXV = 200000;

const int DIRS = 4;
const int d_x[] = {2, 0, -2, 0};
const int d_y[] = {0, 2, 0, -2};

int N;

vector<int> u, v, a, b;

int res = 0;
map<pi, bool> state;
vector<vector<pi>> xcoord;
vector<int> define_side;

void dfs(pi node)
{
    if (state.find(node) == state.end() || state[node])
        return;

    state[node] = true;
    res++;

    for (int d = 0; d < DIRS; d++) {
        dfs(mp(node.f + d_x[d], node.s + d_y[d]));
    }
}

int find(int x, int y)
{
    int p = lower_bound(xcoord[x].begin(), xcoord[x].end(), mp(y, 0)) - xcoord[x].begin();
    if (p != xcoord[x].size() && xcoord[x][p].f == y)
        return xcoord[x][p].s;

    return -1;
}

void make_road(int k, int l, int m, int n)
{
    u.pb(k);
    v.pb(l);
    a.pb(m);
    b.pb(n);
}

int construct_roads(vector<int> X, vector<int> Y)
{
    N = X.size();

    define_side.assign(N, 0);
    xcoord.resize(MAXV + 3);

    bool sub3 = true;
    for (int i = 0; i < N; i++) {
        state[mp(X[i], Y[i])] = 0;
        xcoord[X[i]].pb(mp(Y[i], i));
        sub3 = sub3 && X[i] <= 6;
    }

    dfs(mp(X[0], Y[0]));
    if (res < N)
        return 0;

    for (int x = 2; x <= MAXV; x += 2)
        sort(xcoord[x].begin(), xcoord[x].end());

    int prv_start = 1;
    for (int x = 2; x <= MAXV; x += 2) {

        // Propagate side definitions from top to bottom
        int p_y = -1;
        int p_id = -1;
        for (int i = xcoord[x].size() - 1; i >= 0; i--) {
            int y, id;
            tie(y, id) = xcoord[x][i];

            if (y + 2 == p_y && define_side[p_id] && !define_side[id])
                define_side[id] = define_side[p_id];
            p_y = y;
            p_id = id;
        }

        int cur = -prv_start;
        p_y = -1;
        p_id = -1;
        bool built_prv_back = false;
        bool built_prv_front = false;
        for (auto [y, id] : xcoord[x]) {
            if (sub3 && x == 2)
                cur = -1;
            if (sub3 && x == 6)
                cur = 1;

            if (p_y + 2 == y) {
                make_road(p_id, id, x + cur, y - 1);
            }
            else {
                if (define_side[id])
                    cur = define_side[id];
                built_prv_back = built_prv_front = false;
            }

            bool swap = false;
            if (!built_prv_back && (!sub3 || x != 6)) {
                int back_id = find(x - 2, y);
                if (back_id != -1) {
                    swap = true;
                    built_prv_back = true;
                    make_road(id, back_id, x - 1, y - cur);
                }
            }
            else {
                built_prv_back = false;
            }

            if (!built_prv_front) {
                int front_id = find(x + 2, y);
                if (front_id != -1) {
                    built_prv_front = true;
                    swap = true;
                    define_side[front_id] = -cur;

                    if (sub3 && x == 4) {
                        make_road(id, front_id, x + 1, y + cur);
                    }
                }
            }
            else {
                built_prv_front = false;
            }

            if (swap)
                cur = -cur;

            p_id = id;
            p_y = y;
        }
    }

    build(u, v, a, b);

    return 1;
}