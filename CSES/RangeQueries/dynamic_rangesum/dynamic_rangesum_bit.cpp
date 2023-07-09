#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<ll> tree;

    void add(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }

    ll sum(int i) {
        ll res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    // Returns sum in [l, r)
    ll sum(int l, int r) {
        return sum(r - 1) - sum(l - 1);
    }

    void init(int n, vector<int> a) {
        size = n;
        tree.resize(size, 0);
        for (int i = 0; i < size; i++)
            add(i, a[i]);
    }
};

int n, q;
vector<int> a;

BITree b;

int main(void)
{
    scanf("%d %d", &n, &q);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    b.init(n, a);
    while (q--) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int k, v;
            scanf("%d %d", &k, &v);
            k--;

            b.add(k, v - a[k]);
            a[k] = v;
        }
        else {
            int l, r;
            scanf("%d %d", &l, &r);
            l--;

            printf("%lld\n", b.sum(l, r));
        }
    }

    return 0;
}