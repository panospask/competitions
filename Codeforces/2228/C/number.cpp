#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18;

ll A, N;
vector<int> d;
vector<ll> tenpow;
vector<int> analyze;

bool revcmp(int a, int b) {
    return a > b;
}

ll bigger(int pos, bool completed, bool smaller) {
    if (pos == -1) {
        return 0;
    }

    if (completed) {
        return d[0] * tenpow[pos] + bigger(pos - 1, completed, smaller);
    }

    int cur;
    if (smaller) {
        cur = lower_bound(d.begin(), d.end(), analyze[pos], revcmp) - d.begin();
    }
    else {
        cur = lower_bound(d.begin(), d.end(), analyze[pos]) - d.begin();
    }
    if (cur == d.size()) {
        // We failed, oops
        return -1;
    }
    else {
        // :(
        bool completed = !(d[cur] == analyze[pos]);
        ll res = bigger(pos - 1, completed, smaller);
        if (res == -1) {
            if (cur != d.size() - 1) {
                cur++;
                res = bigger(pos - 1, true, smaller);
            }
            else {
                return -1;
            }
        }

        return d[cur] * tenpow[pos] + res;
    }
}

void solve(void) {
    scanf("%lld %lld", &A, &N);

    d.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &d[i]);
    }
    ll Abackup = A;

    analyze.clear();
    tenpow.clear();
    tenpow.push_back(1);
    while (A) {
        analyze.push_back(A % 10);
        A /= 10;
        tenpow.push_back(tenpow.back() * 10);
    }
    int nonzero = d[0];
    if (d[0] == 0) {
        if (d.size() >= 2) {
            nonzero = d[1];
        }
        else {
            nonzero = -1;
            printf("%lld\n", Abackup);
            return;
        }
    }

    if (Abackup == 0) {
        printf("%d\n", d[0]);
        return;
    }

    ll x = bigger(analyze.size() - 1, false, false);
    reverse(d.begin(), d.end());
    ll y = bigger(analyze.size() - 1, false, true);

    if (y == -1) {
        // Just zero the first position
        y = bigger(analyze.size() - 2, true, true);
    }
    reverse(d.begin(), d.end());
    if (x == -1) {
        // use something more
        x = tenpow[analyze.size()] * nonzero + bigger(analyze.size() - 1, true, false);
    }
    ll ans = abs(Abackup - y);
    if (y == 0 && d[0] != 0) {
        ans = abs(Abackup - x);
    }
    ans = min(ans, abs(Abackup - x));

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}