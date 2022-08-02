/*
ID: panos.p1
LANG: C++11
TASK: rockers
*/

#include <bits/stdc++.h>
#define MAXN 20

using namespace std;
int t, n, m;
int discs[MAXN];
int ans = 0;

void dfs(int discs_remaining, int cur_songs, int cur_space, int last_entry)
{
    ans = max(ans, cur_songs);

    if (discs_remaining != 0 ) {
        for (int i = last_entry + 1; i < n; i++) {
            if (discs[i] <= cur_space) {
                dfs(discs_remaining, cur_songs + 1, cur_space - discs[i], i);
            }
        }

        if (discs_remaining != 0 && cur_space != t)
            dfs(discs_remaining - 1, cur_songs, t, last_entry);
    }
}

int main(void)
{
    freopen("rockers.in", "r", stdin);
    freopen("rockers.out", "w", stdout);

    scanf("%d %d %d", &n, &t, &m);
    for (int i = 0; i < n; i++)
        scanf("%d", &discs[i]);

    dfs(m, 0, t, -1);
    printf("%d\n", ans);
    return 0;
}