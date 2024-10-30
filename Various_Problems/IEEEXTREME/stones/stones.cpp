#include <bits/stdc++.h>

using namespace std;

const int MAXV = 45;

// dp[i][j][k][l]: Chance of player A winning if he has (i,j), and B has (k, l)
double dp[MAXV][MAXV][MAXV][MAXV];

double lmd(double a, double p[4])
{
    return (p[0] - p[1] - p[2] + p[3]) * a - p[0] + p[1];
}
double c (double a, double p[4])
{
    return (p[2] - p[0]) * a + p[0];
}

double probable(double a, double p[4])
{
    double l = lmd(a, p);

    if (l >= 0) {
        return c(a, p);
    }
    else {
        return c(a, p) + l;
    }
}

double calculate(int i, int j, int k, int l)
{
    if (i == 0 || j == 0) {
        return 0;
    }
    if (k == 0 || l == 0) {
        return 1;
    }
    if (dp[i][j][k][l] >= 0) {
        return dp[i][j][k][l];
    }

    double p[4];
    p[0] = 1 - calculate(k, l, i - 1, j);
    p[1] = 1 - calculate(k, l - 1, i, j);
    p[2] = 1 - calculate(k - 1, l, i, j);
    p[3] = 1 - calculate(k, l, i, j - 1);

    double m = p[0] - p[1] - p[2] + p[3];
    double n = -p[0] + p[1];

    double x = -1;
    if (m != 0) {
        x = -n / m;
    }

    double ans = max(probable(0, p), probable(1, p));
    if (0 <= x && x <= 1) {
        ans = max(ans, probable(x, p));
    }

    return dp[i][j][k][l] = ans;
}

void init(void)
{
    for (int i = 0; i < MAXV; i++) {
        for (int j = 0; j < MAXV; j++) {
            for (int k = 0; k < MAXV; k++) {
                for (int l = 0; l < MAXV; l++) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }
}

int main(void)
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    init();

    printf("%lf\n", calculate(a, b, c, d));

    return 0;
}