#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

vector<int> adj_list[MAXN + 2];
bool milk[MAXN + 2];
int belongs_to[MAXN + 2];
int component[MAXN + 2];
int n, m;
string s;

void dfs(int node, int parent, int cur_comp)
{
    if (milk[node] != component[cur_comp])
        return;

    belongs_to[node] = cur_comp;
    for (auto child : adj_list[node])
        if (child != parent)
            dfs(child, node, cur_comp);
}

int main(void)
{
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    scanf("%d %d", &n, &m);
    
    int a, b;
    char c;
    getchar();
    for (int i = 0; i < n; i++) {
        c = getchar();
        milk[i] = c == 'G';
        belongs_to[i] = -1;
    }
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    int ttl_comp = 0;
    for (int i = 0; i < n; i++) {
        if (belongs_to[i] == -1) {
            component[ttl_comp] = milk[i];
            dfs(i, i, ttl_comp);
            ttl_comp++;
        }
    }

    for (int q = 0; q < m; q++) {
        int a, b; 
        char c;
        scanf("%d %d %c", &a, &b, &c);
        a--; b--;

        int milktype = c == 'G';

        bool ishappy = true;
        if (belongs_to[a] == belongs_to[b] && milk[a] != milktype)
            ishappy = false;

        printf("%d", ishappy);
    }
    printf("\n");
    return 0;
}