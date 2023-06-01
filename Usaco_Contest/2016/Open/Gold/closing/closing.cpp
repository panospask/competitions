#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct UnionFind {

    int size;
    int components;
    int largest = 0;
    vector<int> rep;
    vector<int> nodes;

    void init(int n) {
        size = n;
        components = n;
        nodes.assign(size, 1);
        largest = 1;

        rep.resize(size);
        for (int i = 0; i < rep.size(); i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (nodes[b] > nodes[a])
            swap(a, b);

        rep[b] = a;
        nodes[a] += nodes[b];
        largest = max(largest, nodes[a]);

        components--;
    }
};

int n, m, q;
vector<vector<pi>> Queries;
vector<vector<int>> adj_list;
vector<bool> closed;
UnionFind dsu;
vector<int> ans;

int main(void)
{
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);

    scanf("%d %d", &n, &m);
    adj_list.resize(n);
    Queries.resize(n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    closed.assign(n, false);
    for (int i = 0; i < n; i++) {
        int barn;
        scanf("%d", &barn);
        barn--;

        for (auto& e : adj_list[barn])
            if (!closed[e])
                Queries[i].push_back(mp(barn, e));

        closed[barn] = true;
    }

    dsu.init(n);
    ans.resize(n);
    for (int q = n - 1; q >= 0; q--) {
        for (auto& edge : Queries[q]) {
            dsu.unite(edge.first, edge.second);
        }

        ans[q] = dsu.largest == n - q;
    }

    for (int i = 0; i < n; i++) {
        if (ans[i])
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}