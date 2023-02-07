#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (int)(10e5)

using namespace std;

vector<int> adj_list[MAXN];
bool visited[MAXN];
int level[MAXN];
int n;

int main(void)
{
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);

    scanf("%d", &n);
    int n1, n2;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &n1, &n2);
        adj_list[--n1].pb(--n2);
        adj_list[n2].pb(n1);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, (int)adj_list[i].size() + 1);
    }

    printf("%d\n", ans);
    return 0;
}