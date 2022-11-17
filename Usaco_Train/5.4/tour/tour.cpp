/*
ID: panos.p1
LANG: C++11
TASK: tour
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;


map<string, int> nodeconvert;
int curvisit;
int ans;
int n, m;
int dp[MAXN][MAXN];
bool edge[MAXN][MAXN];

int main(void)
{
    freopen("tour.in", "r", stdin);
    freopen("tour.out", "w", stdout);

    scanf("%d %d", &n, &m);
    getchar();
    string cur;
    for (int i = 0; i < n; i++) {
        cin >> cur;
        nodeconvert[cur] = i;
    }

    string s1, s2;
    int n1, n2;
    for (int j = 0; j < m; j++) {
        cin >> s1 >> s2;
        n1 = nodeconvert[s1];
        n2 = nodeconvert[s2];

        edge[min(n1, n2)][max(n1, n2)] = true;
    }

    ans = 1;
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = 0; k < j; k++) {
                if (k == i && k != 0) continue;
                if (!edge[k][j]) continue;

                if (dp[i][k] != 0 && dp[i][k] + 1 > dp[i][j])
                    dp[i][j] = dp[i][k] + 1;
            }
            dp[j][i] = dp[i][j];
        }

        if (i == n - 1)
            ans = max(ans, dp[n - 1][n - 1] - 1);
        else if (edge[i][n - 1])
            ans = max(ans, dp[i][n - 1]);
    }

    printf("%d\n", ans);
    return 0;
}