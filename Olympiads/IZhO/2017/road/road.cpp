#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<ll, ll> pi;

int N;
vector<vector<int>> adj_list;
vector<ll> d;
vector<ll> c;
pi ans;

void calc_height(int node, int par)
{
    d[node] = 0, c[node] = 1;

    for (auto neigh : adj_list[node]) if (neigh != par){
        calc_height(neigh, node);

        if (d[neigh] + 1 > d[node]) {
            d[node] = d[neigh] + 1;
            c[node] = c[neigh];
        }
        else if (d[neigh] + 1 == d[node]) {
            c[node] += c[neigh];
        }
    }
}

void calculate_hardness(int node, int par, int outside_distance, int outside_count)
{
    vector<pi> paths;
    if (par != -1 || adj_list[node].size() == 1)
        paths.pb(mp(outside_distance, outside_count));

    for (auto neigh : adj_list[node]) if (neigh != par)
        paths.pb(mp(d[neigh] + 1, c[neigh]));

    sort(paths.begin(), paths.end(), [&] (pi&a, pi& b) {return a > b;});

    if (paths.size() >= 3 && paths[0].f * (paths[1].f + paths[2].f) >= ans.f) {
        // Calculate maximum distance
        // Paths that are available are : c[1] * c[2] (if all dist are distinct)
        ll curdist = paths[0].f * (paths[1].f + paths[2].f);
        ll third_chances = 0;
        ll total_chances = 0;

        for (auto p : paths)
            if (p.f == paths[2].f)
                third_chances += p.s;

        if (paths[1].f == paths[2].f) {
            // Many pairing possibilities
            total_chances = third_chances * third_chances;
            for (auto p : paths)
                if (p.f == paths[2].f) {
                    // Remove the chances going into the same path twice
                    total_chances -= (p.s) * (p.s);
                }

            // We have doublecounted each path(front to back and back to front)
            // It is the same path, therefore half the result
            total_chances /= 2;
        }
        else if (paths[0].f == paths[1].f) {
            // We can use both first and second paths in our chance calculation
            total_chances = third_chances * (paths[0].s + paths[1].s);
        }
        else {
            // All distinct
            total_chances = third_chances * paths[1].s;
        }

        if (ans.f < curdist) {
            ans = mp(curdist, total_chances);
        }
        else {
            ans.s += total_chances;
        }
    }

    // Calculate the best path to give to children
    ll d1 = paths[0].f + 1;
    ll d2 = 0;
    ll c2 = 1;
    ll c1 = 0;
    if (paths.size() >= 2) {
        d2 = paths[1].f + 1;
        c2 = 0;

        for (auto p : paths) {
            if (p.f + 1 == d1)
                c1 += p.s;
            if (p.f + 1 == d2)
                c2 += p.s;
        }
    }

    paths.clear();
    for (auto neigh : adj_list[node]) {
        if (neigh != par) {
            if (d[neigh] + 2 == d1 && c[neigh] == c1)
                calculate_hardness(neigh, node, d2, c2);
            else if (d[neigh] + 2 == d1)
                calculate_hardness(neigh, node, d1, c1 - c[neigh]);
            else
                calculate_hardness(neigh, node, d1, c1);
        }
    }
}

int main(void)
{
    scanf("%d", &N);

    adj_list.resize(N);
    d.resize(N);
    c.resize(N);
    ans = mp(0, 1);

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calc_height(0, -1);
    calculate_hardness(0, -1, 0, 1);

    printf("%lld %lld\n", ans.f, ans.s);

    return 0;
}