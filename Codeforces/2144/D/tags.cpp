#include <bits/stdc++.h>
#define pb push_back
#define ceil(v, x) (((v) + (x) - 1) / (x))

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MAXV = 2e5;
const ll INF = 1e18;

int N, Y;
vector<int> C;

vector<stack<pi>> change;

int find_next(int v, int cur) {
    // We find the smallest number x that reduces v
    int target = cur - 1;
    int x = ceil(v, target);

    return x;
}

void solve(void) {
    scanf("%d %d", &N, &Y);

    C.resize(N);
    change.assign(MAXV + 1, stack<pi>());

    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    ll ans = -INF;
    // Set initial profit and tags
    ll p = 0;
    for (int i = 0; i < N; i++) {
        p += C[i];
    }
    vector<int> t(MAXV + 1);
    vector<int> initial(MAXV + 1);
    vector<int> cnt(MAXV + 1);
    for (int i = 0; i < N; i++) {
        t[C[i]]++;
        cnt[C[i]]++;
    }
    for (int i = 0; i <= MAXV; i++) {
        if (cnt[i] > 0) {
            if (i > 1) {
                change[find_next(i, i)].push({i, cnt[i]});
            }
        }
    }

    initial = t;

    for (int x = 2; x <= MAXV; x++) {
        // We start the process
        
        while (!change[x].empty()) {
            int c, v;
            tie(v, c) = change[x].top();
            change[x].pop();

            int prv = ceil(v, x - 1);
            int cur = ceil(v, x);

            p += (cur - prv) * (ll)c;
            
            t[cur] += c;
            if (t[cur] > initial[cur]) {
                p -= (ll)min(t[cur] - initial[cur], c) * Y;
            }
            if (t[prv] > initial[prv]) {
                p += (ll)min(t[prv] - initial[prv], c) * Y;
            }
            t[prv] -= c;

            if (x != v) {
                change[find_next(v, cur)].push({v, c});
            }
        }

        ans = max(ans, p);
    }

    printf("%lld\n", ans);

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}