#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int DIRS = 4;
int d_i[] = {1, 0, -1, 0};
int d_j[] = {0, 1, 0, -1};

int n, m;
int Q;

// Everything is 1-based to avoid errors
vector<vector<pi>> par;
vector<vector<int>> grid;
vector<vector<int>> val;
vector<vector<bool>> visited;
vector<vector<int>> pref;

vector<vector<int>> l_parents;
vector<vector<int>> r_parents;
vector<vector<int>> u_parents;
vector<vector<int>> d_parents;

bool inbound(int i, int j)
{
    return i > 0 && i <= n && j > 0 && j <= m;
}

void dfs(int i, int j, int i_p, int j_p)
{
    par[i][j] = mp(i_p, j_p);

    visited[i][j] = true;

    if (i_p != -1) {
        if (j_p != j) {
            if (j_p == j + 1)
                r_parents[j][i]++;
            else
                l_parents[j][i]++;
        }
        else {
            if (i_p == i + 1) {
                d_parents[i][j]++;
            }
            else {
                u_parents[i][j]++;
            }
        }
    }

    val[i][j] = 1;

    for (int x = 0; x < DIRS; x++) {
        int ni = i + d_i[x];
        int nj = j + d_j[x];

        if (inbound(ni, nj) && (ni != i_p || nj != j_p) && grid[ni][nj]) {
            dfs(ni, nj, i, j);
            val[i][j]--;
        }
    }
}

void calculate_prefix(void)
{
    pref.assign(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + val[i][j];

    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++) {
            l_parents[j][i] += l_parents[j][i - 1];
            r_parents[j][i] += r_parents[j][i - 1];
        }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            u_parents[i][j] += u_parents[i][j - 1];
            d_parents[i][j] += d_parents[i][j - 1];
        }
}

int in_square(pi p, int x1, int y1, int x2, int y2)
{
    int i, j;
    tie(i, j) = p;
    return x1 <= i && x2 >= i && y1 <= j && y2 >= j;
}

int main(void)
{
    scanf("%d %d %d", &n, &m, &Q);

    val.assign(n + 1, vector<int>(m + 1, 0));
    grid.resize(n + 1, vector<int>(m + 1));
    par.assign(n + 1, vector<pi>(m + 1, mp(-1 , -1)));
    visited.assign(n + 1, vector<bool>(m + 1, false));

    l_parents.assign(m + 1, vector<int>(n + 1, 0));
    r_parents.assign(m + 1, vector<int>(n + 1, 0));
    d_parents.assign(n + 1, vector<int>(m + 1, 0));
    u_parents.assign(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            scanf("%1d", &grid[i][j]);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!visited[i][j] && grid[i][j])
                dfs(i, j, -1, -1);

    calculate_prefix();

    while (Q--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int ans = pref[x2][y2] - pref[x1 - 1][y2] - pref[x2][y1 - 1] + pref[x1 - 1][y1 - 1];

        ans += d_parents[x1 - 1][y2] - d_parents[x1 - 1][y1 - 1];
        if (x2 != n)
            ans += u_parents[x2 + 1][y2] - u_parents[x2 + 1][y1 - 1];

        ans += r_parents[y1 - 1][x2] - r_parents[y1 - 1][x1 - 1];
        if (y2 != m)
            ans += l_parents[y2 + 1][x2] - l_parents[y2 + 1][x1 - 1];

        printf("%d\n", ans);
    }

    return 0;
}