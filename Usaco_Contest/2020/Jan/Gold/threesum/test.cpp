#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MAX_VAL = 1e6;

int main() {
	freopen("threesum.in", "r", stdin);
	freopen("threesum.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);

	int n, q;
	cin >> n >> q;

	vector<int> val(n);
	for (int i = 0; i < n; i++) {
		cin >> val[i];
		val[i] += MAX_VAL;
	}

	// number of triplets such that i and k are fixed
	vector<vector<ll>> ways(n, vector<ll>(n, 0));
	vector<int> frq(2 * MAX_VAL);

	for (int i = n - 2; i >= 0; i--) {
		// be careful to only consider values in between i and j
		frq[val[i + 1]]++;

		for (int j = i + 2; j < n; j++) {
			// separate val from shifted amt
			int compliment = (MAX_VAL * 3) - (val[i] + val[j]);

			if (compliment >= 0 && compliment < (2 * MAX_VAL)) {
				ways[i][j] = frq[compliment];
			}
			frq[val[j]]++;
		}

		for (int j = i + 1; j < n; j++) { frq[val[j]]--; }
	}

	// essentially 2D prefix sum on ways
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			ways[i][j] +=
			    (ways[i + 1][j] + ways[i][j - 1] - ways[i + 1][j - 1]);
		}
	}

	for (int _ = 0; _ < q; _++) {
		int l, r;
		cin >> l >> r;
		cout << ways[l - 1][r - 1] << '\n';
	}
}