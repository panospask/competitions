#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int SPECIAL = -1;
const int GENS = 5;
const int FIRST = 4;

typedef long long ll;

int N;
vector<int> genome;

int cnt[GENS][GENS][GENS];
int prv[GENS][GENS][GENS];


/* dp[i][j]: How many ways are there of building the first i characters of the original string 
 * with j being the last character
 */ 
vector<vector<int>> dp;

void add(int& a, int b)
{
    a += b;
    if (a > MOD) {
        a -= MOD;
    }
}

int code(char c)
{
    if (c == 'A') {
        return 0;
    }
    if (c == 'T') {
        return 1;
    }
    if (c == 'G') {
        return 2;
    }
    if (c == 'C') {
        return 3;
    }

    return SPECIAL;
}

// Extend latest segment
void extend_segment(int gene)
{
    for (int prv_start = 0; prv_start < GENS; prv_start++) {
        for (int cur_start = 0; cur_start < GENS; cur_start++) {
            for (int end = 0; end < GENS; end++) {
                if (end != gene) {
                    add(cnt[prv_start][cur_start][gene], prv[prv_start][cur_start][end]); 
                }
            }
        }
    }
}

// Close latest segment and open new one
void close_segment(int gene)
{
    for (int prv_start = 0; prv_start < GENS; prv_start++) {
        for (int cur_start = 0; cur_start < GENS; cur_start++) {
            for (int end = 0; end < GENS; end++) {
                if (prv_start == FIRST || prv_start == end) {
                    add(cnt[cur_start][gene][gene], prv[prv_start][cur_start][end]);
                }
            }
        }
    }
}

void clear(void)
{
    for (int i = 0; i < GENS; i++) {
        for (int j = 0; j < GENS; j++) {
            for (int k = 0; k < GENS; k++) {
                cnt[i][j][k] = 0;
            }
        }
    }
}

int main(void)
{
    char c;

    while (scanf("%c", &c) != EOF && !isspace(c)) {
        genome.push_back(code(c));
        N++;
    }

    cnt[FIRST][FIRST][FIRST] = 1;

    for (int i = 0; i < N; i++) {
        // update_cnt with genome[i]:
        swap(cnt, prv);
        clear();

        for (int g = 0; g < GENS - 1; g++) {
            if (genome[i] == g || genome[i] == SPECIAL) {
                close_segment(g);
                if (i != 0) {
                    extend_segment(g);
                }
            }
        }
    }

    int ans = 0;
    for (int p_start = 0; p_start < GENS; p_start++) {
        for (int start = 0; start < GENS; start++) {
            for (int end = 0; end < GENS; end++) {
                if (p_start == FIRST || p_start == end) {
                    add(ans, cnt[p_start][start][end]);
                }
            }
        }
    }

    printf("%d\n", ans);
    
    return 0;
}