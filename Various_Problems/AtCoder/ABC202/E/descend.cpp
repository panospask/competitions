#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

struct Query {
    int id;
    int d;
    int mod;
    int at;
};

int n, q;
vector<vector<int>> kids;
vector<int> tin;
vector<int> tout;
vector<int> depthcount;
vector<int> depth;

vector<Query> queries;
vector<int> ans;

vector<int> euler;

int counter = 0;

void dfs(int node, int d)
{
    tin[node] = counter++;
    euler.pb(node);
    depth[node] = d;

    for (auto kid : kids[node])
        dfs(kid, d + 1);

    tout[node] = counter++;
    euler.pb(node);
}

int main(void)
{
    scanf("%d", &n);

    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    depthcount.resize(n);
    kids.resize(n);

    for (int i = 1; i < n; i++) {
        int p;
        scanf("%d", &p);
        p--;

        kids[p].push_back(i);
    }

    dfs(0, 0);

    scanf("%d", &q);
    queries.resize(2 * q);
    ans.resize(q);

    for (int i = 0; i < q; i++) {
        int a, d;
        scanf("%d %d", &a, &d);
        a--;

        queries[2 * i].id = queries[2 * i + 1].id = i;
        queries[2 * i].d = queries[2 * i + 1].d = d;

        queries[2 * i].mod = 1;
        queries[2 * i].at = tout[a];

        queries[2 * i + 1].mod = -1;
        queries[2 * i + 1].at = tin[a];
    }
    sort(queries.begin(), queries.end(), [&] (Query& a, Query& b) {return a.at < b.at;});

    int curp = 0;
    depthcount.assign(n, 0);
    ans.assign(q, 0);
    for (int i = 0; i < 2 * n; i++) {
        while (curp < 2 * q && queries[curp].at == i) {
            Query cur = queries[curp++];

            ans[cur.id] += depthcount[cur.d] * cur.mod;
        }

        if (tin[euler[i]] == i)
            depthcount[depth[euler[i]]]++;
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}