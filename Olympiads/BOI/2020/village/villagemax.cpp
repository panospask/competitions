#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<int> subtree;
vector<int> dep;
vector<int> target;
long long ans = 0;

void dfs(int node, int par)
{
    subtree[node] = 1;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
        subtree[node] += subtree[neigh];
    }
}

int find_centroid(int node, int par)
{
    for (auto neigh : adj_list[node]) {
        if (neigh != par && subtree[neigh] > N / 2) {
            return find_centroid(neigh, node);
        }
    }

    return node;
}

void traverse(int node, int par, vector<int>& l)
{
    dep[node] = dep[par] + 1;
    l.push_back(node);
    ans += 2 * dep[node];

    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            traverse(neigh, node, l);
        }
    }
}

bool vec_cmp(vector<int>& a, vector<int>& b)
{
    return a.size() > b.size();
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    subtree.resize(N);
    dep.resize(N);
    target.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    dfs(0, 0);
    int cen = find_centroid(0, 0);

    vector<vector<int>> kidlist;
    kidlist.push_back({cen});
    dep[cen] = 0 ;
    for (auto kid : adj_list[cen]) {
        kidlist.push_back({});
        traverse(kid, cen, kidlist.back());
    }

    sort(kidlist.begin(), kidlist.end(), vec_cmp);

    vector<vector<int>> tarlist = kidlist;
    tarlist.push_back(tarlist.front());
    tarlist.erase(tarlist.begin());

    int p1 = 0, p2 = 0;
    for (int i = 0; i < kidlist.size(); i++) {
        for (int j = 0; j < kidlist[i].size(); j++) {
            if (p2 == tarlist[p1].size()) {
                p1++;
                p2 = 0;
            }    
            target[kidlist[i][j]] = tarlist[p1][p2];
            p2++;
        }
    }

    printf("%lld\n", ans);
    for (int i = 0; i < N; i++) {
        printf("%d ", target[i] + 1);
    }
    printf("\n");

    return 0;
}