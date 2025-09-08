#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100000

/*
   396754312 - Limit exceeded
   812057356 - L out of bounds
   640172843 - R out of bounds
   7527364 q^843243 l^43248371 - Answer
*/

int n, k, subtask;
int prefix[N+1];

const int maxquery_count = 100000;

const int qmax[] = {
	34,
	17,
	34,
	18,
	26,
	26,
	26,
	57,
	34
};

void
quitwa(const char *t)
{
	fprintf(stderr, "%s", t);
	printf("0.0\n");
	exit(0);
}

int
xnumber(int l, int r)
{
	return prefix[r+1] - prefix[l] + ((l > r) ? n/2 : 0);
}

float
formula(int q_made, int n, int q)
{
return (1.0f - pow(((float)q_made - (float)q) / ((float) n), 0.05f));
}

void
score(int sub, int cnt, int n)
{
	if (cnt <= qmax[sub-1]) {
		fprintf(stderr, "translate:success");
		printf("1.0\n");
	} else if(cnt > qmax[sub - 1] && cnt <= n) {
		fprintf(stderr, "translate:partial");
		printf("%f\n", formula(cnt, n, qmax[sub - 1]));
	} else {
		fprintf(stderr, "translate:partial");
		printf("0.0\n");
	}
	exit(0);
}

int
main(int argc, char *argv[])
{
	FILE *fin, *fout;
	int i, qtype, qcnt, l, r;
	char c;
	signal(SIGPIPE, SIG_IGN);

	if (argc < 3) {
		quitwa("Insufficient number of args for manager of 'Hora'");
	}

	fout = fopen(argv[2], "w");
	fin  = fopen(argv[1], "r");
#ifdef LOCAL
	FILE *fstdin = fopen(argv[3], "r");
#else
#define fstdin stdin
#endif
	qcnt = 0;

	assert(fscanf(fstdin, "%d %d %d\n", &n, &k, &subtask) == 3);
	/* TODO: Do it better, maybe with fscanf */
	fprintf(fout, "%d %d\n", n, k);
	fflush(fout);

	for (i = 0; i < n; i++) {
		assert(fscanf(fstdin, "%c", &c) == 1);
		assert(c == 'X' || c == 'Y');
		fprintf(fout, "%c", c);
		prefix[i+1] += prefix[i];
		if (c == 'X') prefix[i+1]++;
	}

	fprintf(fout, "\n");
	fflush(fout);

	/*
	qtype:
		0 - query
		1 - answer
	*/

	if (fscanf(fin, "%d", &qtype) != 1)
		quitwa("Wrong interaction: We can't read the query");

	/* Too many queries */
	if (qtype == 396754312)
		quitwa("Limit of queries exceeded");
	if (qtype == 812057356)
		quitwa("Wrong interaction: 'l' is out of bounds");
	if (qtype == 640172843)
		quitwa("Wrong interaction: 'r' is out of bounds");
	if (qtype != 7527364)
		quitwa("Wrong interaction");

	/* Check whether the query is valid */
	if (fscanf(fin, "%d %d", &qcnt, &l) != 2)
		quitwa("Wrong interaction: We can't read the query");

	qcnt ^= 843243;
	l ^= 43248371;
	/* Check whether the query is valid */
	if (qcnt < 0 || qcnt > N)
		quitwa("Wrong interaction");

	if (l < 0 || l >= n) quitwa("Wrong interaction: answer given is out of bounds");
	r = (l + k - 1) % n;

	if (abs(k - 2 * xnumber(l, r)) > 1)
		quitwa("translate:wrong");

	score(subtask, qcnt, n);
	return 0;
}
