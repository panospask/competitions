#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

vector<ii> adj_list[MAXN + 5];
bool visited[MAXN + 5];
int colour[MAXN + 5];
int n, m;

bool dfs(int node, int parent, int coltype)
{
    if (visited[node]) {
        if (coltype == 0)
            return colour[parent] == colour[node];
        else 
            return colour[parent] != colour[node];
    }

    visited[node] = true;
    colour[node] = (coltype == 0 ? colour[parent] : !colour[parent]);
    
    bool isgood = true;
    for (int i = 0; isgood && i < adj_list[node].size(); i++)
        isgood = dfs(adj_list[node][i].first, node, adj_list[node][i].second);

    return isgood;
}

int main(void)
{
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int a, b;
    char c;
    for (int i = 0; i < m; i++) {
        scanf(" %c %d %d", &c, &a, &b);
        a--; b--;
        if (c == 'S') {
            adj_list[a].pb(mp(b, 0));
            adj_list[b].pb(mp(a, 0));
        }
        else {
            adj_list[a].pb(mp(b, 1));
            adj_list[b].pb(mp(a, 1));
        }
    }

    memset(colour, 0, sizeof(colour));
    memset(visited, 0, sizeof(visited));

    int zeroes = 0;
    bool isgood = true;
    for (int i = 0; i < n && isgood; i++) {
        if (!visited[i]) {
            // Double the options => Add an extra 0 to the end of binary represantation
            zeroes++;
            colour[i] = 0;
            isgood = dfs(i, i, 0);
        }
    }

    if (!isgood)
        printf("0\n");
    else {
        printf("1");
        for (int i = 0; i < zeroes; i++)
            printf("0");
        printf("\n");
    }

    return 0;
}