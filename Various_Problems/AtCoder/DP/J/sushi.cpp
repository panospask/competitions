#include <bits/stdc++.h>

using namespace std;

const int MAXN = 300;

int N;
vector<int> a;
int v[3];
double dp[MAXN + 1][MAXN + 1][MAXN + 1];

double calculate_dp(int a, int b, int c)
{
    if (a < 0 || b < 0 || c < 0)
        return -1;
    else if (a + b + c == 0)
        return 0;
    else if (dp[a][b][c] != 0)
        return dp[a][b][c];

    dp[a][b][c] = 0;
    dp[a][b][c] = N + a * calculate_dp(a - 1, b, c) + b * calculate_dp(a + 1, b - 1, c) + c * calculate_dp(a, b + 1, c - 1);
    dp[a][b][c] /= (a + b + c);

    return dp[a][b][c];
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        v[a[i] - 1]++;
    }

    double ans = calculate_dp(v[0], v[1], v[2]);
    printf("%.10lf\n", ans);

    return 0;
}