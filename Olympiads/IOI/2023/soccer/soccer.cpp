#include "soccer.h"
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

struct SegTree {
    int size;
    vector<int> tree;
    const int DEFAULT = INF;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, DEFAULT);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            set(i, v, 2 * x + 1, lx, mid);
        }
        else {
            set(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx) {
            return DEFAULT;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        int g1 = get(l, r, 2 * x + 1, lx, mid);
        int g2 = get(l, r, 2 * x + 2, mid, rx);

        return min(g1, g2);
    }
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int N;
vector<vector<int>> grid;
vector<SegTree> above;
vector<SegTree> below;
vector<vector<pi>> segments;

/* dp[i][j][l][r]:
 * Maximum number of added cells if we have already processed rows [i+1, j-1] and now want to use segments fully contained within [l..r)
 */
map<tuple<int, int, int ,int>, int> dp;

void swap(SegTree& a, SegTree& b)
{
    swap(a.size, b.size);
    swap(a.tree, b.tree);
}

void calculate_trees_above(vector<SegTree>& cur)
{
    vector<vector<int>> prevtrees(N, vector<int>(N));

    cur.resize(N);
    for (int r = 0; r < N; r++) {
        cur[r].init(N);
        for (int c = 0; c < N; c++) {
            if (grid[r][c]) {
                prevtrees[r][c] = 0;
            }
            else if (!r) {
                prevtrees[r][c] = 1;
            }
            else {
                prevtrees[r][c] = prevtrees[r - 1][c] + 1;
            }

            cur[r].set(c, prevtrees[r][c]);
        }
    }
}

int calculate(int i, int j, int l, int r)
{
    // Bring the dp to the optimized version
    int up = above[i].get(l, r);
    int down = below[j].get(l, r);
    i = i - up + 1;
    j = j + down - 1;

    int res = (r - l) * (up + down - 1);

    if (dp.count(make_tuple(i, j, l, r))) {
        return dp[make_tuple(i, j, l, r)] + res;
    }

    int opt = 0;

    // Move to row i - 1
    if (i > 0) {
        int last = lower_bound(segments[i - 1].begin(), segments[i - 1].end(), mp(r, -1)) - segments[i - 1].begin() - 1;
        for (int p = last; p >= 0 && segments[i - 1][p].second > l; p--) {
            opt = max(opt, calculate(i - 1, j, max(segments[i - 1][p].first, l), min(segments[i - 1][p].second, r)));
        }
    }

    // Move to row j + 1
    if (j < N - 1) {
        int last = lower_bound(segments[j + 1].begin(), segments[j + 1].end(), mp(r, -1)) - segments[j + 1].begin() - 1;
        for (int p = last; p >= 0 && segments[j + 1][p].second > l; p--) {
            opt = max(opt, calculate(i, j + 1, max(segments[j + 1][p].first, l), min(segments[j + 1][p].second, r)));
        }
    }

    dp[make_tuple(i, j, l, r)] = opt;

    return opt + res;
}

void find_segments(void)
{
    segments.resize(N);

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (grid[r][c] == 0) {
                if (segments[r].size() == 0 || segments[r].back().second != -1) {
                    segments[r].pb(mp(c, -1));
                }
            }
            else {
                if (segments[r].size() && segments[r].back().second == -1) {
                    segments[r].back().second = c;
                }
            }
        }

        if (segments[r].size() && segments[r].back().second == -1) {
            segments[r].back().second = N;
        }
    }
}

int biggest_stadium(int n, std::vector<std::vector<int>> F)
{
    N = n;
    grid.resize(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = F[i][j];
        }
    }

    find_segments();
    calculate_trees_above(above);

    reverse(grid.begin(), grid.end());
    calculate_trees_above(below);
    reverse(grid.begin(), grid.end());
    reverse(below.begin(), below.end());

    int ans = 0;
    for (int r = 0; r < N; r++) {
        for (auto s : segments[r]) {
            ans = max(ans, calculate(r, r, s.first, s.second));
        }
    }

    return ans;
}