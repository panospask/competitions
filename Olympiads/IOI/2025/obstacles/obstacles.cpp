#include "obstacles.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 1e9 + 2;

typedef pair<int, int> pi;

struct Column {
	int id;
	int h;

	// Ids of nxt and prv
	int nxt_id;
	int prv_id;

	// Gap to nxt;
	int nxt_gap;

};

struct CompareH {
	bool operator()(const Column& a, const Column& b) const {
		if (a.h == b.h) {
			return a.id < b.id;
		}
		return a.h < b.h;
	}
};
struct CompareGap {
	bool operator()(const Column& a, const Column& b) const {
		return a.nxt_gap < b.nxt_gap;
	}
};

int N, M;
vector<int> T, H;
// last[i]: Column j s.t the most down block from i is in column j
vector<int> last;
// Elements in each column
vector<set<int>> elements;

// by_h also allows you to find completely a state
set<Column, CompareH> by_h;
set<Column, CompareGap> by_gap;

Column find_column(int id) {
	Column tmp = {id, H[id], 0, 0};
	return *by_h.lower_bound(tmp);
}

bool check_gap(Column c1, int allowed) {
	if (c1.nxt_gap >= allowed) {
		return false;
	}

	// We can now merge this and nxt
	Column c2 = find_column(c1.nxt_id);
}

void initialize(vector<int> t, vector<int> h) {
  	return;
}

bool can_reach(int L, int R, int S, int D) {
  	return false;
}
