#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
ll K;
vector<char> banned;

// Actually good digits
vector<char> digits;

void solve(void) {
    scanf("%d %lld %d", &N, &K, &M);

    banned.resize(M);
    for (int i = 0; i < M; i++) {
        scanf(" %c", &banned[i]);

    }

    digits.clear();
    for (int i = 0; i < N; i++) {
        char c;
        if (i < 10) {
            c = '0' + i;
        }
        else {
            c = 'A' + i - 10;
        }

        bool good = true;
        for (int j = 0; j < M; j++) {
            good = good && banned[j] != c;
        }
        if (good) {
            digits.push_back(c);
        }
    }

    vector<__uint128_t> x;
    x.push_back(1);
    while (x.back() <= K) {
        x.push_back(x.back() * digits.size());
    }
    
    vector<char> ans;
    ll rem = K;
    for (int i = x.size() - 2; i >= 0; i--) {
        int cur = rem / x[i];
        rem = rem % x[i];
        ans.push_back(digits[cur]);
    }

    for (auto c : ans) {
        printf("%c", c);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}