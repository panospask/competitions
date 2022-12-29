#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

int cowplace[MAXN];
int n;

int simulate_explode(int dir, int radius, int spotnum)
{
    int newspot = spotnum;
    int num_explode = 0;

    while (newspot > 0 && newspot < n - 1 && abs(cowplace[spotnum] - cowplace[newspot + dir]) <= radius){
        newspot += dir;
        num_explode++;
    }
    int to_add = 0;
    if (newspot != spotnum)
        to_add = simulate_explode(dir, radius + 1, newspot);

    return num_explode + to_add;
}

int main(void)
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &cowplace[i]);

    sort(cowplace, cowplace + n);

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans = max(ans, 1 + simulate_explode(1, 1, i) + simulate_explode(-1, 1, i));

    printf("%d\n", ans);
    return 0;
}