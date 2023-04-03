#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20
#define MAXL ((int)1e8)
#define CHECK_BIT(var, pos) (var & (1 << pos))

using namespace std;

typedef pair<int, int> ii;

//dp[i]: The maximum time we can reach by watching the movies with bits on
long long int dp[(1<<MAXN)];
int n, l;

int duration[MAXN + 2];
vector<int> showtimes[MAXN + 2];

int main(void)
{
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);

    scanf("%d %d", &n, &l);
    int c;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &duration[i], &c);
        showtimes[i].resize(c);
        for (int j = 0; j < c; j++)
            scanf("%d", &showtimes[i][j]); 
    }

    dp[0] = 0;
    int ans = -1;
    for (int s = 0; s < (1<<n); s++) {
        for (int i = 0; i < n; i++) {
            if (CHECK_BIT(s, i)) {
                // What if movie i is watched last
                int prev_subset = s ^ (1<<i);

                int latest_show = upper_bound(showtimes[i].begin(), showtimes[i].end(), dp[prev_subset]) - showtimes[i].begin();
                latest_show--;

                dp[s] = max(dp[s], (long long int)showtimes[i][latest_show] + duration[i]);
            } 
        }

        if (dp[s] >= l) {
            int tmp_ans = 0;
            int tmp = s;
            while (tmp) {
                if (tmp & 1)
                    tmp_ans++;
                tmp /= 2;
            }

            if (ans != -1)
                ans = min(ans, tmp_ans);
            else 
                ans = tmp_ans;
        }
    }

    printf("%d\n", ans);
    return 0;
}