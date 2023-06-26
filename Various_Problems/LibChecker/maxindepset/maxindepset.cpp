#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) (val & (1<<pos))

using namespace std;

int n, m;
int n1, n2;

vector<vector<bool>> adj1;
vector<vector<bool>> adj2;
vector<int> dp1, dp2;
vector<int> p1, p2;
vector<vector<int>> inter_edges;

int ans_v = 0;
int ans1 = 0, ans2 = 0;

bool adjacent(int i, int s, vector<vector<bool>>& adj_matrix)
{
    for (int j = 0; j < adj_matrix[i].size(); j++)
        if (CHECK_BIT(s, j) && adj_matrix[i][j])
            return true;

    return false;
}

void generate_subsets(int n, vector<int>& dp, vector<int>&p, vector<vector<bool>>& adj_matrix)
{
    dp.resize(1 << n);
    p.assign(1 << n, -1);

    dp[0] = 0;
    vector<bool> isgood;
    isgood.assign(1 << n, true);

    for (int s = 0; s < 1 << n; s++) {
        if (isgood[s]) {
            dp[s] = __builtin_popcount(s);
            p[s] = -1;
        }

        for (int i = 0; i < n; i++) {
            if (!CHECK_BIT(s, i)) {
                if (!isgood[s] || adjacent(i, s, adj_matrix))
                    isgood[s + (1 << i)] = false;
                else
                    isgood[s + (1 << i)] = true;

                if (dp[s + (1 << i)] < dp[s]) {
                    dp[s + (1 << i)] = dp[s];
                    p[s + (1 << i)] = s;
                }
            }
        }
    }
}

void generate_vertices(int s, vector<int>& p, int n, int add = 0)
{
    while (p[s] != -1)
        s = p[s];

    for (int i = 0; i < n; i++)
        if (CHECK_BIT(s, i))
            printf("%d ", i + add);

    return;
}

int main(void)
{
    scanf("%d %d", &n, &m);

    n1 = n / 2;
    n2 = n - n1;

    inter_edges.resize(n2);
    adj1.resize(n1, vector<bool>(n1, false));
    adj2.resize(n2, vector<bool>(n2, false));

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a > b)
            swap(a, b);

        if (b < n1)
            adj1[a][b] = adj1[b][a] = true;
        else if (a >= n1) {
            adj2[a - n1][b - n1] = adj2[b - n1][a - n1] = true;
        }
        else {
            inter_edges[b - n1].push_back(a);
        }
    }

    generate_subsets(n1, dp1, p1, adj1);
    generate_subsets(n2, dp2, p2, adj2);

    for (int s2 = 0; s2 < (1 << n2); s2++) {
        int s1 = (1 << n1) - 1;
        for (int i = 0; i < n2; i++) {
            if (CHECK_BIT(s2, i)) {
                for (auto e : inter_edges[i])
                    s1 = s1 & ((1 << n1) - 1 - (1 << e));
            }
        }

        if (dp1[s1] + dp2[s2] > ans_v) {
            ans_v = dp1[s1] + dp2[s2];
            ans1 = s1;
            ans2 = s2;
        }
    }

    printf("%d\n", ans_v);
    generate_vertices(ans1, p1, n1);
    generate_vertices(ans2, p2, n2, n1);
    printf("\n");

    return 0;
}