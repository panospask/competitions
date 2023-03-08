#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 1000

using namespace std;

struct statement {
    int target_cow;
    bool same_col;
    int id;

    statement(int a, int b, int c) {
        target_cow = a; 
        same_col = b;
        id = c;
    }
};
typedef struct statement Statement;

vector<Statement> adj_list[MAXN + 2];
int n, m;
bool visited[MAXN + 2];
bool col[MAXN + 2];

bool dfs(int node, int colour, int a)
{
    if (visited[node]) {
        if (col[node] == colour)
            return true;
        else 
            return false;
    }

    visited[node] = true;
    col[node] = colour;

    bool isgood = true;
    for (auto& neigh : adj_list[node]) {
        if (neigh.id >= a) break;

        if (neigh.same_col)
            isgood = isgood && dfs(neigh.target_cow, colour, a);
        else 
            isgood = isgood && dfs(neigh.target_cow, !colour, a);
    }

    return isgood;
}

bool consistent(int a)
{
    memset(visited, false, sizeof(visited));

    bool isgood = true;
    for (int i = 0; i < n && isgood; i++)
        if (!visited[i]) {
            isgood = isgood && dfs(i, 0, a);
        }

    return isgood;
}

int main(void)
{
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);

    scanf("%d %d", &n, &m);

    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %c", &a, &b, &c);
        a--; b--;
        bool same = c == 'T';

        adj_list[a].pb(Statement(b,same,i));
        adj_list[b].pb(Statement(a,same,i));
    }

    int l = 0; //consistent(l) = true;
    int r = m + 1; //consistent(r) = false;

    while (r > l + 1) {
        auto mid = (l + r) / 2;
        if (consistent(mid))
            l = mid;
        else 
            r = mid;
    }

    printf("%d\n", l);
    return 0;
}