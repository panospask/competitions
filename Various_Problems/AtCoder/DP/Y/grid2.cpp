#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = (int)1e9 + 7;

int H, W, N;
vector<pi> points;
vector<int> bef;
vector<ll> ans;

vector<ll> fact;
vector<ll> inv;

ll calc_inv(ll a)
{
    ll c = 1;
    int b = MOD - 2;

    while (b) {
        if (b % 2)
            c = c * a %  MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

void precalculate_fact(void)
{
    fact.resize(H + W + 1);
    inv.resize(H + W + 1);

    fact[0] = 1;
    for (int i = 1; i <= H + W; i++)
        fact[i] = fact[i - 1] * i % MOD;

    inv[H + W] = calc_inv(fact[H + W]);
    for (int i = H + W - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;
}

ll choose(int a, int b)
{
    if (a < b || b < 0)
        return 0;

    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

bool before(pi a, pi b)
{
    return a.first <= b.first && a.second <= b.second;
}
bool before(int a, int b)
{
    return before(points[a], points[b]);
}

int main(void)
{
    scanf("%d %d %d", &H, &W, &N);

    precalculate_fact();

    points.resize(N + 1);
    ans.resize(N + 1);
    bef.resize(N + 1);
    for (int i = 0; i < N; i++)
        scanf("%d %d", &points[i].first, &points[i].second);
    points[N] = {H, W};
    for (int i = 0; i <= N; i++) {
        points[i].first--;
        points[i].second--;
    }

    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++) {
            if (i != j && before(i, j))
                bef[j]++;
        }

    queue<int> q;
    for (int i = 0; i <= N; i++)
        if (!bef[i])
            q.push(i);

    while (!q.empty()) {
        int cur = q.front(); q.pop();

        ans[cur] += choose(points[cur].first + points[cur].second, points[cur].first);
        ans[cur] = (ans[cur] % MOD + MOD) % MOD;

        for (int j = 0; j <= N; j++) {
            if (cur == j)
                continue;

            if (before(cur, j)) {
                int n = points[j].first - points[cur].first + points[j].second - points[cur].second;
                int k = points[j].first - points[cur].first;

                ans[j] -= ans[cur] * choose(n, k) % MOD;

                bef[j]--;
                if (!bef[j])
                    q.push(j);
            }
        }
    }

    printf("%lld\n", ans[N]);

    return 0;
}