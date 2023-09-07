#include "Alicelib.h"
#include <cassert>
#include <cstdio>
#define pb push_back
#define CHECK_BIT(val, pos) (val & (1 << pos))
#include <vector>

const int BITS = 10;

using namespace std;

int V, E;

vector<int> C;
vector<int> D;

void Alice( int N, int M, int A[], int B[] ){
	// Just create some new nodes

	V = N;
	E = M;

	// First the bitnodes
	for (int b = 0; b < BITS; b++) {
		for (int i = 0; i < N; i++)
			if (CHECK_BIT(i, b)) {
				C.pb(i);
				D.pb(V);
			}
		if (b) {
			C.pb(V);
			D.pb(V - 1);
		}
		V++;
	}

	// Then the one with all the connections
	for (int i = 1; i <= BITS; i++) {
		C.pb(V);
		D.pb(V - i);
	}
	V++;

	// Then the one with all but this
	for (int i = 0; i < V - 1; i++) {
		C.pb(V);
		D.pb(i);
	}
	V++;

	InitG(V, C.size() + M);
	for (int i = 0; i < M; i++)
		MakeG(i, A[i], B[i]);
	for (int i = 0; i < C.size(); i++)
		MakeG(i + M, C[i], D[i]);

	return;;
}
