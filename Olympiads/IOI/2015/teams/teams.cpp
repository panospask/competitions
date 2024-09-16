#include <bits/stdc++.h>
#include "teams.h"

using namespace std;

typedef pair<int, int> pi;

struct SegTree {
	struct Node {
		Node *l, *r;

		int v;

		Node(int a) {
			v = a;
			l = nullptr;
			r = nullptr;
		}
		Node(Node* a, Node* b) {
			v = 0;
			l = a;
			r = b;
		}
	};

	int size;
	vector<Node*> roots;
	Node* null;

	void init(int N) {
		size = 1;
		while (size < N) {
			size *= 2;
		}

		null = new Node(0);
		null->l = null;
		null->r = null;

		roots.push_back(null);
	}

	Node* add(int i, int v, Node* x, int lx, int rx) {
		x = new Node(x->l, x->r);
		x->v = x->l->v + x->r->v;

		if (lx == rx - 1) {
			x->v += v;
			return x;
		}

		int mid = (lx + rx) / 2;
		if (i < mid) {
			x->l = add(i, v, x->l, lx, mid);
		}
		else {
			x->r = add(i, v, x->r, mid, rx);
		}

		x->v = x->l->v + x->r->v;

		return x;
	}
	int add(int i, int v) {
		roots.push_back(add(i, v, roots.back(), 0, size));
		return roots.size() - 1;
	}

	int sum(int l, int r, Node* x, int lx, int rx) {
		if (l >= rx || lx >= r) {
			return 0;
		}
		else if (l <= lx && rx <= r) {
			return x->v;
		}

		int mid = (lx + rx) / 2;
		return sum(l, r, x->l, lx, mid) + sum(l, r, x->r, mid, rx);
	}
	int sum(int l, int r, int root) {
		return sum(l, r, roots[root], 0, size);
	}

	int kth(int k, Node* x, int lx, int rx) {
		if (x->v < k) {
			return -1;
		}
		if (lx == rx - 1) {
			return lx;
		}

		int mid = (lx + rx) / 2;
		int ans = kth(k, x->l, lx, mid);
		if (ans == -1) {
			ans = kth(k - x->l->v, x->r, mid, rx);
		}

		return ans;
	}

	// Returns the position of the kth 1 if we start counting from pos
	int kth_after(int k, int pos, int root) {
		return kth(k + sum(0, pos, root), roots[root], 0, size);
	}
};

struct Student {
	int a, b;
	int id;
};

struct Event {
	int v;
	bool end;
	int id;
};

bool operator < (Event a, Event b)
{
	if (a.v == b.v) {
		return a.end < b.end;
	}
	return a.v < b.v;
}

int N;
SegTree st;

// Position of each student in the segment tree
vector<Event> events;
vector<Event> insertions;
vector<int> pos;
vector<int> root_id;

void init(int n, int A[], int B[])
{
	N = n;

	pos.resize(N);
	root_id.resize(N);
	st.init(2 * N);

	for (int i = 0; i < N; i++) {
		events.push_back({A[i], false, i});
		events.push_back({B[i], true, i});
		insertions.push_back({A[i], false, i});
	}
	sort(events.begin(), events.end());
	sort(insertions.begin(), insertions.end());

	for (int i = 0; i < 2 * N; i++) {
		if (events[i].end) {
			pos[events[i].id] = i;
		}
	}
	for (int i = 0; i < 2 * N; i++) {
		if (!events[i].end) {
			root_id[events[i].id] = st.add(pos[events[i].id], 1);
		}
	}
}

int can(int M, int K[])
{
	sort(K, K + M);

	vector<int> prv(M);
	vector<int> p_idx(M);
	for (int i = 0; i < M; i++) {
		int start = upper_bound(insertions.begin(), insertions.end(), Event{K[i], false, -1}) - insertions.begin() - 1;
		start = upper_bound(events.begin(), events.end(), insertions[start]) - events.begin() - 1;
		int root = root_id[events[start].id];

		// Somehow must remove extra
		int remove = 0;

		int res = st.kth_after(K[i] + remove, start, root);
		if (res == -1) {
			return 0;
		}

		prv[i] = res;
		p_idx[i] = root;
	}

	return 1;
}
