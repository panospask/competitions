#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int dest[MAXN + 2];
int n;
bool visited[MAXN + 2];
bool proc[MAXN + 2];
vector<int> curpath;

void dfs(int node)
{
    curpath.pb(node);
    if (proc[node] || visited[node])
        return;
    
    visited[node] = true;
    dfs(dest[node]);
}

int main(void)
{
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &dest[i]);
        dest[i]--;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            curpath.clear();
            dfs(i);

        
            if (!proc[curpath.back()]) {
                int termination_node = curpath.back(); curpath.pop_back();
                
                int cur = -1;
                while (cur != termination_node) {
                    cur = curpath.back(); curpath.pop_back();

                    proc[cur] = true;
                    ans++;
                }
            }
            while (!curpath.empty()) {
                proc[curpath.back()] = true;
                curpath.pop_back();
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}