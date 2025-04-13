#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

typedef int ll;

const ll INF = 1e9;

const int MAXN = 19;
const int MAXM = 50;
const int MAXV = (1 << MAXN);

int subtask;

int N, M;

// dp[mask]: Minimum cost for assigning the largest cnt(mask) values to the letters indicated by mask
int dp[MAXV];

int first[MAXM][MAXV];

int total_occurences[MAXN];

vector<int> schedules[MAXM];

int main(void) {
    scanf("%d", &subtask);
    scanf("%d %d", &N, &M);

    // Init
    for (int j = 0; j < M; j++) {
        for (int mask = 0; mask < (1 << N); mask++) {
            dp[mask] = INF;
            first[j][mask] = INF;
        }   
    }

    for (int j = 0; j < M; j++) {
        string s;
        cin >> s;

        schedules[j].resize(s.size());
        for (int i = 0; i < s.size(); i++) {
            schedules[j][i] = s[i] - 'A';
            total_occurences[schedules[j][i]]++;
            first[j][1 << schedules[j][i]] = min(first[j][1 << schedules[j][i]], i);
        }
    }

    // Precalculate first
    for (int j = 0; j < M; j++) {
        for (int mask = 0; mask < 1 << N; mask++) {
            for (int i = 0; i < N; i++) {
                if (CHECK_BIT(mask, i)) {
                    continue;
                }

                first[j][mask + (1 << i)] = min(first[j][mask], first[j][1 << i]);
            }
        }
    }

    dp[0] = 0;
    for (int mask = 0; mask < (1 << N); mask++) {
        int count = __builtin_popcount(mask);
        // The current value we will add
        int value = N - count - 1;

        for (int i = 0; i < N; i++) {
            if (CHECK_BIT(mask, i)) {
                continue;
            } 

            ll additional = -(ll)total_occurences[i] * value;
            for (int j = 0; j < M; j++) {
                int pos = first[j][1 << i];
                int others = first[j][mask];
                others = min(others, (int)schedules[j].size());

                if (pos < others) {
                    additional += (others - pos) * value;
                    if (pos != 0) {
                        additional += value;
                    }
                    if (others != schedules[j].size()) {
                        additional -= value;
                    }
                }
            }

            dp[mask + (1 << i)] = min(dp[mask + (1 << i)], dp[mask] + additional);
        }
    }

    printf("%d\n", dp[(1 << N) - 1]);

    return 0;
}