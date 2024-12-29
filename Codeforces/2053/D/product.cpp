#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MOD = 998244353;

int N, Q;
ll ans;

vector<pi> initial[2];

vector<int> v[2];
map<int, int> finishes[2];

// Where is the element with index i
vector<int> pos[2];

// Index of the element at position p
vector<int> id[2];

ll calc_pow(ll a, ll b)
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

void update(vector<int>& a, vector<int>& b, map<int, int>& f, vector<int>& pos, vector<int>& id, int i)
{
    int j = f[a[i]];

    // Swap elements at positions i and j
    swap(id[i], id[j]);
    pos[id[i]] = i;
    pos[id[j]] = j;


    // Increment a[j]
    int counter_element = b[j];
    a[j]++;
    if (a[j] <= b[j]) {
        ans = ans * calc_pow(a[j] - 1, MOD - 2) % MOD * a[j] % MOD;
    }

    // Update f
    if (j > 0 && a[j - 1] == a[j] - 1) {
        f[a[j] - 1] = j - 1;
    }
    else {
        f.erase(a[j] - 1);
    }

    f[a[j]] = max(f[a[j]], j);
}

void solve(void)
{
    scanf("%d %d", &N, &Q);

    ans = 0;

    for (int c = 0; c < 2; c++) {
        v[c].resize(N);
        initial[c].resize(N);
        finishes[c].clear();
        pos[c].resize(N);
        id[c].resize(N);

        for (int i = 0; i < N; i++) {
            scanf("%d", &initial[c][i].first);
            initial[c][i].second = i;
        }

        sort(initial[c].begin(), initial[c].end());
        for (int i = 0; i < N; i++) {
            v[c][i] = initial[c][i].first;
            id[c][i] = initial[c][i].second;
            pos[c][id[c][i]] = i;
        }

        sort(v[c].begin(), v[c].end());
        for (int i = 0; i < N; i++) {
            finishes[c][v[c][i]] = i;
        }
    }

    ans = 1;
    for (int i = 0; i < N; i++) {
        ans = ans * min(v[0][i], v[1][i]);
        ans %= MOD;
    }

    printf("%lld ", ans);
    while (Q--) {
        int op, x;
        scanf("%d %d", &op, &x);
        op--;
        x--;

        update(v[op], v[!op], finishes[op], pos[op], id[op], pos[op][x]);

        printf("%lld ", ans);
    }
    printf("\n");

    return;
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