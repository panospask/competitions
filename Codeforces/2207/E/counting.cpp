#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;

int N;
vector<int> A;

void solve(void) {
    cin >> N;

    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    A.insert(A.begin(), N);

    ll ans = 1;
    // Banned values

    // The MEX (ie A[N]) is certainly removed
    for (int i = N; i > 0; i--) {
        int cur = A[i];
        int prv = A[i - 1];

        if (cur > prv) {
            // Impossible
            printf("0\n");
            return;
        }
        // How many gaps does A[i - 1] have
        int gaps = N - i + 1;
        if (cur == prv) {
            // In i - 1 there was an extra gap, which is now patched by b[i]
            // We have to patch this gap
            // Because we're going backwards, just create a gap in [cur - 1, 0]
            // However (gaps - 1) empty slots are alread created and we account for them
            ans = ans * (cur - (gaps - 1)) % MOD;
        }
        else {
            // No gap is patched
            // Any other value is fair game
            ans = ans * (N + 1 - gaps) % MOD;
        }
    }

    cout << ans << endl;
}

int main(void) {
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}