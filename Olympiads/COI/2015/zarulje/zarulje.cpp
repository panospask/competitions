#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 1e9 + 7;
const int MAXV = 2e5;

struct State {
    int v;
    int cnt;
};

int N, K;
vector<int> a;
stack<State> s;
vector<ll> contribute;
vector<ll> fact;
vector<ll> inv;
vector<int> bef;
vector<vector<pi>> changes_before;
vector<int> aft;
vector<vector<pi>> changes_after;
vector<stack<int>> queries;
vector<int> ans;

ll cur = 1;

ll calc_power(ll a, int b)
{
    ll c = 1;
    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}

ll find_inverse(ll a) 
{
    return calc_power(a, MOD - 2);
}

void initialize_factorials(void)
{
    fact.resize(N + 1);
    inv.resize(N + 1);

    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    inv[N] = find_inverse(fact[N]);
    for (int i = N - 1; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % MOD;
    }
}

ll choose(int a, int b)
{
    ll nom = fact[a];
    ll den = inv[b] * inv[a - b] % MOD;

    return nom * den % MOD;
}

void clearstack(void)
{
    while (!s.empty()) {
        s.pop();
    }
}

void remove_val(int v)
{
    cur = cur * find_inverse(contribute[v]) % MOD;
    contribute[v] = 1;
}

void add_val(int v)
{
    contribute[v] = choose(bef[v] + aft[v], bef[v]);
    cur = cur * contribute[v] % MOD;
}

int main(void)
{
    scanf("%d %d", &N, &K);

    initialize_factorials();

    contribute.assign(MAXV + 1, 1);
    a.resize(N);
    queries.resize(N);
    ans.resize(K);
    changes_before.resize(MAXV + 1);
    changes_after.resize(MAXV + 1);
    bef.assign(MAXV + 1, 0);
    aft.assign(MAXV + 1, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < K; i++) {
        int p;
        scanf("%d", &p);
        queries[p - 1].push(i);
    }

    for (int i = 0; i < N; i++) {
        while (!s.empty() && s.top().v > a[i]) {
            changes_before[i].pb(mp(s.top().v, -s.top().cnt));
            s.pop();
        }

        if (!s.empty() && s.top().v == a[i]) {
            s.top().cnt++;
        }
        else {
            s.push({a[i], 1});
        }

        changes_before[i].pb(mp(a[i], 1));
    }

    clearstack();

    for (int i = N - 1; i >= 0; i--) {
        while (!s.empty() && s.top().v > a[i]) {
            changes_after[i].pb(mp(s.top().v, s.top().cnt));
            s.pop();
        }

        if (!s.empty() && s.top().v == a[i]) {
            s.top().cnt++;
        }
        else {
            s.push({a[i], 1});
        }

        changes_after[i].pb(mp(a[i], -1));
    }
    while (!s.empty()) {
        aft[s.top().v] = s.top().cnt;
        s.pop();
    }

    cur = 1;
    for (int i = 0; i < N; i++) {
        for (auto [v, c] : changes_after[i]) {
            remove_val(v);
            aft[v] += c;
            add_val(v);
        }

        while (!queries[i].empty()) {
            ans[queries[i].top()] = cur;
            queries[i].pop();
        }

        for (auto [v, c] : changes_before[i]) {
            remove_val(v);
            bef[v] += c;
            add_val(v);
        }
    }

    for (int i = 0; i < K; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}