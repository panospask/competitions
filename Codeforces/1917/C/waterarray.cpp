#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K, D;
vector<ll> period;
vector<int> b;
vector<int> a;

int ans = 0;
int opt = 0;
int day;

bool change_day(void)
{
    for (int i = 0; i < b[(day-1) % K]; i++) {
        a[i]++;
        if (a[i] == i + 2) {
            opt--;
        }
        else if (a[i] == i + 1) {
            opt++;
        }
    }

    day++;
    return true;
}

void solve(void)
{
    scanf("%d %d %d", &N, &K, &D);
    period.assign(N, 0);
    b.resize(K);
    a.resize(N);

    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    for (int i = 0; i < K; i++) {
        scanf("%d", &b[i]);
    }

    opt = 0;
    day = 1;
    ans = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == i + 1)
            opt++;
    }

    while (day <= D && day < 2 * N + 4) {
        ans = max(ans, opt + (D - day) / 2);
        change_day();
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}