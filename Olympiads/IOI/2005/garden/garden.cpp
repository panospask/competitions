#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6;

int N, K, L, W;

vector<int> opt_up;
vector<int> opt_down;
vector<vector<int>> sums;
vector<vector<int>> a;
vector<pi> trees;

void make_sums(void)
{
    sums.assign(L + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= L; i++) {
        for (int j = 1; j <= W; j++) {
            sums[i][j] = a[i - 1][j - 1] + sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1];
        }
    }
}

void assign_trees(void)
{
    a.assign(L, vector<int>(W, 0));
    for (int i = 0; i < N; i++) {
        a[trees[i].first][trees[i].second]++;
    }
}

// Number of trees in the square with top left corner at (i1, j1) and
// bottom right corner at (i2, j2)
int tot(int i1, int j1, int i2, int j2)
{
    return sums[i2 + 1][j2 + 1] - sums[i1][j2 + 1] - sums[i2 + 1][j1] + sums[i1][j1];
}

int per(int i1, int j1, int i2, int j2)
{
    return 2 * (i2 - i1 + 1 + j2 - j1 + 1);
}

int calculate(void)
{
    assign_trees();
    make_sums();
    opt_down.assign(L, INF);
    opt_up.assign(L, INF);


    for (int i1 = 0; i1 < L; i1++) {
        for (int i2 = i1; i2 < L; i2++) {
            int j2 = 0;
            for (int j1 = 0; j1 < W; j1++) {
                while (j2 < W && tot(i1, j1, i2, j2) < K) {
                    j2++;
                }

                if (j2 != W && tot(i1, j1, i2, j2) == K) {
                    opt_down[i1] = min(opt_down[i1], per(i1, j1, i2, j2));
                    opt_up[i2] = min(opt_up[i2], per(i1, j1, i2, j2));
                }
            }
        }
    }

    // Propagate optimal
    for (int i = 1; i < L; i++) {
        opt_up[i] = min(opt_up[i], opt_up[i - 1]);
    }
    for (int i = L - 2; i >= 0; i--) {
        opt_down[i] = min(opt_down[i], opt_down[i + 1]);
    }

    int res = INF;
    for (int i = 1; i < L; i++) {
        res = min(res, opt_down[i] + opt_up[i - 1]);
    }

    return res;
}

int main(void)
{
    scanf("%d %d %d %d", &L, &W, &N, &K);
    
    trees.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &trees[i].first, &trees[i].second);
        trees[i].first--;
        trees[i].second--;
    }

    int ans = calculate();

    swap(L, W);
    for (int i = 0; i < N; i++) {
        swap(trees[i].first, trees[i].second);
    }
    ans = min(ans, calculate());

    if (ans != INF) {
        printf("%d\n", ans);
    }
    else {
        printf("NO\n");
    }

    return 0;
}