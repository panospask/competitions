#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXV = 1e6;
int block_size;

struct query{
    int l, r;
    int id;
    void readquery(int i) {
        id = i;
        cin >> l >> r;
        l--;
    }

    bool operator < (query& b) {
        if (this->l / block_size == b.l / block_size)
            return this->r < b.r;
        return (this->l / block_size < b.l / block_size);
    }
};
typedef struct query Query;

int n, t;
vector<Query> queries;
vector<int> a;
vector<int> freq;
ll cur_power;
vector<ll> ans;

ll calc_pow(int l, int r)
{
    ll curp = 0;
    unordered_map<int, int> f;
    for (int i = l; i < r; i++)
        f[a[i]]++;

    for (auto p : f) {
        curp += p.first * (ll)p.second * p.second;
    }

    return curp;
}

void reset(void)
{
    for (int i = 0; i < n; i++)
        freq[a[i]] = 0;
    cur_power = 0;
}

int main(void)
{
    ios::sync_with_stdio(false);

    cin >> n >> t;
    a.resize(n);
    ans.resize(t);
    freq.assign(MAXV, 0);
    queries.resize(t);
    block_size = floor(sqrt(n));

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < t; i++) {
        queries[i].readquery(i);
    }
    sort(queries.begin(), queries.end());

    int l = block_size, r = block_size;
    int cur_block = 0;
    for (auto& q : queries) {
        if (q.l / block_size == q.r / block_size) {
            // Instant calc
            ans[q.id] = calc_pow(q.l, q.r);
            continue;
        }

        if (q.l / block_size != cur_block) {
            reset();
            cur_block = q.l / block_size;
            r = l = block_size * (cur_block + 1);
        }

        // Move right pointer to target (will always move right)
        while (r < q.r) {
            int cur_f = freq[a[r]];
            ll add = (ll)(2 * cur_f + 1) * a[r];
            cur_power += add;
            freq[a[r++]]++;
        }

        // Move left pointer to target
        if (q.l < l) {
            // We move left and keep adding
            while (l > q.l) {
                l--;
                int cur_f = freq[a[l]];
                ll add = (ll)(2 * cur_f + 1) * a[l];
                cur_power += add;
                freq[a[l]]++;
            }
        }
        else {
            // Move right --> remove
            while (l < q.l) {
                int cur_f = freq[a[l]];
                ll add = (ll)(-2 * cur_f + 1) * a[l];
                cur_power += add;
                freq[a[l++]]--;
            }
        }

        ans[q.id] = cur_power;
    }

    for (int i = 0; i < t; i++)
        printf("%lld\n", ans[i]);

    return 0;
}