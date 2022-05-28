#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair

typedef pair<int,int> ii;

int n, m;
vector<vector<int>> grid;
ii what_swapped;

void swap_cols(ii cols)
{
    int i = cols.first;
    int j = cols.second;
    for (int x = 0; x < n; x++) {
        swap(grid[x][i], grid[x][j]);
    }
}

int find_spot(int* sorted, int val, int j)
{
    for (int i = 0; i < m; i++) {
        if (sorted[i] == val && grid[j][i] != val)
            return i;
    }

    return -1;
}

ii find_swap_cols(int i)
{
    int a[m];
    for (int j = 0; j < m; j++)
        a[j] = grid[i][j];

    sort (a, a + m);

    for (int j = 0; j < m; j++) {
        if (grid[i][j] != a[j]) {
            return mp(j, find_spot(a, grid[i][j], i));
        }
    }

    return mp(0, 0);
}

bool examine(bool have_swap)
{
    for (int i = 0; i < n; i++) 
        for (int j = 1; j < m; j++)
            if (grid[i][j - 1] > grid[i][j]) {
                if (have_swap) {
                    ii cols = find_swap_cols(i);
                    swap_cols(cols);
                    what_swapped = cols;
                    return examine(false);
                }
                else {
                    return false;
                }
            }

    return true;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    for (int x = 0; x < t; x++) {
        grid.clear();
        scanf("%d %d", &n, &m);
        grid.resize(n);
        for (int i = 0; i < n; i++)
            grid[i].resize(m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &grid[i][j]);

        what_swapped = mp(0, 0);
        bool correct = examine(true);

        if (correct)
            printf("%d %d\n", what_swapped.first + 1, what_swapped.second + 1);
        else
            printf("-1\n");
    }
}