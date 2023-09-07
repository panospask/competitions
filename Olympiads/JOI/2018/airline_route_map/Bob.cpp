#include "Boblib.h"
#include <cassert>
#include <cstdio>
#include <vector>
#include <bits/stdc++.h>
#define pb push_back

const int BITS = 10;

using namespace std;

// Bit nodes, in little endian order
vector<int> bitnodes;
vector<int> real_order;
vector<vector<int>> adj_list;

vector<int> actual;

int edge_ttl = 0;

vector<bool> banned;

int inside(int a, vector<int>& v)
{
	int p = lower_bound(v.begin(), v.end(), a) - v.begin();
	if (p != v.size() && v[p] == a)
		return true;

	return false;
}

int decode(int node)
{
	int res = 0;
	for (int i = 0; i < BITS; i++) {
		if (inside(bitnodes[i], adj_list[node])) {
			res += (1 << i);
			edge_ttl--;
		}
	}

	return res;
}

void find_next_bitnode(int node, int par)
{
	for (auto i : bitnodes) {
		if (i == node || i == par)
			continue;

		if (inside(i, adj_list[node])) {
			real_order.pb(i);
			find_next_bitnode(i, node);
			return;
		}
	}
}

void Bob( int V, int U, int C[], int D[] )
{
	bitnodes.clear();
	adj_list.clear();
	actual.clear();

	edge_ttl = U;

	adj_list.resize(V);
	banned.assign(V, false);
	actual.assign(V, -1);

	for (int i = 0; i < U; i++) {
		adj_list[C[i]].pb(D[i]);
		adj_list[D[i]].pb(C[i]);
	}

	int outl = -1;
	for (int i = 0; i < V; i++) {
		if (adj_list[i].size() == V - 2)
			outl = i;

		sort(adj_list[i].begin(), adj_list[i].end());
	}

	// Find the node not connected to outlier
	int curp = 0;
	int special = -1;
	for (int i = 0; i < V - 1; i++) {
		if (i == outl)
			continue;

		if (adj_list[outl][curp++] != i) {
			special = i;
			break;
		}
	}
	if (special == -1)
		special = V - 1;

	banned[special] = banned[outl] = true;
	edge_ttl -= adj_list[special].size() + adj_list[outl].size();
	edge_ttl -= BITS - 1;

	// Found special, find bitnodes
	for (auto neigh : adj_list[special]) {
		bitnodes.pb(neigh);
		banned[neigh] = true;
	}

	// Find correct ordering
	// Find one of the starts

	int st = -1;
	for (int i = 0; i < BITS; i++) {
		int cnt = 0;
		for (int j = 0; j < BITS; j++) {
			if (inside(bitnodes[j], adj_list[bitnodes[i]]))
				cnt++;
		}
		if (cnt == 1)
			st = bitnodes[i];
	}
	real_order.pb(st);
	find_next_bitnode(st, -1);

	if (adj_list[real_order.front()].size() < adj_list[real_order.back()].size())
		reverse(real_order.begin(), real_order.end());
	bitnodes = real_order;

	for (int i = 0; i < V; i++) {
		if (!banned[i])
			actual[i] = decode(i);
	}

	InitMap(V - BITS - 2, edge_ttl);

	for (int i = 0; i < V; i++)
		for (auto j : adj_list[i]) {
			if (!banned[i] && !banned[j] && actual[i] < actual[j])
				MakeMap(actual[i], actual[j]);
		}
}
