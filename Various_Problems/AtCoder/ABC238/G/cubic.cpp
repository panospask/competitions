#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXV = 1e6;

typedef long long ll;

ll calc_pow(ll a, int b, int m)
{
    ll c = 1;
    while (b)
    {
        if (b % 2)
        {
            c = c * a % m;
        }

        a = a * a % m;
        b /= 2;
    }

    return c;
}

struct HashTable
{
    int MOD;
    vector<ll> h;
    map<int, int> prv;

    void initialize(int m)
    {
        MOD = m;
        h.assign(1, 0);
    }

    // Returns size of current hash
    int increment(map<int, int> &cnt) {
        ll res = h.back();
        for (auto [v, c] : cnt) {
            res -= calc_pow(3, v, MOD) * prv[v] % MOD;
            prv[v] = (prv[v] + c) % 3;
            res += calc_pow(3, v, MOD) * prv[v] % MOD;

        }
        res = (res % MOD + MOD) % MOD;

        h.pb(res);

        return h.size();
    }

    bool same(int l, int r) {
        ll diff = h[r] - h[l];

        diff = (diff % MOD + MOD) % MOD;
        return diff == 0;
    }
};

int N, Q;
vector<int> A;
vector<map<int, int>> cnt;
vector<map<int, int>> pref;

// Index of smallest prime that divides i
vector<int> last;

vector<int> primes;

// If it doesn't pass, just add more hashtables
HashTable h1;

void calculate_primes(void)
{
    last.assign(MAXV + 1, -1);

    for (int i = 2; i <= MAXV; i++)
    {
        if (last[i] == -1)
        {
            last[i] = primes.size();
            primes.pb(i);
        }

        for (int j = 0; j < primes.size() && primes[j] * i <= MAXV; j++)
        {
            last[primes[j] * i] = j;

            if (i % primes[j] == 0)
            {
                break;
            }
        }
    }
}

void decompose(int v, map<int, int> &c)
{
    while (v > 1)
    {
        c[last[v]]++;
        v /= primes[last[v]];
    }
}

int main(void)
{
    calculate_primes();

    scanf("%d %d", &N, &Q);

    A.resize(N);
    cnt.assign(N, map<int, int>());
    h1.initialize(1e9 + 7);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);

        decompose(A[i], cnt[i]);
        h1.increment(cnt[i]);
    }

    while (Q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;

        bool valid = h1.same(l, r + 1);

        if (valid)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}