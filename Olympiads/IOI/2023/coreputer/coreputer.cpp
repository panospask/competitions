#include "coreputer.h"

using namespace std;

vector<int> malfuction;

vector<int> include_range(int l, int r, int skipped = -1)
{
	vector<int> v;
	for (int i = l ; i <= r; i++) {
		if (i != skipped)
			v.push_back(i);
	}

	return v;
}

vector<int> malfunctioning_cores(int N)
{
	malfuction.assign(N, 0);

	// Binary search on the first idx such that include_range(0, idx) contains more cores
	int l = -1;
	int r = N - 1;

	while (r > l + 1) {
		int mid = (l + r) / 2;
		if (run_diagnostic(include_range(0, mid)) == 1)
			r = mid;
		else
			l = mid;
	}
	malfuction[r] = true;

	if (r == N - 1) {
		// Either 1 or 2 cores, the one is at N - 1
		// Special case because we cannot cut with the normal way

		if (N == 2) {
			if (run_diagnostic({0}) == 0)
				malfuction[0] = 1;

			return malfuction;
		}

		bool exists = false;
		int found = r - 1;
		for (int i = 0; i < min(r, 14); i++) {
			int res = run_diagnostic(include_range(0, r - 1, i));
			if (res == 0) {
				exists = true;
			}
			if (res == -1) {
				found = i;
			}
		}

		if (exists)
			malfuction[found] = true;

		return malfuction;
	}

	// The idx at position r is a coreputer for sure
	// Check all indexes in positions [0..l]
	bool are_equal = false;
	int cnt = 0;
	for (int i = 0; i < r; i++) {
		int res = run_diagnostic(include_range(0, r, i));
		if (res < 1) {
			malfuction[i] = true;
			cnt++;
			are_equal = are_equal || res == 0;
		}
	}

	// Calculate the remaining malfunctioning cores
	int rem = cnt - are_equal;

	// Check all cores in the range [r+1...N-2], the last one can be deduced
	for (int i = r + 1; i < N - 1; i++) {
		int res = run_diagnostic(include_range(r, N - 1, i));
		if (res == -1) {
			rem--;
			malfuction[i] = true;
		}
	}

	if (rem)
		malfuction[N - 1] = true;

	return malfuction;
}
