#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 2500

using namespace std;

pair<int, int> cows[MAXN + 5];
int n;
map<int, int> reduce_x, reduce_y;

int above_y_line[MAXN + 5][MAXN + 5];
int below_y_line[MAXN + 5][MAXN + 5];

int main(void)
{
    // freopen("rectbarn.in", "r", stdin);
    // freopen("rectbarn.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cows[i].first, &cows[i].second);
    }

    sort(cows, cows + n);
    for (int c = 0; c < n; c++)
        reduce_x[cows[c].first] = c;

    auto cmp = [&] (const pair<int, int>& c1, const pair<int, int>& c2) {
        return c1.second < c2.second;
    };
    sort(cows, cows + n, cmp);
    for (int c = 0; c < n; c++)
        reduce_y[cows[c].second] = c;

    for (int c = 0; c < n; c++) {
        cows[c].first = reduce_x[cows[c].first];
        cows[c].second = reduce_y[cows[c].second];
    }

    sort(cows, cows + n);
    int cur_y;
    // Create two prefix sum arrays for every y-value
    for (int c = 0; c < n; c++) {
        cur_y = cows[c].second;
        for (int x = 1; x <= n; x++) {
            above_y_line[cur_y][x] = above_y_line[cur_y][x - 1];
            below_y_line[cur_y][x] = below_y_line[cur_y][x - 1];

            above_y_line[cur_y][x] += cows[x - 1].second > cur_y;
            below_y_line[cur_y][x] += cows[x - 1].second < cur_y;
        }
    }

    // Check for the number of possible rectangles with a, b at the top and bottom
    long long int ans = 0;
    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            int bottom = min(cows[a].second, cows[b].second);
            int top = max(cows[a].second, cows[b].second);

            int bottom_total = 1 + below_y_line[bottom][cows[b].first + 1] - below_y_line[bottom][cows[a].first];
            int top_total = 1 + above_y_line[top][cows[b].first + 1] - above_y_line[top][cows[a].first];

            ans += (long long int)bottom_total * top_total;
        }
    }

    ans += n + 1;
    printf("%lld\n", ans);
    return 0;
}