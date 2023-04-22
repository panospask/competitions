#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 300

using namespace std;

typedef pair<int, int> ii;

struct cow {
	int l, r, weight;
};
typedef struct cow Cow;

int n, m;

// dp[l][r]: The heaviest way such that the cows eat ** a subset** of the pies
// in [l..r]
long long int dp[MAXN + 2][MAXN + 2];

// max_cow[l][r][i]: The heaviest cow with enpoints within [l..r] that passes
// through i
int max_cow[MAXN + 2][MAXN + 2][MAXN + 2];

int main(void) {
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);

	scanf("%d %d", &n, &m);
	int w, l, r;
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &w, &l, &r);
		l--;
		r--;
		for (int j = l; j <= r; j++)
			max_cow[l][r][j] = max(max_cow[l][r][j], w);
	}

	for (int spot = 0; spot < n; spot++)
		for (int len = 2; len <= n; len++)
			for (int l = 0; l <= n - len; l++) {
				int r = len + l - 1;

				max_cow[l][r][spot] = max(max_cow[l][r][spot], max_cow[l][r-1][spot]);
                max_cow[l][r][spot] = max(max_cow[l][r][spot], max_cow[l+1][r][spot]);
			}

    for (int len = 1; len <= n; len++)
        for (int l = 0; l <= n - len; l++) {
            int r = len + l - 1;
            dp[l][r] = 0;

            if (l == r) {
                dp[l][r] = max_cow[l][r][l];
            }
            else {
                for (int i = l; i < r; i++) {
                    dp[l][r] = max(dp[l][r], dp[l][i] + dp[i+1][r]);
                    if (i != l) {
                        dp[l][r] = max(dp[l][r], dp[l][i-1] + max_cow[l][r][i] + dp[i+1][r]);
                    }
                }
                dp[l][r] = max(dp[l][r], dp[l][r-1] + max_cow[l][r][r]);
                dp[l][r] = max(dp[l][r], max_cow[l][r][l] + dp[l+1][r]);
            }

        }

	printf("%lld\n", dp[0][n - 1]);
	return 0;
}