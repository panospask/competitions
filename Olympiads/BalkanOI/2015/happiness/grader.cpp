#include "happiness.h"
#include <stdio.h>
#include <stdlib.h>

#define NMAX 200000
#define QMAX 100000

static int N, Q;
static long long M;
static long long coins[NMAX], A[5];

int main()
{
	int i, d;
	long long max_code;

	scanf("%d%lld", &N, &M);
	for (i = 0; i < N; ++i) {
		scanf("%lld", &coins[i]);
	}
	if (init(N, M, coins))printf("1\n");
	else printf("0\n");
	scanf("%d", &Q);
	for (i = 0; i < Q; ++i) {
		int ck, c;
		scanf("%d%d", &ck, &c);
		for (int j = 0; j < c; j++) {
			scanf("%lld", &A[j]);
		}
		if (is_happy(ck, c, A))printf("1\n");
		else printf("0\n");
	}

	return 0;
}
