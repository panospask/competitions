#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pi;

int N;
vector<int> a, b;

void solve(void)
{
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }

    stack<pi> s;
    ll time = 0;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        pi cur = {a[i], b[i]};
        while (!s.empty() && (s.top().second == cur.second || s.top().first <= cur.first)) {
            pi prv = s.top();
            s.pop();

            if (prv.second == cur.second) {
                cur.first += prv.first - time;
            }

            time = prv.first;
        }

        if (s.empty()) {
            ans = cur.first;
        }
        s.push(cur);

        printf("%lld ", ans);
    }

    printf("\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}