#include "lockpicking.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 150;

int M;
unordered_map<bitset<MAXN>, int> done;

vector<int> B;
vector<vector<int>> T;

int N;
vector<int> A;
vector<vector<int>> S;

bool operator <(const bitset<MAXN>& a, const bitset<MAXN>& b)
{
	int i = a._Find_first();
	int j = b._Find_first();

	while (i == j) {
		i = a._Find_next(i);
		j = b._Find_next(j);
	}

	return i < j;
}

int get_state(bitset<MAXN>& b)
{

	if (done.find(b) != done.end()) {
		return done[b];
	}
	int cur = M++;

	done[b] = cur;
	B.push_back(0);
	T.push_back(vector<int>(2));

	int cnt[2];
	bitset<MAXN> nxt[2];

	nxt[0].reset();
	nxt[1].reset();
	cnt[0] = cnt[1] = 0;

	for (int i = b._Find_first(); i < N; i = b._Find_next(i)) {
		cnt[A[i]]++;
	}

	if (cnt[0] > cnt[1]) {
		B[cur] = 0;
	}
	else {
		B[cur] = 1;
	}

	for (int i = b._Find_first(); i < N; i = b._Find_next(i)) {
		nxt[A[i]].set(S[i][B[cur]]);
	}

	T[cur][0] = get_state(nxt[0]);
	T[cur][1] = get_state(nxt[1]);

	return cur;
}

void construct_card(int n, vector<int> a, vector<std::vector<int>> s) {
	A = a;
	S = s;
	N = n;

	bitset<MAXN> init;
	for (int i = 0; i < N; i++)
		init.set(i);

	get_state(init);

	define_states(M, B, T, 0);
}
