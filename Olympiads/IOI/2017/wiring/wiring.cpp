#include "wiring.h"
#include <math.h>
#include <iostream>

#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18;

struct Group {
	int cnt;
	vector<int> positions;
	int first;
	int last;

	// Prefix sums to first, suffix sums to last
	vector<ll> pref;

	Group (void) {;}

	void precalc_group(void) {
		first = positions.front();
		last = positions.back();

		cnt = positions.size();

		pref.resize(positions.size() + 1);

		pref[0] = 0;
		for (int i = 0; i < positions.size(); i++)
			pref[i + 1] = pref[i] + positions[i];
	}

	ll get_total(int l, int r)
	{
		// Returns the sum of positions in the range [l..r)
		return pref[r] - pref[l];
	}

	int size(void) {
		return cnt;
	}
};

int N, M;

// dp[i][j] : We have paired up everything in groups i - 1 and back, and the first j ones in group i
// When processing dp[i][j], we will never touch dp[i - 1] and before again
vector<vector<ll>> dp;

// Group size for each group
vector<Group> groups;

long long min_total_length(std::vector<int> r, std::vector<int> b) {
	N = r.size();
	M = b.size();

	int cur = -1;
	int r_p = 0, b_p = 0;

	while (r_p < r.size() || b_p < b.size()) {
		int add = 0;
		if (r_p == r.size()) {
			add = 1;
		}
		else if (b_p == b.size()) {
			add = 0;
		}
		else {
			if (r[r_p] < b[b_p])
				add = 0;
			else
				add = 1;
		}

		if (cur != add) {
			// Create new group
			if (cur != -1) {
				groups.back().precalc_group();
			}

			groups.pb(Group());
			cur = add;
		}

		if (add == 0) {
			groups.back().positions.pb(r[r_p]);
			r_p++;
		}
		else {
			groups.back().positions.pb(b[b_p]);
			b_p++;
		}
	}
	groups.back().precalc_group();

	dp.resize(groups.size());
	dp[0].assign(groups[0].cnt + 1, INF);
	dp[0][0] = 0;

	for (int g = 0; g < groups.size() - 1; g++) {
		dp[g + 1].assign(groups[g + 1].size() + 1, INF);

		for (int j = 0; j < groups[g].size(); j++) {
			// The first element to be paired is in position j
			// Pair it with the leftmost element of the next group

			dp[g][j + 1] = min(dp[g][j + 1], dp[g][j] + abs(groups[g].positions[j] - groups[g + 1].first));
		}

		for (int j = 0; j <= min(groups[g].size(), groups[g + 1].size()); j++) {
			// Connect the last j from group g with the first j from group g + 1
			// Assume all previous sockets in group g are connected

			// Number of connected sockets in group g
			int v = groups[g].size() - j;

			ll connection_cost = groups[g + 1].get_total(0, j) - groups[g].get_total(groups[g].size() - j, groups[g].size());

			dp[g + 1][j] = min(dp[g + 1][j], dp[g][v] + connection_cost);
		}

		for (int j = 0; j < groups[g + 1].size(); j++) {
			// In dp[g + 1][j], the next element to be paired is j
			// Pair this with the rightmost element of this group

			dp[g + 1][j + 1] = min(dp[g + 1][j + 1], dp[g + 1][j] + abs(groups[g + 1].positions[j] - groups[g].last));
		}
	}

	return dp[groups.size() - 1][groups.back().size()];
}
