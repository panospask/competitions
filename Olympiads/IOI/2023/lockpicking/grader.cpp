#include "lockpicking.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <fstream>

static int callCount = 0;
static int M, j0;
static std::vector<int> B;
static std::vector<std::vector<int>> T;

static std::ofstream output;

static void protocol_violation(std::string message) {
	printf("Protocol Violation: %s\n", message.c_str());
	exit(0);
}

static void output_device(int N, int cparam, std::vector<int> A, std::vector<std::vector<int>> S) {
	output.put(N >> 8);
	output.put(N & 0xff);
	output.put(cparam >> 8);
	output.put(cparam & 0xff);
	for (int i = 0; i < N; ++i) {
		output.put(A[i]);
		int s0 = S[i][0], s1 = S[i][1];
		output.put(s0 >> 8);
		output.put(s0 & 0xff);
		output.put(s1 >> 8);
		output.put(s1 & 0xff);
	}
}

void define_states(int _M, std::vector<int> _B, std::vector<std::vector<int>> _T, int _j0) {
	if (++callCount > 1) {
		protocol_violation("too many calls");
	}
	if (_M <= 0 || _M > 50000) {
		protocol_violation("invalid number");
	}
	M = _M;
	if ((int)_B.size() != M || (int)_T.size() != M) {
		protocol_violation("invalid array");
	}
	for (int b : _B) {
		if (b != 0 && b != 1)
			protocol_violation("invalid bit");
	}
	for (auto& t : _T) {
		if ((int)t.size() != 2)
			protocol_violation("invalid array");
		if (t[0] < 0 || t[0] >= M || t[1] < 0 || t[1] >= M)
			protocol_violation("invalid state");
	}
	B = _B, T = _T;
	if (_j0 < 0 || _j0 >= M)
		protocol_violation("invalid initial state");
	j0 = _j0;
}

int main() {
	int N, K;
	assert(2 == scanf("%d %d", &N, &K));
	std::vector<int> A(N);
    std::vector<std::vector<int>> S(N, std::vector<int>(2));
    for (int i = 0; i < N; ++i) {
        assert(3 == scanf("%d %d %d", &A[i], &S[i][0], &S[i][1]));
    }
	fclose(stdin);

	construct_card(N, A, S);
	if (callCount == 0) {
		protocol_violation("missing call");
	}

	printf("%d %d\n", M, j0);
	for (int j = 0; j < M; ++j) {
        printf("%d %d %d\n", B[j], T[j][0], T[j][1]);
    }
	fclose(stdout);

	output.open("lockpicking.bin", std::ios::binary);
	output_device(N, K, A, S);
	output_device(M, j0, B, T);
	output.close();

	return 0;
}
