#include <bits/stdc++.h>
#define MAXN 5000

using namespace std;

int dist_pref_sum[MAXN + 2][MAXN + 2];
string a;
string b;
int n, m;

bool match(int x, int y)
{
    return a[x] == b[y];
}

int prefix_edit_distance(int x, int y)
{
    if (x == -1)
        return y + 1;
    if (y == -1)
        return x + 1;

    if (dist_pref_sum[x][y] != -1)
        return dist_pref_sum[x][y];

    dist_pref_sum[x][y] = 1e9;

    // Remove a character from x
    dist_pref_sum[x][y] = min(prefix_edit_distance(x-1,y) + 1, dist_pref_sum[x][y]);

    // Add a character to x <-- Test the (x,y-1) dist and then add the last character of b to a
    dist_pref_sum[x][y] = min(prefix_edit_distance(x,y-1) + 1, dist_pref_sum[x][y]);

    // Replace the character in x <-- Test the (x-1, y-1) dist and then make sure the last characters match
    dist_pref_sum[x][y] = min(prefix_edit_distance(x-1,y-1) + !match(x,y), dist_pref_sum[x][y]);

    return dist_pref_sum[x][y];
}

int main(void)
{
    cin >> a >> b;

    n = a.size();
    m = b.size();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist_pref_sum[i][j] = -1;

    int ans = prefix_edit_distance(n-1,m-1);
    printf("%d\n", ans);
    return 0;
}
