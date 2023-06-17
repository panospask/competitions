#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int n;
vector<vector<int>> adj_list;

// If the returnval is k, it can mean any path greater than or equal to k
int dfs(int node, int par, int k)
{
    multiset<int> kidpaths;

    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        int res = dfs(neigh, node, k);
        if (res == -1)
            return -1;

        if (res != 0) {
            kidpaths.insert(res);
        }
    }

    while (kidpaths.size() > 2 && *kidpaths.begin() < k) {
        int small = *kidpaths.begin();

        if (2 * small >= k) {
            // We reached the point
            while (kidpaths.size() > 2 && *kidpaths.begin() < k) {
                kidpaths.erase(kidpaths.begin());
                kidpaths.erase(kidpaths.begin());
            }
        }
        else {
            auto it = kidpaths.lower_bound(k - small);
            if (it == kidpaths.end()) {
                return -1;
            }
            else {
                kidpaths.erase(it);
                kidpaths.erase(kidpaths.begin());
            }
        }
    }

    int len = par != -1;
    if (kidpaths.size() == 2) {
        if (*kidpaths.rbegin() + *kidpaths.begin() < k)
            return -1;
        if (*kidpaths.rbegin() >= k && par != -1) {
            len += *kidpaths.begin();
        }
    }
    else if (kidpaths.size() == 1) {
        len += *kidpaths.begin();
    }

    return len;
}

bool works(int val)
{
    int ans = dfs(0, -1, val);

    return ans == 0 || ans >= val;
}

int main(void)
{
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);

    scanf("%d", &n);

    adj_list.resize(n);

    for (int i = 0; i < n - 1; i++ ) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    int l = 1;
    int r = n;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (works(mid))
            l = mid;
        else
            r = mid;
    }

    printf("%d\n", l);

    return 0;
}