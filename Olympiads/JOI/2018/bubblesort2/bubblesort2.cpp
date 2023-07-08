#include "bubblesort2.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct SegTree {
	const ll NO_OP = 0;
	const ll NEUTRAL = 0;

	int size;
	vector<ll> tree;
	vector<ll> operations;

	void init(int n) {
		size = 1;
		while (size < n)
			size *= 2;

		tree.resize(2 * size, NEUTRAL);
		operations.assign(2 * size, NO_OP);
	}

	void propagate(int x) {
		tree[2 * x + 1] += operations[x];
		tree[2 * x + 2] += operations[x];
		operations[2 * x + 1] += operations[x];
		operations[2 * x + 2] += operations[x];

		operations[x] = NO_OP;
	}

	void modify(int l, int r, int v, int x, int lx, int rx) {
		if (l >= rx || lx >= r) {
			return;
		}
		else if (l <= lx && rx <= r) {
			tree[x] += v;
			operations[x] += v;
			return;
		}

		propagate(x);

		int mid = (lx + rx) / 2;
		modify(l, r, v, 2 * x + 1, lx, mid);
		modify(l, r, v, 2 * x + 2, mid, rx);

		tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
	}
	void modify(int l, int r, int v) {
		modify(l, r, v, 0, 0, size);
	}

	ll calc(int l, int r, int x, int lx, int rx) {
		if (l >= rx || lx >= r) {
			return NEUTRAL;
		}
		else if (l <= lx && rx <= r) {
			return tree[x];
		}

		propagate(x);

		int mid = (lx + rx) / 2;
		ll c1 = calc(l, r, 2 * x + 1, lx, mid);
		ll c2 = calc(l, r, 2 * x + 2, mid, rx);

		return max(c1, c2);
	}
	ll calc(int l, int r) {
		return max(calc(l, r, 0, 0, size), 0ll);
	}
};

int N;
set<int> seen;
vector<set<int>> latest;
unordered_map<int, int> compress;
vector<int> startv;

SegTree st;

vector<int> countScans(vector<int> A, vector<int> X, vector<int> V)
{
	// Coordinate compression
	for (int i = 0; i < A.size(); i++)
		seen.insert(A[i]);
	for (int i = 0; i < V.size(); i++)
		seen.insert(V[i]);
	for (auto val : seen)
		compress[val] = N++;

	latest.resize(N);
	st.init(N);
	for (int val = 0; val < N; val++)
		latest[val].insert(0);
	for (int i = 0; i < A.size(); i++) {
		A[i] = compress[A[i]];
		latest[A[i]].insert(i + 1);

		st.modify(A[i], N, -1);
	}

	for (int val = 0; val < N; val++) {
		st.modify(val, val + 1, *latest[val].rbegin());
	}

	vector<int> ans;
	for (int q = 0; q < X.size(); q++) {
		int i = X[q];
		int val = compress[V[q]];
		int prev = A[i];

		// Take care of the old value first
		st.modify(prev, N, +1);
		st.modify(prev, prev + 1, - *latest[prev].rbegin());
		latest[prev].erase(i + 1);
		st.modify(prev, prev + 1, *latest[prev].rbegin());

		// Proccess the new value
		st.modify(val, N, -1);
		st.modify(val, val + 1, - *latest[val].rbegin());
		latest[val].insert(i + 1);
		st.modify(val, val + 1, *latest[val].rbegin());

		A[i] = val;
		ans.push_back(st.calc(0, N));
	}

	return ans;
}