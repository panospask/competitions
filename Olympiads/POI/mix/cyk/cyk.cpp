#include <bits/stdc++.h>
#include "cyklib.hpp"
#define pb push_back

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 1;

ll PREVIOUS_ELEMENT = -1;

/* Returns true iff x is bigger than the length of the sequence
 * It is necessary that:
 * x / 2 <= len < 2 * x 
 * for the function to work
 */
bool bigger(int x)
{
	int first = x / 2;
	int sec = x - first;

	ll r1 = PREVIOUS_ELEMENT;
	ll r2 = circular_shift(first);
	ll r3 = circular_shift(sec);

	// How many times did the sequence circle fron the last element to the first?
	int times = (r1 >= r2) + (r2 >= r3);

	assert(times >= 0 && times <= 2);

	PREVIOUS_ELEMENT = r3;

	if (times == 2) {
		// We covered a distance greater than len by moving x, therefore x is greater than len
		return true;
	}	
	else if (times == 1) {
		// Only circled back to the start once.
		return r3 > r1;
	}
	else {
		// We have not even circled back once, therefore x is less than the length of the sequence
		return false;
	}
}

int main(void) 
{
	int minlen = 1;
	ll prv = circular_shift(0);
	ll first = prv;
	ll cur;

	int l, r;

	while (true) {
		cur = circular_shift(minlen);

		if (cur > prv) {
			minlen *= 2;
			prv = cur;
		}
		else {
			break;
		}
	}

	if (cur < first) {
		int x = minlen;
		minlen = 1;
		prv = cur;

		while (true) {
			cur = circular_shift(minlen);

			if (cur > prv) {
				minlen *= 2;
				prv = cur;
			}
			else {
				break;
			}
		}

		// Since x < minlen we gather that l >= 3r, hence for all the queries bigger(mid) the condition is fullfilled.
		l = minlen;
		r = 2 * minlen + x;
	}
	else {
		l = minlen;
		r = 2 * minlen + 1;
	}

	PREVIOUS_ELEMENT = cur;

	// The sequence has size greater than or equal to l and smaller than r
	while (l + 1 < r) {
		int mid = (l + r) / 2;
		if (bigger(mid)) {
			r = mid;
		}
		else {
			l = mid;
		}
	}

	give_answer(l);

	return 0;
}
