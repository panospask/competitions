#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

int n, m;
int maxcontra;
vector<vector<pi>> adj_list;
vector<int> depth;
vector<int> contra_passing;
vector<int> non_contra_passing;
vector<int> col;
vector<bool> onstack;
vector<bool> vis;
int counter = 0;
int latest_contra = 0;
set<int> edges;

void analyze_component(int node, int par=-1, int d = 0)
{
    depth[node] = d;
    contra_passing[node] = non_contra_passing[node] = 0;

    for (auto kid : adj_list[node]) {
        if (kid.f == par)
            continue;

        if (depth[kid.f] == -1) {
            analyze_component(kid.f, node, d + 1);

            contra_passing[node] += contra_passing[kid.f];
            non_contra_passing[node] += non_contra_passing[kid.f];
            if (contra_passing[kid.f] == maxcontra && non_contra_passing[kid.f] == 0)
                edges.insert(kid.s);
        }
        else if (depth[kid.f] < depth[node]) {
            if (depth[kid.f] % 2 == depth[node] % 2)
                contra_passing[node]++;
            else
                non_contra_passing[node]++;
        }
        else {
            if (depth[kid.f] % 2 == depth[node] % 2)
                contra_passing[node]--;
            else
                non_contra_passing[node]--;
        }
    }
}

int dfs(int node, int par = -1, int c = 0, int id = -1)
{
    if (vis[node]) {
        if (c != col[node] && onstack[node]) {
            latest_contra = id;
            return 1;
        }

        else
            return 0;
    }
    vis[node] = true;
    onstack[node] = true;
    col[node] = c;

    int r = 0;
    for (auto kid : adj_list[node]) if (kid.f != par)
    {
        int t = dfs(kid.f, node, (c + 1) % 2, kid.s);
        r += t;


    }

    onstack[node] = false;
    return r;
}

int main(void)
{
    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    vis.assign(n, false);
    depth.assign(n, -1);
    non_contra_passing.resize(n);
    contra_passing.resize(n);
    col.assign(n, -1);
    onstack.assign(n, false);



    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(mp(v,i));
        adj_list[v].push_back(mp(u, i));
    }

    int nonb = 0, contedge = 0;
    int lcomp = 0;
    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            int tmp = dfs(i);
            nonb += tmp > 0;
            if (tmp > 0)
                lcomp = i;
            contedge += tmp;
        }

    if (nonb > 1)
        printf("0\n");
    else if (nonb == 0) {
        printf("%d\n", m);
        for (int i = 0; i < m; i++)
            printf("%d ", i + 1);
    }
    else {
        if (contedge == 1)
            edges.insert(latest_contra);
        maxcontra = contedge;
        analyze_component(lcomp);
        printf("%d\n", (int)edges.size());
        for (auto i : edges)
            printf("%d ", i + 1);
        printf("\n");
    }
}