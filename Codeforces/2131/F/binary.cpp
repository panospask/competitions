#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N;
vector<int> a, b;

// Cost to make first i rows or columns 0 and 1 resp.
vector<vector<int>> rows;
vector<vector<int>> columns;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%1d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%1d", &b[i]);
    }

    rows.assign(N, vector<int>(2, 0));
    columns.assign(N, vector<int>(2, 0));

    for (int i = 0; i < N; i++) {
        for (int p = 0; p < 2; p++) {
            rows[i][p] = (a[i] != p);
            columns[i][p] = (b[i] != p);
            if (i > 0) {
                rows[i][p] += rows[i - 1][p];
                columns[i][p] += columns[i - 1][p];
            }
        }
    }

    ll base = 0;
    vector<int> extra;
    // Fow now always assume we make rows to 0
    for (int i = 0; i < N; i++) {
        base += rows[i][0];
        extra.pb(rows[i][1] - rows[i][0]);
    }
    sort(extra.begin(), extra.end());
    
    // pref[i] is if we take extra from 0 to (i-1) 
    vector<ll> pref(N + 1);
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + extra[i];
    }

    ll ans = 0;
    for (int c = 0; c < N; c++) {
        // Assume we make column 0
        ll v = columns[c][0];
        int swapcost = columns[c][1] - columns[c][0];

        // If current swapcost + extra[i] < 0, then it is good to swap
        int pos = lower_bound(extra.begin(), extra.end(), -swapcost) - extra.begin();

        ans += (base + v * N);
        // Perform the pos swaps
        ans += pref[pos] + (ll)swapcost * pos;
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}