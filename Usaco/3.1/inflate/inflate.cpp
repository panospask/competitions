/*
ID: panos.p1
LANG: C++11
TASK: inflate
*/

#include <bits/stdc++.h>
#define MAXN 10000

using namespace std;

typedef pair<int, int> ii;

int ans = 0;

ii categories[MAXN];
int ttl_time;
int n;

void dfs(int time_left, int latest_cat, int cur_points)
{
    ans = max(ans, cur_points);
    
    int curmon;
    for (int i = latest_cat + 1; i < n && categories[i].first <= time_left; i++) {
            curmon = categories[i].second;
            for (int j = 1; categories[i].first * j <= time_left; j++)
                dfs(time_left - j * categories[i].first, i, cur_points + curmon * j); 
    }

}

int main(void)
{
    freopen("inflate.in", "r", stdin);
    freopen("inflate.out", "w", stdout);

    scanf("%d %d", &ttl_time, &n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &categories[i].second, &categories[i].first);

    sort(categories, categories + n);
    dfs(ttl_time, -1, 0);

    printf("%d\n", ans);
    return 0;
}