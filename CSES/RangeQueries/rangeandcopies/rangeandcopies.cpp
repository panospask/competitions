#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node {
    ll val;
    Node* l, *r;

    Node(int v) : val(v), l(nullptr), r(nullptr) {};
    Node(Node* a, Node* b) : val(a->val + b->val), l(a), r(b) {};
    Node(Node* cp) : val(cp->val), l(cp->l), r(cp->r) {};
};

Node* build(vector<int>& a, int lx, int rx)
{
    if (lx == rx - 1)
        return new Node(a[lx]);

    int mid = (lx + rx) / 2;
    return new Node(build(a, lx, mid), build(a, mid, rx));
}

Node* update(Node* x, int i, int v, int lx, int rx)
{
    if (lx == rx - 1)
        return new Node(v);

    assert(lx < rx);

    int mid = (lx + rx) / 2;
    if (i < mid)
        return new Node(update(x->l, i, v, lx, mid), x->r);
    else
        return new Node(x->l, update(x->r, i, v, mid, rx));
}

ll query(int l, int r, Node* x, int lx, int rx)
{
    if (l >= rx || lx >= r)
        return 0;
    else if (l <= lx && rx <= r)
        return x->val;

    int mid = (lx + rx) / 2;
    ll s1 = query(l, r, x->l, lx, mid);
    ll s2 = query(l, r, x->r, mid, rx);

    return s1 + s2;
}

int n, q;
vector<Node*> roots;
vector<int> a;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    roots.push_back(build(a, 0, n));

    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int k, a, x;
            scanf("%d %d %d", &k, &a, &x);
            a--; k--;
            roots[k] = update(roots[k], a, x, 0, n);
        }
        else if (op == 2) {
            int k, a, b;
            scanf("%d %d %d", &k, &a, &b);
            k--; a--;
            ll ans = query(a, b, roots[k], 0, n);
            printf("%lld\n", ans);
        }
        else {
            int k;
            scanf("%d", &k);
            k--;
            roots.push_back(new Node(roots[k]));
        }
    }

    return 0;
}