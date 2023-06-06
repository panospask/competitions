/* The task can be reformulated as creating a MaximumST
 * Notice that the MaximumST will contain the highest value edges possible.
 * A cycle in not allowed since in every game a team must be eliminated.
 */

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;

int n;
vector<bool> used;
vector<int> mdist;
vector<int> id;

// Returns the position of mdist with the highest value that is not used
int find_max()
{
    int maxv = -1, maxid = -1;
    for (int i = 0; i < n; i++)
        if (!used[i] && mdist[i] > maxv) {
            maxv = mdist[i];
            maxid = i;
        }

    return maxid;
}

int main(void)
{
    freopen("superbull.in", "r", stdin);
    freopen("superbull.out", "w", stdout);

    scanf("%d", &n);
    id.resize(n);
    mdist.assign(n, -1);
    used.assign(n, false);

    for (int i = 0; i < n; i++) {
        scanf("%d", &id[i]);
    }

    ll total_val = 0;
    mdist[0] = 0;
    for (int cnt = 0; cnt < n; cnt++) {
        int v = find_max();

        used[v] = true;
        total_val += mdist[v];

        for (int i = 0; i < n; i++) {
            if (used[i]) continue;

            mdist[i] = max(mdist[i], id[i] ^ id[v]);
        }
    }

    printf("%lld\n", total_val);

    return 0;
}