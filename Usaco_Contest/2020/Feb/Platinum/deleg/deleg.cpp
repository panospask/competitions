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
    int left = -1;
    int smallpaths = 0;

    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        int res = dfs(neigh, node, k);
        if (res == -1)
            return -1;
        res++;

        if (res != 0) {
            kidpaths.insert(res);
            if (res < k)
                smallpaths++;
        }
    }

    int posans = 0;

    while (smallpaths > 0) {
        int v = *kidpaths.begin();

        if (smallpaths == 1 && left == -1 && par != -1)
            posans = v;

        smallpaths--;
        kidpaths.erase(kidpaths.begin());

        auto it = kidpaths.lower_bound(k - v);
        if (it == kidpaths.end()) {
            if (left == -1)
                left = v;
            else
                return -1;
        }
        else {
            if (*it < k)
                smallpaths--;
            kidpaths.erase(it);
        }
    }

    if (left != -1)
        return left;

    if (!kidpaths.empty())
        posans = max(posans, *kidpaths.rbegin());
    return posans;
}

bool works(int val)
{
    int res = dfs(0, -1, val);

    return res == 0 || res >= val;
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