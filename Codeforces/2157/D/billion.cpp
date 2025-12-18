#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, L, R;
vector<int> A;
ll lv = 0, rv = 0;

// small is true if we predict A[i] <= p
void insert(int i, bool small, int m) {
    int v = A[i];

    if (small) {
        lv += (L - A[i]) * m;
        rv += (R - A[i]) * m;
    }
    else {
        lv += (A[i] - L) * m;
        rv += (A[i] - R) * m;
    }
}

void solve(void) {
    scanf("%d %d %d", &N, &L, &R);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    sort(A.begin(), A.end());

    ll ans = 0;
    lv = rv = 0;

    int p1 = 0;
    int p2 = N - 1;

    while (p1 <= p2) {
        insert(p1, true, 1);
        ll a1 = min(lv, rv);
        insert(p1, true, -1);
        
        insert(p2, false, 1);
        ll a2 = min(lv, rv);
        insert(p2, false, -1);

        if (a1 > a2) {
            ans = max(ans, a1);
            insert(p1, true, 1);
            p1++;
        }
        else {
            ans = max(ans, a2);
            insert(p2, false, 1);
            p2--;
        }
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}