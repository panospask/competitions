#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 200000

using namespace std;

vector<int> curpath;
bool visited[MAXN + 2];
int dest[MAXN + 2];
bool proc[MAXN + 2];
int n;
int v[MAXN + 2];

void dfs(int node)
{
    curpath.pb(node);
    if (visited[node])
        return;
    visited[node] = true;
    dfs(dest[node]);
}

int main(void)
{
    // freopen("visits.in", "r", stdin);
    // freopen("visits.out", "w", stdout);

    scanf("%d", &n);

    long long int total_moo_sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &dest[i], &v[i]);
        dest[i]--;

        visited[i] = false;

        total_moo_sum += v[i];
    }

    long long int ttl_elim = 0;
    for (int i = 0; i < n; i++) 
        if (!visited[i]) {
            curpath.clear();
            dfs(i);

            if (proc[curpath.back()]) {
                while (!curpath.empty()) {
                    proc[curpath.back()] = true;
                    curpath.pop_back();
                }
            }
            else {
                // We must choose one element of the cycle to eliminate
                int elim = INT_MAX;
                int breakpoint = curpath.back(); curpath.pop_back();
                int cur = -1;

                while (cur != breakpoint) {
                    cur = curpath.back(); curpath.pop_back();
                    proc[cur] = true;
                    elim = min(elim, v[cur]);
                }
                while (!curpath.empty()) {
                    proc[curpath.back()] = true;
                    curpath.pop_back();
                }

                ttl_elim += elim;
            }
        }

    total_moo_sum -= ttl_elim;
    printf("%lld\n", total_moo_sum);

    return 0;
}