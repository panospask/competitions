#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))

using namespace std;

const int LETTERS = 24;

int N;
vector<int> words;
vector<int> dp;

int main(void) {
    scanf("%d", &N);

    words.resize(1 << LETTERS, 0);
    for (int i = 0; i < N; i++) {
        string s;
        vector<int> v(3);
        cin >> s;
        for (int j = 0; j < 3; j++) {
            v[j] = s[j] - 'a';
        }

        words[(1 << v[1]) | (1 << v[2]) | (1 << v[0])]++;
    }

    dp.resize(1 << LETTERS, 0);
    for (int mask = 0; mask < dp.size(); mask++) {
        dp[mask] = words[mask];
    }

    for (int i = 0; i < LETTERS; i++) {
        for (int mask = 0; mask < (1 << LETTERS); mask++) {
            if (CHECK_BIT(mask, i)) {
                dp[mask] += dp[mask - (1 << i)];
            }
        }
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << LETTERS); mask++) {
        int res = N - dp[(1 << LETTERS) - 1 - mask];
        ans = ans ^ (res * res);
    }
    printf("%d\n", ans);

    return 0;
}