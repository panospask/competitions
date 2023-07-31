#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) ((val) & (1 << pos))

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAXN = 15;

struct Mouse {
    int s;
    pi loc;
};

const double INF = 10000 + 5;

int T, N;
double m;
pi start;
vector<Mouse> mice;
double speedmul[1 << MAXN];
double dp[1 << MAXN][MAXN];

double cover_distance(pi& a, pi& b, double speed)
{
    double dist = sqrt((ll)(a.first - b.first) * (a.first - b.first) + (ll)(a.second - b.second) * (a.second - b.second));

    return dist / speed;
}

bool reaches(double initial)
{
    for (int s = 0; s < 1 << N; s++)
        for (int i = 0; i < N; i++)
            dp[s][i] = INF;

    for (int i = 0; i < N; i++) {
        double t = cover_distance(start, mice[i].loc, initial);
        if (t <= mice[i].s)
            dp[1 << i][i] = t;
    }

    for (int s = 0; s < 1 << N; s++) {
        for (int i = 0; i < N; i++) {
            if (dp[s][i] == INF)
                continue;

            double speed = initial * speedmul[s];
            for (int j = 0; j < N; j++) {
                if (CHECK_BIT(s, j))
                    continue;

                double t = dp[s][i]  + cover_distance(mice[i].loc, mice[j].loc, speed);
                if (t <= mice[j].s)
                    dp[s + (1 << j)][j] = min(dp[s + (1 << j)][j], t);
            }
        }
    }

    for (int i = 0; i < N; i++)
        if (dp[(1 << N) - 1][i] != INF)
            return true;

    return false;
}

void calculate_speedmul(void)
{
    speedmul[0] = 1;
    for (int s = 0; s < 1 << N; s++) {
        for (int i = 0; i < N; i++)
            if (!CHECK_BIT(s, i))
                speedmul[s + (1 << i)] = speedmul[s] * m;
    }
}

int main(void)
{
    scanf("%d", &N);

    mice.resize(N);
    for (int i = 0; i < N; i++)
        scanf("%d %d %d", &mice[i].loc.first, &mice[i].loc.second, &mice[i].s);
    scanf("%lf", &m);

    calculate_speedmul();

    double l = 0;
    double r = 1;
    while (!reaches(r)) {
        l = r;
        r *= 2;
    }

    for (int i = 0; i < 80; i++) {
        double mid = (l + r) / 2;
        if (reaches(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%.10lf\n", r);

    return 0;
}