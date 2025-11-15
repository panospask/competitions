#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

ll ceil(ll a, int b) {
    return (a + b - 1) / b;
}

struct Line {
    // ax + b = 0
    int a;
    ll b;

    ll eval(ll v) {
        return a * v + b;
    }
    // Returns ceil of intersection
    ll intersect(Line l) {
        return ceil(l.b - b, a - l.a);
    }
};

int N;
vector<vector<pi>> adj_list;
vector<int> S, V;
vector<int> dist;

// dp[node]: Answer for node
vector<ll> dp;

// hull and stack size
int hullsz = 0;
vector<Line> hull;

void calculate(int node, int par) {
    // Binary search on hull to find optimal line
    int l = 0; // ans >= l
    int r = hullsz; // ans < l

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (hull[mid].eval(V[node]) <= hull[mid - 1].eval(V[node])) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    dp[node] = S[node] + (ll)dist[node] * V[node] + hull[l].eval(V[node]);

    // Insert current line and remove everything necessary (don't forget to store)
    Line cur = {-dist[node], dp[node]};

    // Binary search to find furthest removing position
    l = 0;
    r = hullsz;

    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (hull[mid - 1].intersect(hull[mid]) >= hull[mid].intersect(cur)) {
            // Line at mid is useless and must be removed
            r = mid;
        }
        else {
            // Line at mid remains usefull
            l = mid;
        }
    }

    int prv_size = hullsz;
    // New size of hull
    hullsz = r + 1;

    hull.pb(cur);
    swap(hull[hull.size() - 1], hull[r]);

    for (auto [neigh, w] : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dist[neigh] = dist[node] + w;
        calculate(neigh, node);
    }

    swap(hull[hull.size() - 1], hull[r]);
    hull.pop_back();

    hullsz = prv_size;
}

int main(void) {
    scanf("%d", &N);

    adj_list.resize(N);
    S.resize(N);
    V.resize(N);
    dist.resize(N);
    dp.resize(N);   

    for (int i = 0; i < N - 1; i++) {
        int u, v, d;
        scanf("%d %d %d", &u, &v, &d);
        u--; v--;

        adj_list[u].pb(mp(v, d));
        adj_list[v].pb(mp(u, d));
    }
    for (int i = 1; i < N; i++) {
        scanf("%d %d", &S[i], &V[i]);
    }

    dp[0] = 0;
    hull.push_back({0, 0});
    hullsz = 1;
    for (auto [neigh, w] : adj_list[0]) {
        dist[neigh] = w;
        calculate(neigh, 0);
    }

    for (int i = 1; i < N; i++) {
        printf("%lld ", dp[i]);
    }
    printf("\n");

    return 0;
}