#include <bits/stdc++.h>
#define CHECK_BIT(var, pos) (((var) & (1LL << (pos))) != 0)

using namespace std;

typedef long long ll;
typedef pair<int, ll> pi;

const int BITS = 31;
const ll INF = 1e18;

int N, Q;
vector<int> A;
vector<int> suff;
vector<ll> ans;

ll calculate(int b) {
    vector<bool> banned(N, false);
    ll res = 0;
    for (int j = b; j >= 0; j--) {
        bool found = false;
        int mod = (1 << j);
        int mx = 0;
        int mi = -1;
        for (int i = 0; i < N && !found; i++) {
            if (banned[i]) {
                continue;
            }

            if (CHECK_BIT(A[i], j)) {
                found = true;
            }
            else if (mx < A[i] % mod) {
                mx = A[i] % mod;
                mi = i;
            }
        }

        if (!found) {
            res += mod - mx;
            if (mi != -1) {
                banned[mi] = true;
            }
        }
    }

    return res;
}

void solve(void) {
    scanf("%d %d", &N, &Q);

    A.resize(N);
    suff.assign(BITS + 1, 0);
    ans.assign(BITS + 1, INF);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
        for (int b = 0; b < BITS; b++) {
            if (CHECK_BIT(A[i], b)) {
                suff[b] = 1;
            }
        }
    }
    
    for (int i = BITS - 1; i >= 0; i--) {
        suff[i] += suff[i + 1];
    }

    for (int b = 0; b < BITS; b++) {
        // Fix everything including b and whatever you have above
        ans[suff[b + 1] + b + 1] = min(ans[suff[b + 1] + b + 1], calculate(b));
    }

    ans[suff[0]] = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        ans[b] = min(ans[b], ans[b + 1]);
    }

    while (Q--) {
        int i = 0;

        int v;
        scanf("%d", &v);

        while (i + 1 <= BITS && ans[i + 1] <= v) {
            i++;
        }
        printf("%d\n", i);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}