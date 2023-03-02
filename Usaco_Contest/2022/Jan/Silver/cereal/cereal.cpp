#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

typedef pair<int, int> ii;

struct edge {
    int cow;
    int to;
    bool preffered;

    edge(void) {;}
    edge(int t, int c, bool p) {
        to = t;
        cow = c;
        preffered = p;
    }
};
typedef struct edge Edge;

int n, m;
vector<Edge> adj_list[MAXN + 5];
queue<int> order;
bool visited[MAXN + 5];
bool in_cycle[MAXN + 5];
bool gets_cereal[MAXN + 5];
int firstnode;
int ignore_edge;

void find_cycle(int node, int prev)
{
    in_cycle[node] = true;

    for (auto neigh : adj_list[node]) {
        if (in_cycle[neigh.to]) {
            if (firstnode != -1 || prev == neigh.to)
                continue;

            if (neigh.preffered) { 
                firstnode = neigh.to;
            }
            else {
                firstnode = node;
            }

            ignore_edge = neigh.cow;
            order.push(neigh.cow);
            gets_cereal[neigh.cow] = true;
        }
        else {
            find_cycle(neigh.to, node);
        }
    }
}

void dfs(int node)
{
    if (visited[node]) {
        return;
    }

    visited[node] = true;
    for (auto neigh : adj_list[node]) {
        if (neigh.cow != ignore_edge && !visited[neigh.to]) {
            gets_cereal[neigh.cow] = true;
            order.push(neigh.cow); 
            dfs(neigh.to);
        }
    }
}

int main(void)
{
    // freopen("cereal.in", "r", stdin);
    // freopen("cereal.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int a, b;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;
        adj_list[a].pb(Edge(b, i, false));
        adj_list[b].pb(Edge(a, i, true));
    }

    for (int i = 0; i < m; i++) {
        if (!visited[i]) {
            ignore_edge = -1;
            firstnode = -1;

            find_cycle(i, -1);
            if (firstnode == -1) {
                // No cycle found, it is a tree
                dfs(i);
            }
            else {
                dfs(firstnode);
            }
        }
    }

    int ans = n - order.size();
    for (int i = 0 ; i < n; i++)
        if (!gets_cereal[i])
            order.push(i);

    printf("%d\n", ans);
    for (int i = 0; i < n; i++) {
        printf("%d\n", order.front() + 1);
        order.pop();
    }

    return 0;
}