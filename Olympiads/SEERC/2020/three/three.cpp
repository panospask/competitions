#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

vector<int> s;
vector<int> t;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    s.resize(N + 1);
    t.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        a[i] %= 3;
    }

    s[N] = 0;
    t[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        s[i] = (a[i] + s[i + 1]) % 3;
        t[i] = (a[i] * a[i] + t[i + 1]) % 3;
    }

    long long ans = 0;

    vector<vector<int>> cnt(3, vector<int>(3, 0));
    for (int i = N; i >= 0; i--) {
        
        ans += cnt[s[i]][t[i]];

        int nxt = (t[i] + 2) % 3;
        ans += cnt[(s[i] + 1) % 3][nxt];
        ans += cnt[(s[i] + 2) % 3][nxt];
        cnt[s[i]][t[i]]++;
    }

    printf("%lld\n", ans);

    return 0;
}