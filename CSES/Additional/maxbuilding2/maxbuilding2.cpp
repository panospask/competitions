#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, m;
vector<vector<bool>> grid;
vector<vector<int>> cnt_up;

// h x w
vector<vector<ll>> area;
vector<vector<ll>> area2;

// Create width prefix sum of a to b
void prop_width(vector<vector<ll>>& a, vector<vector<ll>>& b)
{
    for (int h = 1; h <= n; h++) {
        b[h][m] = a[h][m];
        for (int w = m - 1; w > 0; w--) {
            b[h][w] = a[h][w] + b[h][w + 1];
        }
    }
}
void prop_height(vector<vector<ll>>& a, vector<vector<ll>>& b)
{
    for (int w = 1; w <= m; w++) {
        b[n][w] = a[n][w];
        for (int h = n - 1; h > 0; h--) {
            b[h][w] = a[h][w] + b[h + 1][w];
        }
    }
}

void init_count(void)
{
    cnt_up.assign(n, vector<int>(m));

    for (int col = 0; col < m; col++) {
        cnt_up[0][col] = grid[0][col];
        for (int row = 1; row < n; row++) {
            if (grid[row][col])
                cnt_up[row][col] = cnt_up[row - 1][col] + 1;
            else
                cnt_up[row][col] = 0;
        }
    }
}

void process_row(int r)
{
    vector<int> h = cnt_up[r];
    vector<int> w;
    w.assign(m, 1);

    stack<int> s;
    int prvadd = 0;
    for (int i = 0; i < m; i++) {
        prvadd = 0;
        while (!s.empty() && h[s.top()] >= h[i]) {
            w[s.top()] += prvadd;
            prvadd = w[s.top()];
            int width = w[s.top()];

            // Add its area
            area[h[s.top()]][width]++;
            s.pop();

            // Remove intersection
            int hrm = h[i];
            if (!s.empty())
                hrm = max(h[i], h[s.top()]);

            area[hrm][width]--;

        }

        w[i] += prvadd;
        s.push(i);
    }

    // Clear the stack

    prvadd = 0;
    while (!s.empty()) {
        w[s.top()] += prvadd;
        prvadd = w[s.top()];
        int width = w[s.top()];

        area[h[s.top()]][width]++;

        s.pop();
        if (!s.empty())
            area[h[s.top()]][width]--;
    }
}

int main(void)
{
    scanf("%d %d", &n, &m);

    grid.assign(n, vector<bool>(m));
    area.assign(n + 1, vector<ll>(m + 1, 0));
    area2.assign(n + 1, vector<ll>(m + 1, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);

            grid[i][j] = c == '.';
        }

    init_count();
    for (int r = 0; r < n; r++)
        process_row(r);

    // Propagate the results in width - height - width order
    prop_width(area, area2);
    prop_height(area2, area);
    prop_width(area, area2);

    for (int h = 1; h <= n; h++) {
        for (int w = 1; w <= m; w++)
            printf("%lld ", area2[h][w]);
        printf("\n");
    }

    return 0;
}