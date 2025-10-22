#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e18;

int H, W, S;

int ceil(int x, int y) {
    return (x + y - 1) / y;
}

vector<pi> generate(int v) {
    int p = 1;
    int len = v;
    vector<pi> ans;

    ans.pb(mp(len, p));

    while (len > 1) {
        int last = (v - 1) / (len - 1);

        p = last + 1;
        len = ceil(v, p);
        ans.pb(mp(len, p));
    }

    return ans;
}

void solve(void) {
    scanf("%d %d %d", &H, &W, &S);

    auto v1 = generate(H);
    auto v2 = generate(W);

    ll ans = INF;
    
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}