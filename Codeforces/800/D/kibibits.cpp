#include <vector>
#include <stdio.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int DIGITS = 6;
const int exp[7] = {1, 10, 100, 1000, 10000, 100000, 1000000};

ll calc_pow(ll a, int b) {
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

int N;
vector<int> A;

// superset[i][v]: Total count of numbers that are supersets of v and differ only in the first i digits
vector<vector<ll>> superset;
// supersum[i][v]: Total sum of numbers that are supersets of v and differ only in the first i digits
vector<vector<ll>> supersum;

int digit(int num, int k) {
    if (k + 1 < DIGITS) {
        num %= exp[k + 1];
    }
    return num / exp[k];
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    superset.resize(DIGITS + 1, vector<ll>(exp[DIGITS], 0));
    supersum.resize(DIGITS + 1, vector<ll>(exp[DIGITS], 0));
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        superset[0][A[i]]++;
        supersum[0][A[i]] += A[i];
    }

    for (int d = 0; d < DIGITS; d++) {
        for (int num = exp[DIGITS] - 1; num >= 0; num--) {
            superset[d + 1][num] = superset[d][num];
            supersum[d + 1][num] = supersum[d][num];

            int cur = digit(num, d);
            if (cur + 1 < DIGITS) {
                superset[d + 1][num] += superset[d][num + exp[d]];
                supersum[d + 1][num] += supersum[d][num + exp[d]];
            }

            supersum[d + 1][num] %= MOD;
        }
    }

    ll ans = 0;
    for (int num = 0; num < exp[DIGITS]; num++) {
        ll total_length;
    }
}