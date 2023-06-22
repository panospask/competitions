#include <bits/stdc++.h>

using namespace std;

// typedef __int128_t lll;
// typedef long long ll;
typedef int ll;
typedef long long lll;

const ll MOD = (int)1e9 + 7;

const int P = 2;
const int Q = 3;

int n, m;
vector<vector<int>> grid;
vector<vector<ll>> hashed;

vector<ll> pow_q;
vector<ll> pow_p_inv;
vector<ll> pow_q_inv;
vector<ll> pow_p;

pair<int, int> ans = make_pair(0, 0);

ll submatrix(int i1, int j1, int rownum, int colnum)
{
    // The hashing is 1-based
    i1++;
    j1++;

    int i2 = i1 + rownum - 1;
    int j2 = j1 + colnum - 1;
    ll val = hashed[i2][j2] - hashed[i2][j1 - 1] - hashed[i1 - 1][j2] + hashed[i1 - 1][j1 - 1];

    val = ((val % MOD) + MOD) % MOD;

    val = ((lll)val * pow_p[n - i1] % MOD);
    val = ((lll)val * pow_q[m - j1] % MOD);

    return val;
}

// Returns true if the n x m submatrix starting at i1, j1 is smaller than the one starting at i2, j2
bool is_smaller(int i1, int j1, int i2, int j2)
{
    // ll a = submatrix(i1, j1, n, m);
    // ll b = submatrix(i2, j2, n, m);
    // if (a == b) {
    //     return false;
    // }

    int l_row = 0;
    int r_row = n;
    while (r_row > l_row + 1) {
        int mid = (l_row + r_row) / 2;
        if (submatrix(i1, j1, mid, m) == submatrix(i2, j2, mid, m))
            l_row = mid;
        else
            r_row = mid;
    }

    int l_col = 0;
    int r_col = m;
    while (r_col > l_col + 1) {
        int mid = (l_col + r_col) / 2;
        if (submatrix(i1, j1, r_row, mid) == submatrix(i2, j2, r_row, mid))
            l_col = mid;
        else
            r_col = mid;
    }

    return grid[i1 + r_row - 1][j1 + r_col - 1] < grid[i2 + r_row - 1][j2 + r_col - 1];
}

void initialize_hashing(void)
{
    hashed.assign(2 * n + 1, vector<ll>(2 * m + 1, 0));

    for (int i = 0; i < 2 * n; i++)
        for (int j = 0; j < 2 * m; j++) {
            lll h =  hashed[i][j + 1] + hashed[i + 1][j] - hashed[i][j];
            h = ((h % MOD) + MOD) % MOD;

            h += ((lll)grid[i][j] * pow_p[i] % MOD) * (lll)pow_q[j] % MOD;
            h %= MOD;

            hashed[i + 1][j + 1] = h;
        }
}

int main(void)
{
    scanf("%d %d", &n, &m);

    pow_q.resize(2 * m + 1);
    pow_p.resize(2 * n + 1);

    pow_p[0] = pow_q[0] = 1;
    for (int i = 0; i < 2 * n; i++)
        pow_p[i + 1] = (lll)pow_p[i] * P % MOD;
    for (int i = 0; i < 2 * m; i++)
        pow_q[i + 1] = (lll)pow_q[i] * Q % MOD;

    grid.resize(2 * n, vector<int>(2 * m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);

            grid[i][j] = grid[i + n][j] = grid[i][j + m] = grid[i + n][j + m] = (c == '.');
        }

    initialize_hashing();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (is_smaller(i, j, ans.first, ans.second))
                ans = make_pair(i, j);
        }

    for (int i = ans.first; i < ans.first + n; i++) {
        for (int j = ans.second; j < ans.second + m; j++) {
            if (grid[i][j])
                putchar('.');
            else
                putchar('*');
        }
        putchar('\n');
    }

    return 0;
}