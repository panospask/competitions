#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

struct Query {
    int dest;
    int col;
    int id;
};

int n, m;

const int C = 1e5 + 5;

vector<stack<int>> latest_oc;
vector<vector<int>> adj_list;
vector<int> anc_at;
vector<int> t;
vector<int> ans;
vector<vector<Query>> queries;

int counter = 0;
vector<int> tin;
vector<int> tout;
vector<int> depth;

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void answer_queries(int node, int par)
{
    anc_at.push_back(node);
    latest_oc[t[node]].push(node);

    for (auto& q : queries[node]) {
        int y = latest_oc[q.col].top();

         if (y == -1)
            continue;

        if (y == node) {
            ans[q.id] = true;
        }
        else if (!ancestor(y, q.dest)) {
            ans[q.id] = true;
        }
        else if (!ancestor(anc_at[depth[y] + 1], q.dest)) {
            ans[q.id] = true;
        }
    }

    for (auto neigh : adj_list[node])
        if (neigh != par)
            answer_queries(neigh, node);

    anc_at.pop_back();
    latest_oc[t[node]].pop();
}

void dfs(int node, int par)
{
    depth[node] = par != -1 ? depth[par] + 1 : 0;

    tin[node] = counter++;

    for (auto neigh : adj_list[node])
        if (neigh != par)
            dfs(neigh, node);

    tout[node] = counter;
}

int main(void)
{
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    scanf("%d %d", &n, &m);

    t.resize(n);
    adj_list.resize(n);
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    queries.resize(n);

    ans.assign(m, false);

    latest_oc.resize(C);
    for (int i = 1; i < C; i++)
        latest_oc[i].push(-1);


    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        a--; b--;

        queries[a].push_back({b, c, i});
        queries[b].push_back({a, c, i});
    }

    dfs(0, -1);
    answer_queries(0, -1);

    for (int i = 0; i < m; i++)
        printf("%d", ans[i]);
    printf("\n");

    return 0;
}