#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> s;
string c;

void solve(void)
{
    cin >> c;
    N = c.size();
    s.resize(c.size());

    for (int i = 0; i < N; i++) {
        s[i] = c[i] - '0';
    }

    int curlen = 0;
    ll tot = 0;
    for (int i = 0; i < N; i++) {
        if (s[i] == 1) {
            curlen++;
        }
        else if (curlen) {
            tot += curlen + 1;
        }
    }

    printf("%lld\n", tot);
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