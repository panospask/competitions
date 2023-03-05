#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100
#define MAXK 100

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, ii> pp;

bool iscow[MAXN + 2][MAXN + 2];
bool visited[MAXN + 2][MAXN + 2];
bool block[MAXN + 2][MAXN + 2][4];
set<int> adj_list[MAXN + 5];
int n, k, road;
int u = 0, l = 1, d = 2, r = 3;
int dir_ver[4] = {-1, 0, 1, 0};
int dir_hor[4] = {0, -1, 0, 1};

int dfs(int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= n)
        return 0;

    if (visited[i][j])
        return 0;

    visited[i][j] = true;
    int cur_cows = 0;
    if (iscow[i][j])
        cur_cows++;
    for (int x = 0; x < 4; x++)
        if (!block[i][j][x])
            cur_cows += dfs(i + dir_ver[x], j + dir_hor[x]);

    return cur_cows;
}

int main(void)
{
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    scanf("%d %d %d", &n, &k, &road);

    int i1, j1, i2, j2;
    int n1, n2;
    for (int i = 0; i < road; i++) {
        scanf("%d %d %d %d", &i1, &j1, &i2, &j2);
        i1--; j1--; i2--; j2--;

        if(i1 == i2) {
            if (j1 > j2)
                swap(j1, j2);
            block[i2][j2][l] = true;
            block[i1][j1][r] = true;
        }
        else {
            if (i1 > i2)
                swap(i1, i2);
            block[i2][j2][u] = true;
            block[i1][j1][d] = true;
        }
    }


    for (int i = 0; i < k; i++) {
        scanf("%d %d", &i1, &j1);
        i1--; j1--;
        iscow[i1][j1] = true;
    }

    vector<int> con_comp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (iscow[i][j] && !visited[i][j])
                con_comp.pb(dfs(i, j));

    long long int ans = 0;
    for (int i = 0; i < con_comp.size(); i++)
        for (int j = i + 1; j < con_comp.size(); j++)
            ans += con_comp[i] * con_comp[j];

    printf("%lld\n", ans);
    return 0;
}