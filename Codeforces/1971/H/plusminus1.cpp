#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N;
vector<vector<bool>> possible;
vector<vector<vector<pi>>> adj_list;
vector<vector<unordered_map<int, int>>> joined;

vector<vector<pi>> grid;

// Merge i into j :)
bool merge(int i, int s_i, int j, int s_j)
{
    if (possible[i][s_i] == false) {
        possible[j][s_i] == false;
        return false;
    }

    if (joined[i][s_i].size() > joined[j][s_j].size()) {
        swap(joined[i][s_i], joined[j][s_j]);
    }

    for (auto& [v, s] : joined[i][s_i]) {
        if (joined[s][s_j].count(v) == 0) {
            joined[j][s_j][v] = s;
        }
        else if (joined[s][s_j][v] != s) {
            possible[j][s_j] = false;
            return false;
        }
    }

    return true;
}

void clear(void)
{
    adj_list.clear();
    possible.clear();
    joined.clear();
    grid.clear();
}

void solve(void)
{
    scanf("%d", &N);

    joined.resize(N, vector<unordered_map<int, int>>(2));
    adj_list.resize(N, vector<vector<pi>>(2));
    possible.assign(N, vector<bool>(2, true));
    grid.resize(N, vector<pi>(3));

    for (int c = 0; c < 3; c++) {
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &grid[i][c].first);
            grid[i][c].second = grid[i][c].first < 0 ? 0 : 1;
            grid[i][c].first = abs(grid[i][c].first);
            grid[i][c].first--;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int c = 0; c < 3; c++) {
            // Make current value neg to force other 2 to become positive
            int v = grid[i][c].first;
            int s = !grid[i][c].second;
            for (int d = 0; d < 3; d++) {
                if (d == c) {
                    continue;
                }
                adj_list[v][s].push_back(grid[i][d]);
            }
        }
    }

    for (int i = 0; i < N; i++) {

    }
}

int main(void)
{
    ;
}