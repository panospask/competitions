#include <bits/stdc++.h>
#include "cyklib.hpp"
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 1;
const int MAXLEN = 100;

// A[i]: Value at position 2^i
vector<ll> A;

// pos[i]: If length is i, what position are we at?
vector<int> pos;

void update_position(int l, int r, int steps)
{
	for (int i = l; i < r; i++) {
		pos[i] = (pos[i] + steps) % i;
	}
}

int main(void) 
{
	int minlen = 1;
	A.pb(circular_shift(0));

	while (true) {
		A.pb(circular_shift(minlen));
		update_position(minlen, MAXLEN, minlen);

		if (A.back() > A[A.size() - 2]) {
			minlen *= 2;
		}
		else {
			break;
		}
	}

	ll landed = A.back();
	A.pop_back();

	int bef = lower_bound(A.begin(), A.end(), landed) - A.begin();
	int l_len = 2 * minlen - (1 << bef);
	if (A[bef] == landed) {
		give_answer(l_len);
	}
	int r_len = 2 * minlen - (1 << (bef - 1));

	int l_pos = 1 << (bef - 1);
	int r_pos = 1 << bef;



	return 0;
}
