#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<map<int, ll>> spec_cases;
vector<vector<int>> adj_list;
vector<int> a;
vector<int> f;
vector<ll> opt;
vector<ll> child_opt;

void calculate(int node, int par)
{
    for (auto kid : adj_list[node]) {
        if (kid == par)
            continue;

        calculate(kid, node);
        child_opt[node] += opt[kid];
    }

    // Find min bigger than this
    int m = INT_MAX;
    for (int i = a[i] + 1; i <= n; i++)
        m = min(m, f[i]);

    opt[node] = child_opt[node] + m;

    // Check for any interesting special cases

    // 0 first
    for (auto kid : adj_list[node]) {
        if (a[kid] == 0) {
            if (spec_cases[node].find(a[node] + 1) == spec_cases[node].end())
                spec_cases[node][a[node] + 1] = child_opt[node] + f[a[node] + 1];

            spec_cases[node][a[node] + 1] -= opt[kid];
            ll b = child_opt[kid];
            if (a[node] == 0 && spec_cases[kid].find(a[node] + 1) != spec_cases[kid].end())
                b = min(b, spec_cases[kid][a[node] + 1] - f[a[node] + 1]);

            spec_cases[node][a[node] + 1] += b;
        }
        else if (a[kid] == a[node] + 1) {
            ;
        }

        spec_cases[kid].clear();
    }
}

int main(void)
{
    ;
}