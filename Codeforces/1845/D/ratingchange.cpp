#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n;
vector<int> a;
ll curheight;
stack<ll> local_max;

ll ans_save = 0;
ll ans_v = 0;

void solve(void)
{
    scanf("%d", &n);
    a.resize(n);

    ans_save = ans_v = 0;

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    ll latest_max = 0;
    ll latest_min = 0;
    ll cur_h = 0;
    for (int i = 0; i < n; i++) {
        cur_h += a[i];
        if (latest_min > cur_h)
            latest_min = cur_h;
        else if (latest_max < cur_h) {
            if (latest_max - latest_min > ans_v) {
                ans_v = latest_max - latest_min;
                ans_save = latest_max;
            }
            latest_max = cur_h;
            latest_min = cur_h;
        }
    }
    if (latest_max - latest_min > ans_v)
        ans_save = latest_max;

    printf("%lld\n", ans_save);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}