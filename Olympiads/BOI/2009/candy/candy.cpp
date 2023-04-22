#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int main() {
	int n;
	cin >> n;

	vector<pi> candies(n);
	vector<int> lis(n + 1);
	vector<vector<pi>> candies_caught(n + 1);

	for (int i = 0; i < n; i++) {
		int s, t;
		cin >> s >> t;
		candies[i] = make_pair(s - t, s + t);
	}

	/*
	 * Sort the segments by left endpoint
	 * NOTE: It is important to sort segments of same left point by decreasing
	 * right point so they count as nested
	 */
	sort(candies.begin(), candies.end(), [](const pi &a, const pi &b) -> bool {
		return (a.first == b.first ? a.second > b.second : a.first < b.first);
	});

	for (int len = 0; len <= n; len++) { lis[len] = INT_MAX; }
	lis[0] = 0;
	for (int i = 0; i < n; i++) {
		int r_point = candies[i].second;

		int l = 0;  // Condition: lis[l] < r_point
		int r = n;  // Condition: lis[r] >= r_point
		while (r > l + 1) {
			int mid = (l + r) / 2;
			if (lis[mid] < r_point) {
				l = mid;
			} else {
				r = mid;
			}
		}
		lis[l + 1] = r_point;
		// Candies with the same lis length can be caught by the same wagon
		candies_caught[l + 1].push_back(candies[i]);
	}

	int ans = 0;
	while (ans < n && lis[ans + 1] != INT_MAX) { ans++; }

	cout << ans << "\n";
	for (int len = 1; len <= ans; len++) {
		for (pi c : candies_caught[len]) {
			int s = (long long)(c.first + c.second) / 2;
			int t = (long long)(c.second - c.first) / 2;

			cout << s << " " << t << " " << len << "\n";
		}
	}
}
