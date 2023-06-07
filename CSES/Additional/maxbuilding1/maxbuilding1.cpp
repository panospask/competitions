#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> grid;
vector<int> furthest_back;
vector<int> height;

void count_from(int row)
{
    for (int col = 0; col < m; col++) {
        int j = row;
        while (j >= 0 && grid[j][col])
            j--;

        height[col] = row - j;
    }
}

int process_row(int row)
{
    count_from(row);

    int ans = 0;
    stack<int> active_left_columns;

    for (int col = 0; col < m; col++) {

        while (!active_left_columns.empty()) {
            if (height[active_left_columns.top()] > height[col]) {
                int h = height[active_left_columns.top()];
                int w = col - furthest_back[active_left_columns.top()];

                ans = max(ans, w * h);

                active_left_columns.pop();
            }
            else {
                break;
            }
        }

        if (active_left_columns.empty()) {
            furthest_back[col] = 0;
            active_left_columns.push(col);
        }
        else {
            furthest_back[col] = active_left_columns.top() + 1;
            active_left_columns.push(col);
        }
    }

    while (!active_left_columns.empty()) {
        int h = height[active_left_columns.top()];
        int w = m - furthest_back[active_left_columns.top()];

        ans = max(ans, w * h);

        active_left_columns.pop();
    }

    return ans;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    grid.resize(n, vector<int>(m));
    height.resize(m);
    furthest_back.resize(m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            char c;
            scanf(" %c", &c);
            grid[i][j] = c == '.';
        }

    int ans = 0;
    for (int r = 0; r < n; r++)
        ans = max(ans, process_row(r));

    printf("%d\n", ans);
    return 0;
}