#include <bits/stdc++.h>
#define POSITIVE_M(v) (v = ((v%MOD) + MOD) % MOD)

using namespace std;

typedef long long ll;
typedef __int128_t lll;

const ll MOD = (1ll << 61) - 1;
const int PRIME = 3;

int n, Q;
vector<int> a;
vector<ll> pos_v;
vector<ll> num_v;

// DSU variables
vector<ll> total_pos, total_num;
vector<int> rep;
vector<int> sz;
unordered_map<ll, int> diff_looking;

ll q4ans = 0;

int find(int a)
{
    if (rep[a] != a)
        rep[a] = find(rep[a]);

    return rep[a];
}

void remove_option(int a)
{
    a = find(a);


    ll diff = total_num[a] - total_pos[a];
    POSITIVE_M(diff);

    if (diff == 0)
        return;

    int v = diff_looking[diff];
    if (v == sz[a])
        diff_looking.erase(diff);
    else
        diff_looking[diff] -= sz[a];

    ll rev = -diff;
    POSITIVE_M(rev);

    if (diff_looking.find(rev) != diff_looking.end()) {
        int b = diff_looking[rev];

        q4ans -= (ll)b * sz[a];
    }
}

void add_option(int a)
{
    a = find(a);

    ll diff = total_num[a] - total_pos[a];
    POSITIVE_M(diff);
    if (diff == 0)
        return;

    diff_looking[diff] += sz[a];

    ll rev = -diff;
    POSITIVE_M(rev);

    if (diff_looking.find(rev) != diff_looking.end()) {
        int b = diff_looking[rev];

        q4ans += (ll)sz[a] * b;
    }
}

void init(void)
{
    rep.resize(n);
    sz.assign(n, 1);

    total_pos.resize(n);
    total_num.resize(n);

    for (int i = 0; i < n; i++) {
        rep[i] = i;
        total_pos[i] = pos_v[i];
        total_num[i] = num_v[a[i]];

        add_option(i);
    }
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    if (sz[b] > sz[a])
        swap(a, b);

    remove_option(a);
    remove_option(b);

    rep[b] = a;
    sz[a] += sz[b];

    total_num[a] += total_num[b];
    POSITIVE_M(total_num[a]);
    total_pos[a] += total_pos[b];
    POSITIVE_M(total_pos[a]);

    add_option(a);
}

void change_to(int a, int p_v, int n_v)
{
    a = find(a);

    remove_option(a);

    total_num[a] += num_v[n_v] - num_v[p_v];
    POSITIVE_M(total_num[a]);

    add_option(a);
}

ll bigger_rand(void)
{
    ll a = rand();
    ll b = rand();

    ll res = (a * RAND_MAX) + b;

    return res;
}

int main(void)
{
    scanf("%d %d", &n, &Q);

    num_v.assign(1e6 + 1, -1);
    pos_v.resize(n);
    a.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    srand(13);

    vector<int> s_a = a;
    sort(s_a.begin(), s_a.end());

    for (int i = 0; i < n; i++) {
        if (num_v[s_a[i]] == -1) {
            num_v[s_a[i]] = bigger_rand() % MOD;
            POSITIVE_M(num_v[s_a[i]]);
        }


        pos_v[i] = num_v[s_a[i]];
    }

    init();

    while (Q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int p1, p2;
            scanf("%d %d", &p1, &p2);
            p1--; p2--;

            change_to(p1, a[p1], a[p2]);
            change_to(p2, a[p2], a[p1]);

            swap(a[p1], a[p2]);
        }
        else if (op == 2) {
            int p1, p2;
            scanf("%d %d", &p1, &p2);
            p1--; p2--;

            unite(p1, p2);
        }
        else if (op == 3) {
            if (diff_looking.size())
                printf("NE\n");
            else
                printf("DA\n");
        }
        else {
            printf("%lld\n", (long long)q4ans);
        }
    }

    return 0;
}