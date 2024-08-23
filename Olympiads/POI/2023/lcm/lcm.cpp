#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const int MAXV = 1e6;
const int MAXPOW = 21;

struct SegTree {
    const ll DEFAULT = 1;

    struct Node {
        ll totalsum = 0;
        ll lcmsum = 0;

        ll op_lcm = 1;
        ll op_total = 0;
    };

    int size;
    int MOD;
    vector<Node> tree;

    inline void mutliply(Node& a, int v) {
        a.lcmsum = a.lcmsum * v % MOD;
        a.op_lcm = a.op_lcm * v % MOD;
    }

    void merge(Node& par, Node &k1, Node & k2) {
        par.lcmsum = (k1.lcmsum + k2.lcmsum) % MOD;
        par.totalsum = (k1.totalsum + k2.totalsum) % MOD;
        par.op_lcm = 1;
        par.op_total = 0;
    }

    void propagate(Node& par, Node& kid) {
        kid.totalsum = (kid.totalsum + kid.lcmsum * par.op_total) % MOD;
        kid.op_total = (kid.op_total + kid.op_lcm * par.op_total) % MOD;

        kid.op_lcm = kid.op_lcm * par.op_lcm % MOD;
        kid.lcmsum = kid.lcmsum * par.op_lcm % MOD;
    }
    void null_ops(Node& n) {
        n.op_lcm = 1;
        n.op_total = 0;
    }
    void propagate(int x) {
        propagate(tree[x], tree[2 * x + 1]);
        propagate(tree[x], tree[2 * x + 2]);
        null_ops(tree[x]);
    }

    void build(int N, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < N) {
                tree[x].lcmsum = 1;
                tree[x].op_lcm = 1;
            }

            return;
        }

        int mid = (lx + rx) / 2;
        build(N, 2 * x + 1, lx, mid);
        build(N, 2 * x + 2, mid, rx);

        merge(tree[x], tree[2 * x + 1], tree[2 * x + 2]);
    }

    void init(int N, int M) {
        size = 1;
        MOD = M;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, Node());
        build(N, 0, 0, size);
    }

    void mul(int l, int r, int v, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x].lcmsum = tree[x].lcmsum * v % MOD;
            tree[x].op_lcm = tree[x].op_lcm * v % MOD;
            return;
        }

        propagate(x);
    
        int mid = (lx + rx) / 2;
        mul(l, r, v, 2 * x + 1, lx, mid);
        mul(l, r, v, 2 * x + 2, mid, rx);

        merge(tree[x], tree[2 * x + 1], tree[2 * x + 2]);
    }
    void mul(int l, int r, int v) {
        mul(l, r, v, 0, 0, size);
    }

    void addlcm(int l, int r,int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return;
        }
        else if (l <= lx && rx <= r) {
            tree[x].totalsum = (tree[x].totalsum +  tree[x].lcmsum) % MOD;
            tree[x].op_total = (tree[x].op_total + tree[x].op_lcm) % MOD;
            return;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        addlcm(l, r, 2 * x + 1, lx, mid);
        addlcm(l, r, 2 * x + 2, mid, rx);

        merge(tree[x], tree[2 * x + 1], tree[2 * x + 2]);
    }
    void addlcm(int l, int r) {
        addlcm(l, r, 0, 0, size);
    }

    ll sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x].totalsum;
        }

        propagate(x);

        int mid = (lx + rx) / 2;
        ll c1 = sum(l, r, 2 * x + 1, lx, mid);
        ll c2 = sum(l, r, 2 * x + 2, mid, rx);

        return (c1 + c2) % MOD;        
    }
    ll sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

struct Query {
    int l, r, id;
};

int N, Q, M;
vector<int> A;
SegTree st;
vector<Query> queries;
vector<ll> ans;

// Variables related to primes
vector<int> primes;
vector<int> first;
vector<vector<pi>> decomposition;
vector<vector<int>> pwr;

void sieve(void)
{
    first.assign(MAXV + 1, -1);
    decomposition.resize(MAXV + 1);

    for (int i = 2; i <= MAXV; i++) {
        if (first[i] == -1) {
            primes.pb(i);
            first[i] = primes.size() - 1;
        }

        for (int j = 0; primes[j] * i <= MAXV; j++) {
            first[i * primes[j]] = j;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }

    for (int i = 2; i <= MAXV; i++) {
        int cur = i;
        while (cur > 1) {
            int f = first[cur];
            int p = primes[f];
            int c = 0;
            while (cur % p == 0) {
                c++;
                cur /= p;
            }

            decomposition[i].pb(mp(f, c));
        }
    }
}

void prime_powers(void)
{
    pwr.resize(primes.size(), vector<int>(MAXPOW, 1));

    for (int j = 0; j < primes.size(); j++) {
        pwr[j][0] = 1;
        for (int c = 1; c < MAXPOW; c++) {
            pwr[j][c] = (ll)pwr[j][c - 1] * primes[j] % M;
        }
    }
}

bool rightsort(const Query& a, const Query& b)
{
    return a.r < b.r;
}

int main(void)
{
    scanf("%d %d %d", &N, &Q, &M);

    A.resize(N);
    st.init(N, M);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    sieve();
    prime_powers();

    queries.resize(Q);
    ans.resize(Q);
    for (int q = 0; q < queries.size(); q++) {
        scanf("%d %d", &queries[q].l, &queries[q].r);
        queries[q].l--;
        queries[q].r--;

        queries[q].id = q;
    }
    sort(queries.begin(), queries.end(), rightsort);

    st.init(N, M);

    vector<stack<pi>> times(primes.size());
    for (int i = 0; i < primes.size(); i++) {
        times[i].push(mp(-1, MAXPOW));
    }

    int pt = 0;
    for (int r = 0; r < N; r++) {
        for (auto [i, c] : decomposition[A[r]]) {
            int prv = r;
            int diff = c;

            while (times[i].top().second <= c) {
                st.mul(times[i].top().first + 1, prv + 1, pwr[i][diff]);

                diff = c - times[i].top().second;
                prv = times[i].top().first;
                times[i].pop();
            }
            st.mul(times[i].top().first + 1, prv + 1, pwr[i][diff]);

            times[i].push(mp(r, c));
        }

        st.addlcm(0, r + 1);

        while (pt < queries.size() && queries[pt].r == r) {
            ans[queries[pt].id] = st.sum(queries[pt].l, r + 1);
            pt++;
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}