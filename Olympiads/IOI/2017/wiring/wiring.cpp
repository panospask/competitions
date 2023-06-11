#include "wiring.h"
#include <math.h>
#include <iostream>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

int n, m;
vector<vector<ll>> dp;

long long min_total_length(std::vector<int> r, std::vector<int> b) {
	n = r.size();
	m = b.size();

	if (r.back() < b.front()) {
		ll ans = 0;
		int rfocal = r.back();
		int bfocal = b.front();

		int cnt = 0;
		while (cnt < n && cnt < m) {
			int rpoint = r[n - 1 - cnt];
			int bpoint = b[cnt];

			ans += abs(rpoint - bpoint);
			cnt++;
		}

		for (int i = cnt; i < n; i++) {
			ans += abs(r[n - 1 - i] - bfocal);
		}
		for (int i = cnt; i < m; i++) {
			ans += abs(b[i] - rfocal);
		}

		return ans;
	}
	else if (n <= 10000 && m <= 10000) {
		dp.assign(n, vector<ll>(m, INF));

		dp[0][0] = abs(r[0] - b[0]);

		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (i != n - 1) {
					dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + abs(r[i + 1] - b[j]));
				}
				if (j != m - 1) {
					dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + abs(r[i] - b[j + 1]));
				}
				if (i != n - 1 && j != m - 1) {
					dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + abs(r[i + 1] - b[j + 1]));
				}
			}

		return dp[n - 1][m - 1];
	}

	return -1;
}
