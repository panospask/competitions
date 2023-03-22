#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000
#define MOD 1000000007

using namespace std;

typedef pair<int, int> ii;
typedef long long int ll;

ii events[2 * MAXN + 2];
bool isactive[MAXN + 2];
int n;
ll two_pow[MAXN + 2];

void calc_two_pow(int i)
{
    two_pow[0] = 1;
    for (int j = 1; j <= i; j++) {
        two_pow[j] = 2 * two_pow[j-1] % MOD;
    }
}

int main(void)
{
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);

    scanf("%d", &n);
    int l, r;
    for (int i = 0; i <n ; i++) {
        scanf("%d %d", &l, &r);

        events[2 * i] = mp(l, i);
        events[2 * i + 1] = mp(r, n + i);
    }
    calc_two_pow(n);
    sort(events, events + 2 * n);

    ll ans = 0;
    int cur_active = 0;
    for (int i = 0; i < 2 * n; i++) {
        ii cur = events[i];
        if (cur.second >= n) {
            cur.second -= n;
            isactive[cur.second] = false;
            cur_active--;
        }
        else {
            // The subsets involving the current segment: 2^(n-1)
            // The subsets also not involving the currently active segments
            // => involving only n-open-1 segments
            // => 2^(n-open-1)
            int cur_rm = cur_active + 1;

            ans = (ans + two_pow[n - cur_rm]) % MOD;

            cur_active++;
            isactive[cur.second] = true;
        }
    }

    printf("%lld\n", ans);
    return 0;
}