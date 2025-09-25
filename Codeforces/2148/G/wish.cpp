#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N) {
            size *= 2;
        }

        tree.assign(2 * size, 0);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid) {
            add(i, v, 2 * x + 1, lx, mid);
        }
        else {
            add(i, v, 2 * x + 2, mid, rx);
        }

        tree[x] = min(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int calc(void) {
        return tree[0];
    }
};

int N;
vector<int> A;
vector<int> primes;

// prv[v] is the smallest prime number that divides v (or -1)
vector<int> prv;

// How many times does a specific prime appear in the gcd
vector<int> cnt;
// How many numbers in our array have the "bottleneck" in prime i (ie the fewest possible prime[i] in the representation)
SegTree st;
int increment = 0;

int gcd(int a, int b) {
    if (a < b) {
        swap(a, b);
    }

    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }

    return a;
}

void precalculate(int N) {
    primes.clear();

    prv.assign(N + 1, -1);
    for (int i = 2; i <= N; i++) {
        if (prv[i] == -1) {
            prv[i] = primes.size();
            primes.pb(i);
        }

        for (int j = 0; j < primes.size(); j++) {
            if ((long long )i * primes[j] <= N) {
                prv[i * primes[j]] = j;
            }

            if (j >= prv[i]) {
                break;
            }
        }
    }
}

// Make prime decomposition of v and insert the "bottlenecks" into the segment tree
vector<pi> decompose(int v) {
    vector<pi> ans;

    while (v > 1) {
        int p = prv[v];
        int c = 0;

        while (prv[v] == p) {
            c++;
            v /= primes[p];
        }

        ans.pb({p, c});
    }

    return ans;
}

void insert(vector<pi> l) {
    increment++;
    for (auto [p, c] : l) {
        if (c != cnt[p]) {
            st.add(p, -1);
        }
    }
}

void solve(void) {
    scanf("%d", &N);

    precalculate(N);

    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    // Make initial gcd something not A[0] (maybe 2A[0] or sth)
    int g = 2 * A[0];
    increment = 0;

    for (int i = 0; i < N; i++) {
        int n_g = gcd(g, A[i]);

        if (n_g != g) {
            // Change everything
            g = n_g;
            st.init(primes.size());
            increment = 0;
            cnt.assign(primes.size(), 0);

            for (auto [p, c] : decompose(g)) {
                cnt[p] = c;
            }

            for (int j = 0; j < i; j++) {
                insert(decompose(A[j]));
            }
        }

        insert(decompose(A[i]));

        printf("%d ", i - (st.calc() + increment) + 1);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}