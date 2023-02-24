#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

vector<ii> adj_list[MAXN];
int p[MAXN];
double mincost[MAXN];
int n, m;

bool can_have_x_mean(double x)
{
    for (int i = 0; i < n; i++)
        mincost[i] = INFINITY;

    mincost[0] = 0;
    p[0] = 0;
    for (int node = 0; node < n; node++) {
        if (mincost[node] == INFINITY) continue;
        if (node == n - 1) {
            if (mincost[node] <= 0) return true;
            else return false;
        }

        for (auto neigh : adj_list[node]) {
            if (mincost[node] + neigh.second - x < mincost[neigh.first]) {
                mincost[neigh.first] = mincost[node] + neigh.second - x;
                p[neigh.first] = node;
            }
        }
    }

    return false;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    int n1, n2, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &n1, &n2, &c);
        adj_list[--n1].pb(mp(--n2, c));
    }

    double l = 0; //can_have_x_mean(l) = false
    double r = 100; //can_have_x_mean(r) = true
    for (int i = 0; i < 50; i++) {
        double m = (l + r) / 2;
        if (!can_have_x_mean(m))
            l = m;
        else 
            r = m;
    }

    can_have_x_mean(r);
    vector<int> curpath;
    int curnode = n - 1;
    while (curnode != 0) {
        curpath.pb(curnode);
        curnode = p[curnode];
    } 
    curpath.pb(0);
    reverse(curpath.begin(), curpath.end());
    printf("%d\n", (int)curpath.size() - 1);
    for (auto v : curpath)
        printf("%d ", v+ 1);
    return 0;
}