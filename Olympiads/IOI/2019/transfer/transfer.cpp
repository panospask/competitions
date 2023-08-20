#include "transfer.h"
#include <math.h>

#define CHECK_BIT(val, pos) ((1 << pos) & val)

using namespace std;

vector<int> get_attachment(vector<int> source) {
	int N = source.size();
	int M = ceil(log2(N));

	vector<int> extra(M, 0);
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (CHECK_BIT(i, j))
				extra[j] ^= source[i];
		}
	}

	for (int j = 0; j < M; j++) {
		extra[j] ^= source[0];
	}

	int xorextra = 0;
	for (int i = 0; i < M; i++)
		xorextra ^= extra[i];
	extra.push_back(xorextra);


	return extra;
}


vector<int> retrieve(vector<int> data) {
	vector<int> source;
	vector<int> extras;

	int xorextra = data.back();
	data.pop_back();

	int N = 1;
	while (N + ceil(log2(N)) < data.size()) {
		N++;
	}
	int M = 0;

	M = ceil(log2(N));

	source = vector<int>(data.begin(), data.begin() + N);
	extras = vector<int>(data.begin() + N, data.end());

	int xorsum = 0;
	for (int i = 0; i < M; i++)
		xorsum ^= extras[i];
	if (xorsum != xorextra) {
		return source;
	}

	vector<int> cur_sum(M, 0);
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (CHECK_BIT(i, j))
				cur_sum[j] ^= source[i];
		}
	}
	for (int j = 0; j < M; j++)
		cur_sum[j] ^= source[0];

	int pos = 0;
	for (int j = 0; j < M; j++) {
		if (extras[j] != cur_sum[j])
			pos += 1 << j;
	}

	if (pos) {
		if (pos == (1 << M) - 1)
			source[0] ^= 1;
		else
			source[pos] ^= 1;
	}

	return source;
}
