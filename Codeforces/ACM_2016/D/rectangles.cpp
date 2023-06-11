#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int R, C;
vector<vector<int>> cons_up;
vector<vector<int>> grid;
stack<int> s;
vector<int> h;
vector<int> w;
ll ans = 0;

ll squarecount(int width, int height)
{
    return (ll)height * (width * (width + 1) / 2);
}

void initialize_cons_up(void)
{
    for (int c = 0; c < C; c++) {
        cons_up[0][c] = 1;

        for (int i = 1; i < R; i++) {
            if (grid[i][c] == grid[i - 1][c])
                cons_up[i][c] = cons_up[i - 1][c] + 1;
            else
                cons_up[i][c] = 1;
        }
    }

    return;
}

void clear_stack(void)
{
    int prv_add = 0;

    while (!s.empty()) {
        w[s.top()] += prv_add;

        int width = w[s.top()];
        prv_add = w[s.top()];
        ans += squarecount(width, h[s.top()]);
        s.pop();

        if (!s.empty()) {
            ans -= squarecount(width, h[s.top()]);
        }
    }

    return;
}

void process_row(int row)
{
    h.clear();
    w.clear();
    h = cons_up[row];
    w.assign(C, 1);

    int curcol = -1;
    for (int column = 0; column < C; column++) {
        if (grid[row][column] != curcol) {
            clear_stack();
            curcol = grid[row][column];
            s.push(column);
        }
        else {
            int prv_add = 0;
            while (!s.empty() && h[s.top()] >= h[column]) {
                w[s.top()] += prv_add;

                int width = w[s.top()];
                prv_add = w[s.top()];
                ans += squarecount(width, h[s.top()]);
                s.pop();

                int hrm = h[column];
                if (!s.empty())
                    hrm = max(hrm, h[s.top()]);
                ans -= squarecount(width, hrm);
            }

            w[column] += prv_add;
            s.push(column);
        }
    }

    clear_stack();

    return;
}

void solve(void)
{
    scanf("%d %d", &R, &C);

    ans = 0;
    grid.assign(R, vector<int>(C));
    cons_up.assign(R, vector<int>(C));

    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &grid[i][j]);

    initialize_cons_up();
    for (int i = 0; i < R; i++)
        process_row(i);

    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}