#include "happiness.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> pl;

struct SegTree {
	const ll NO_OP = 0;
	struct Node {
		// v is min(a[i] - i) for all i in node
		ll sum;
		ll min;

		Node *l, *r;

		Node(ll a, ll b, Node* c, Node* d) : sum(a), min(b), l(c), r(d) {};
	};
	Node* null;
	const pl NEUTRAL = {0, 0};

	ll size;
	Node* root;
	void init(ll n) {
		size = 1;
		while (size < n)
			size *= 2;

		null = new Node(0, 0, nullptr, nullptr);
		null->l = null->r = null;
		root = new Node(0, -size + 1, null, null);
	}

	void modify(ll i, ll v, Node* x, ll lx, ll rx) {
		if (lx == rx - 1) {
			x->sum += v * i;
			x->min += v * i;

			return;
		}

		ll mid = (lx + rx) / 2;

		if (i < mid) {
			if (x->l == null) {
				x->l = new Node(0, -mid + 1, null, null);
			}
			modify(i, v, x->l, lx, mid);

			ll m = x->r == null ? -rx + 1 : x->r->min;
			x->min = min(x->l->min, x->l->sum + m);
		}
		else {
			if (x->r == null) {
				x->r = new Node(0, -rx + 1, null, null);
			}
			modify(i, v, x->r, mid, rx);

			ll s = x->l->sum;
			ll m = x->l == null ? -mid + 1 : x->l->min;
			x->min = min(m, s + x->r->min);
		}

		x->sum += v * i;

		return;
	}
	void modify(ll i, ll v) {
		modify(i, v, root, 0, size);
	}

	pl calc(ll l, ll r, Node* x, ll lx, ll rx) {
		if (l >= rx || lx >= r) {
			return NEUTRAL;
		}
		if (x == null) {
			return {0, -min(r, rx)};
		}
		else if (l <= lx && rx <= r) {
			return {x->sum, x->min};
		}

		ll mid = (lx + rx) / 2;
		pl p1 = calc(l, r, x->l, lx, mid);
		pl p2 = calc(l, r, x->r, mid, rx);

		return {p1.first + p2.first, min(p1.second, p1.first + p2.second)};
	}
	ll calc(ll l, ll r) {
		pl v = calc(l, r, root, 0, size);
		// cerr << v.first << endl;
		return v.second;
	}
};

SegTree st;
ll M;
ll cursum = 0;

int checkgood(void)
{
	ll v = st.calc(0, min(M, cursum));
	// fprintf(stderr, "The minimum is %lld\n", v);
	return v >= 0;
}

bool init(int coinsCount, long long maxCoinSize, long long coins[]) {
	M = maxCoinSize + 1;
	st.init(M);

	sort(coins, coins + coinsCount);

	for (int i = 0; i < coinsCount; i++) {
		st.modify(coins[i], 1);
		cursum += coins[i];
	}

	return checkgood();
}

bool is_happy(int event, int coinsCount, long long coins[]) {
	for (int i = 0; i < coinsCount; i++) {
		st.modify(coins[i], event);
		cursum += coins[i] * event;
	}

	return checkgood();
}