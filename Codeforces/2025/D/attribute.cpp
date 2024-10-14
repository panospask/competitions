#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;

const int INF = 1e7;

int N, M;

vector<int> r;
vector<ll> pref;
vector<vector<int>> dp;

// Positions of the point gatherings
vector<int> points;

// points[i][j]: Number of records that require <= j intelligence in between point i-1 and point i
vector<vector<int>> intelligence;
vector<vector<int>> strength;

void makemax(int& a, int b)
{
    if (a < b) {
        a = b;
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    r.resize(N);
    dp.assign(M + 1, vector<int>(M + 1, -INF));
    pref.resize(N + 1);
    intelligence.resize(M + 1, vector<int>(M + 1));
    strength.resize(M + 1, vector<int>(M + 1));

    for (int i = 0; i < N; i++) {
        scanf("%d", &r[i]);

        if (r[i] == 0) {
            points.pb(i);
        }
        else if (r[i] > 0) {
            intelligence[points.size()][r[i]]++;
        }
        else {
            strength[points.size()][-r[i]]++;
        }
    }

    for (int i = 0; i <= M; i++) {
        for (int j = 1; j <= M; j++) {
            intelligence[i][j] += intelligence[i][j - 1];
            strength[i][j] += strength[i][j - 1];
        }
    }

    dp[0][1] = dp[0][0] = 0;
    for (int i = 1; i < M; i++) {
        int tot = i + 1;
        for (int s = 0; s <= tot; s++) {
            if (s) {
                makemax(dp[i][s], dp[i - 1][s - 1] + intelligence[i][s - 1] + strength[i][i - s + 1]);
            }
            if (s != i + 1) {
                makemax(dp[i][s], dp[i - 1][s] + intelligence[i][s] + strength[i][i - s]);
            }
        }
    }

    int ans = 0;
    for (int s = 0; s <= M; s++) {
        makemax(ans, dp[M - 1][s] + intelligence[M][s] + strength[M][M - s]);
    }

    printf("%d\n", ans);

    return 0;
}