#include "migrations.h"
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int N = 10000;
const int log2N = 14;
const int log4N = 7;
const int START = N - log2N - log4N;
const int POINTS = 2;

vector<vector<int>> adj_list;

// Current endpoints of diameter
int id[POINTS] = {0, 0};
vector<int> d[POINTS];
bool swapped[POINTS] = {false, false};

void calculate_distance(int node, int par, vector<int>& d) {
	for (auto neigh : adj_list[node]) {
		if (neigh != par) {
			d[neigh] = d[node] + 1;
			calculate_distance(neigh, node, d);
		}
	}
}

pi find_max(vector<int>& d) {
	int opt = 0;
	for (int i = 0; i < N; i++) {
		if (d[i] > d[opt]) {
			opt = i;
		}
	}

	return mp(d[opt], opt);
}

pi find_time(int i) {
	if (i - START < log4N) {
		return mp(0, i - START);
	}
	else {
		return mp(1, i - START - log4N);
	}
}

int find_bit(int num, int b) {
	return (num & (1 << b)) != 0;
}

int send_message(int N, int i, int Pi) {
	if (i == 1) {
		adj_list.resize(N);
		d[0].resize(N);
		d[1].resize(N);
	}
	adj_list[i].pb(Pi);
	adj_list[Pi].pb(i);

	swapped[0] = swapped[1] = false;
	for (int p = 0; p < 2; p++) {
		d[p][id[p]] = 0;
		calculate_distance(id[p], -1, d[p]);
		pi res = find_max(d[p]);

		if (d[p][id[!p]] != res.first) {
			id[!p] = res.second;
			swapped[!p] = true;
			break;
		}
	}

	if (i >= START) {
		int p, step;
		tie(p, step) = find_time(i);

		int ans = 0;
		if (p == 1) {
			if (swapped[p]) {
				return 4;
			}
			if (swapped[!p]) {
				ans += 2;
			}

			ans += find_bit(id[p], step);
		}
		else {
			if (swapped[p]) {
				return 4;
			}
			ans += find_bit(id[p], 2 * step);
			ans += 2 * find_bit(id[p], 2 * step + 1);
		}

		return ans;
	}

	return 0;
}

pair<int, int> longest_path(vector<int> S) {
	id[0] = id[1] = 0;
	swapped[0] = swapped[1] = false;

	for (int i = START; i < N; i++) {
		int p, step;
		tie(p, step) = find_time(i);

		int ans = S[i];
		if (ans == 4) {
			id[p] = i;
			swapped[p] = true;
		}
		else {
			if (p == 1) {
				if (ans >= 2) {
					id[!p] = i;
					swapped[!p] = true;
					ans -= 2;
				}
				if (!swapped[p]) {
					id[p] += (ans << step);
				}
			}
			else {
				if (!swapped[p]) {
					id[p] += (ans << (2 * step));
				}
			}
		}
	}

	return mp(id[0], id[1]);
}
