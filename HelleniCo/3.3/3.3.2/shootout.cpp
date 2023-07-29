#include <bits/stdc++.h>
#define CHECK_BIT(val, pos) (val & (1 << pos))
#define DOUBLE

#ifdef LONG
    #define double long double
    #define EPSILON LDBL_EPSILON
#endif
#ifdef FLOAT
    #define double float
    #define EPSILON FLT_EPSILON
#endif
#ifdef DOUBLE
    #define double double
    #define EPSILON DBL_EPSILON
#endif

using namespace std;

const int MAXPLAYERS = 13;

bool almost_equal(const double& a, const double& b)
{
    return abs(a - b) <= EPSILON;
}

int N;
double accuracy[MAXPLAYERS];

//dp[s][i][j]: Including only the players in s, player i plays first, what is the probability
// that player j wins
double dp[1 << MAXPLAYERS][MAXPLAYERS][MAXPLAYERS];

double calculate_dp(int s, int first, int pos)
{
    if (first >= N)
        first -= N;

    if (dp[s][first][pos] != -1)
        return dp[s][first][pos];
    else if (__builtin_popcount(s) == 1)
        return CHECK_BIT(s, pos) != 0;

    // Calculate the full dp[s][first]
    for (int i = 0; i < N; i++)
        dp[s][first][i] = 0;

    double p = 1;
    for (int i = first; i != N + first; i++) {
        int shoots = i;
        if (shoots >= N)
            shoots -= N;
        if (!CHECK_BIT(s, shoots))
            continue;

        // Find the optimaly play for this person
        double maxchance = 0;
        vector<int> maxshoot;
        for (int j = 0; j < N; j++) {
            if (!CHECK_BIT(s, j))
                continue;

            // Prevent suicides maybe??
            if (j == shoots)
                continue;

            double winchance = calculate_dp(s - (1 << j), shoots + 1, shoots);

            if (almost_equal(winchance, maxchance)) {
                // If many options are similar, choose randomly
                maxshoot.push_back(j);
            }
            else if (winchance > maxchance) {
                maxchance = winchance;
                maxshoot.clear();
                maxshoot.push_back(j);
            }
        }

        // Shoot
        double hit_probability = p * accuracy[shoots];
        int possible = maxshoot.size();
        double prob = (double)1 / possible;
        for (auto m : maxshoot) {
            for (int j = 0; j < N; j++) {
                dp[s][first][j] += prob * hit_probability * calculate_dp(s - (1 << m), shoots + 1, j);
            }
        }

        // Update remaining probability
        p = p * (1 - accuracy[shoots]);
    }

    // Distribute the remaining probability equally
    double psum = 0;
    for (int i = 0; i < N; i++) {
        psum += dp[s][first][i];
    }

    double a = 1 / psum;
    for (int i = 0; i < N; i++) {
        dp[s][first][i] *= a;
    }

    return dp[s][first][pos];
}

int main(void)
{
    freopen("shootout.in", "r", stdin);
    freopen("shootout.out", "w", stdout);

    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int ac;
        scanf("%d", &ac);

        accuracy[i] = (double)ac / 100;
    }
    for (int i = 0; i < 1 << N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                dp[i][j][k] = -1;

    calculate_dp((1 << N) - 1, 0, 0);

    for (int i = 0; i < N; i++) {
        printf("%.2f\n", (float)(100 * dp[(1 << N) - 1][0][i]));
    }

    return 0;
}