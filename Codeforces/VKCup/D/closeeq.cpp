#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node {
    int val;
    Node* l, *r;

    Node(int v) : val(v), l(nullptr), r(nullptr) {};
    Node(Node* a, Node* b) : val(min(a->val, b->val)), l(a), r(b) {};
};

Node* build(int lx, int rx)
{
    if (lx == rx - 1)
        return new Node(INT_MAX);

    int mid = (lx + rx) / 2;
    return new Node(build(lx, mid), build(mid, rx));
}

Node *update(int i, int v, Node* x, int lx, int rx)
{
    if (lx == rx - 1)
        return new Node(v);

    int mid = (lx + rx) / 2;
    if (i < mid)
        return new Node(update(i, v, x->l, lx, mid), x->r);
    else
        return new Node(x->l, update(i, v, x->r, mid, rx));
}

int query(int l, int r, Node* x, int lx, int rx)
{
    if (l >= rx || lx >= r)
        return INT_MAX;
    else if (l <= lx && rx <= r)
        return x->val;

    int mid = (lx + rx) / 2;
    auto v1 = query(l, r, x->l, lx, mid);
    auto v2 = query(l, r, x->r, mid, rx);
    return min(v1, v2);
}

int n, q;
vector<Node*> roots;
vector<int> ins_time;
vector<int> a;
map<int, int> latest_oc;

int main(void)
{
    scanf("%d %d", &n, &q);
    a.resize(n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    roots.push_back(build(0, n));
    ins_time.push_back(INT_MIN);
    for (int i = 0; i < n; i++) {
        if (latest_oc.find(a[i]) != latest_oc.end()) {
            int lpos = latest_oc[a[i]];
            roots.push_back(update(lpos, i - lpos, roots.back(), 0, n));
            ins_time.push_back(i);
        }
        latest_oc[a[i]] = i;
    }

    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        l--; r--;
        int pos = upper_bound(ins_time.begin(), ins_time.end(), r) - ins_time.begin() - 1;
        int ans = query(l, r + 1, roots[pos], 0, n);
        if (ans == INT_MAX)
            printf("-1\n");
        else
            printf("%d\n", ans);
    }

    return 0;
}