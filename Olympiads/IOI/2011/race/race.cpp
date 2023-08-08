#include "race.h"
#include "vector"
#include "unordered_map"

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int INF = 1e9;

int N, K;
int shift;
int moves_shift;
int ans = INF;
vector<vector<pi>> adj_list;
vector<int> sz;
unordered_map<int, int> minv;
vector<int> dep;
vector<int> dist;

// Euler tour variables
vector<int> tin;
vector<int> tout;
vector<int> trav;
int counter = 0;

void calculate(int node, int par, bool is_heavy)
{
	int BigKid = -1;
	int BigW = 0;
	int BigV = 0;

	for (auto [neigh, w] : adj_list[node]) {
		if (neigh != par && sz[neigh] > BigV) {
			BigKid = neigh;
			BigW = w;
			BigV = sz[neigh];
		}
	}

	for (auto [neigh, w] : adj_list[node]) {
		if (neigh != par && neigh != BigKid)
			calculate(neigh, node, false);
	}
	if (BigKid != -1) {
		calculate(BigKid, node, true);
		shift -= BigW;
		moves_shift++;
	}

	if (minv.find(K + shift) != minv.end())
		ans = min(ans, minv[K + shift] + moves_shift);
	minv[shift] = -moves_shift;
	for (auto [neigh, w] : adj_list[node]) {
		if (neigh == par || neigh == BigKid)
			continue;

		for (int t = tin[neigh]; t < tout[neigh]; t++) {
			int cur = trav[t];
			int len = dist[cur] - dist[node];
			int compliment = K - len;
			int v = dep[cur] - dep[node];

			if (minv.find(compliment + shift) != minv.end())
				ans = min(ans, minv[compliment + shift] + moves_shift + v);
		}
		for (int t = tin[neigh]; t < tout[neigh]; t++) {
			int cur = trav[t];
			int len = dist[cur] - dist[node];
			int v = dep[cur] - dep[node];

			if (minv.find(len + shift) != minv.end())
				minv[len + shift] = min(minv[len + shift], v - moves_shift);
			else
				minv[len + shift] = v - moves_shift;
		}
	}

	if (!is_heavy) {
		for (int t = tin[node]; t < tout[node]; t++) {
			int cur = trav[t];
			int len = dist[cur] - dist[node];

			minv.erase(len + shift);
		}
		shift = K;
		moves_shift = 0;
	}
}

void init(int node, int par)
{
	tin[node] = counter++;
	trav[tin[node]] = node;

	sz[node] = 1;
	for (auto [neigh, w] : adj_list[node]) {
		if (neigh == par)
			continue;

		dep[neigh] = dep[node] + 1;
		dist[neigh] = dist[node] + w;

		init(neigh, node);

		sz[node] += sz[neigh];
	}

	tout[node] = counter;
}

int best_path(int n, int k, int H[][2], int L[])
{
	N = n;
	K = k;

	adj_list.resize(N);
	sz.resize(N);
	dep.resize(N);
	dist.resize(N);

	shift = K;

	tin.resize(N);
	tout.resize(N);
	trav.resize(N);

	for (int i = 0; i < N - 1; i++) {
		int u = H[i][0];
		int v = H[i][1];
		int w = L[i];

		adj_list[u].pb(mp(v, w));
		adj_list[v].pb(mp(u, w));
	}

	init(0, -1);
	calculate(0, -1, true);

	if (ans >= N)
		return -1;
	else
		return ans;
}
