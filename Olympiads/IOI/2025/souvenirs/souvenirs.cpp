#include "souvenirs.h"
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

void buy_souvenirs(int N, ll P0) {
	
	vector<int> times(N, 0);

	ll candidate = P0 - 1;
	for (int i = 1; i < N; i++) {
 		while (times[i] < i) {
			pair<vector<int>, ll> res = transaction(candidate);
			times[i]++;
			if (res.first.size() >= 2) {
				times[N - 1]++;
				candidate--;
			}
			if (res.second) {
				candidate--;
			}
		}

		candidate--;
	}
  	return;
}
