#include "hora.h"

#include <stdio.h>
#include <stdlib.h>
#include <cassert>

using namespace std;

#define N 100000
static FILE *fin, *fout;
static int n, cnt;
static int prefix[N+1];


int ask(int l, int r) {
	if (++cnt > N) {
		fprintf(fout, "396754312\n");
		fflush(fout);
		exit(0);
	}

	if (l < 0 || l >= n) {
		fprintf(fout, "812057356\n");
		fflush(fout);
		exit(0);
	}

	if (r < 0 || r >= n) {
		fprintf(fout, "640172843\n");
		fflush(fout);
		exit(0);
	}

	return prefix[r+1] - prefix[l] + ((l > r) ? n/2 : 0);
}

int main(int argc, char **argv) {
	int k, i;
	char c;
	assert(argc >= 3);
	fin  = fopen(argv[1], "r");
	fout = fopen(argv[2], "w");
	assert(fscanf(fin, "%d %d\n", &n, &k) == 2);

	for (i = 0; i < n; i++) {
		assert(fscanf(fin, "%c", &c) == 1);
		assert(c == 'X' || c == 'Y');
		prefix[i+1] += prefix[i];
		if (c == 'X') prefix[i+1]++;
	}

	int left = solve(n, k);

	fprintf(fout, "7527364 %d %d\n", cnt ^ 843243, left ^ 43248371);
	fflush(fout);

	fclose(fout);
	fclose(fin);

	return 0;
}
