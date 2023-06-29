#include <bits/stdc++.h>

using namespace std;

int x_a, y_a, x_b, y_b, x_c, y_c;
void solve(void)
{
    scanf("%d %d %d %d %d %d", &x_a, &y_a, &x_b, &y_b, &x_c, &y_c);

    int dist_y1 = y_b - y_a;
    int dist_x1 = x_b - x_a;

    int dist_y2 = y_c - y_a;
    int dist_x2 = x_c - x_a;

    int ans = 0;
    if ((dist_x1 < 0 && dist_x2 < 0) || (dist_x1 > 0 && dist_x2 > 0))
        ans += min(abs(dist_x1), abs( dist_x2));
    if ((dist_y1 < 0 && dist_y2 < 0) || (dist_y1 > 0 && dist_y2 > 0))
        ans += min(abs(dist_y1), abs( dist_y2));

    printf("%d\n", ans + 1);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}