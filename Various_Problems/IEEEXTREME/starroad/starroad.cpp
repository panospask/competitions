#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

const int INF = 1e6;

typedef pair<int, int> pi;

// m[i][v]: Highest possible number of restaurants if you are at i and have eaten at most v stars
vector<set<pi>> inc, dcr;

int N;
vector<vector<int>> adj_list;
vector<int> stars;
int ans = 0;

void makemax(int& a, int b)
{
    if (a < b) {
        a = b;
    }
}

void merge(set<pi>& a, set<pi>& b)
{
    if (a.size() < b.size()) {
        swap(a, b);
    }

    for (auto u : b) {
        auto it = a.lower_bound(mp(u.first, INF));

        if (it != a.begin()) {
            it--;

            pi v = *it;
            if (v.second >= u.second) {
                continue;
            }
            if (v.first == u.first) {
                a.erase(it);
            }
        }

        a.insert(u);
        it = a.find(u);
        it++;

        while (it != a.end()) {
            if ((*it).second <= u.second) {
                a.erase(it);
                it = a.find(u);
                it++;
            }
            else {
                break;
            }
        }
    }
}

void calculate(set<pi>& a, set<pi>& b)
{
    bool s = false;
    if (a.size() < b.size()) {
        swap(a, b);
        s = true;
    }

    for (auto u : b) {
        auto it = a.lower_bound(mp(-u.first - 1, INF));

        if (it != a.begin()) {
            it--;
            makemax(ans, u.second + (*it).second);
        }
    }

    if (s) {
        swap(a, b);
    }
}

void dfs(int node, int par)
{
    inc[node].insert(mp(stars[node], 1));
    dcr[node].insert(mp(-stars[node], 1));
    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        calculate(inc[neigh], dcr[node]);
        calculate(dcr[neigh], inc[node]);

        // Calculate for node itself
        int v1 = 1, v2 = 1;
        auto it1 = inc[neigh].lower_bound(mp(stars[node] - 1, INF));
        if (it1 != inc[neigh].begin()) {
            it1--;
            v1 = 1 + (*it1).second;
        }
        auto it2 = dcr[neigh].lower_bound(mp(-stars[node] - 1, INF));
        if (it2 != dcr[neigh].begin()) {
            it2--;
            v2 = 1 + (*it2).second;
        }

        set<pi> s1 = {mp(stars[node], v1)};
        set<pi> s2 = {mp(-stars[node], v2)};
        merge(inc[node], inc[neigh]);
        merge(dcr[node], dcr[neigh]);
        merge(inc[node], s1);
        merge(dcr[node], s2);
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    inc.resize(N);
    dcr.resize(N);
    stars.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &stars[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    ans = 1;
    dfs(0, -1);
    for (auto v : inc[0]) {
        ans = max(ans, v.second);
    }
    for (auto v : dcr[0]) {
        ans = max(ans, v.second);
    }

    printf("%d\n", ans);

    return 0;
}