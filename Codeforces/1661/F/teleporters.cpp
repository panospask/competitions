#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
ll M;
vector<ll> A;

ll cost(ll d, int cur, int lamda) {
    cur++;

    int sz = d / cur;
    int plus1 = d - sz * cur;

    return sz * sz *(cur - plus1) + (sz + 1) * (sz + 1) * plus1 + (cur - 1) * lamda;
}

ll opt(ll d, int lamda) {
    ll l = 0;
    ll r = d;

    while (l + 2 < r) {
        ll m1 = (l + l + r) / 3;
        ll m2 = (l + r + r) / 3;

        ll c1 = cost(d, m1, lamda);
        ll c2 = cost(d, m2, lamda);

        if (c1 < c2) {
            r = m2;
        }
        else {
            l = m1;
        }
    }

    ll c1 = cost(d, l, lamda);
    ll c2 = cost(d, l + 1, lamda);
    ll c3 = cost(d, l + 2, lamda);
    
    if (c1 < c2 && c1 < c3) {
        return l;
    }
    else if (c2 < c3) {
        return l + 1;
    }
    else {
        return l + 2;
    }
}

pair<int, ll> test(ll lambda) {
    ll ans = 0;
    int cnt = 0;

    ll prv = 0;
    for (int i = 0; i < N; i++) {
        int x = opt(A[i] - prv, lambda);
        cnt += x;
        ans += lambda * x;
    }

    return {cnt, ans};
}

int main(void) {
    ;
}