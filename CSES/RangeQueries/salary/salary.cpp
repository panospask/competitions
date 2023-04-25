#include <bits/stdc++.h>

using namespace std;

struct segtree {

    int size;
    vector<int> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.resize(2 * size);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (lx == rx - 1) {
            if (lx < a.size())
                tree[x] = a[lx];
            else
                tree[x] = 0;
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, 2 * x + 1, lx, mid);
        build(a, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void add(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = tree[2 * x + 1] + tree[2  * x + 2];
    }
    void add(int i, int v) {
        add(i, v, 0, 0, size);
    }

    int sum(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint segments
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return sum(l, r, 2 * x + 1, lx, mid) + sum(l, r, 2 * x + 2, mid, rx);
    }
    int sum(int l, int r) {
        return sum(l, r, 0, 0, size);
    }
};

set<int> values;
vector<int> valnum;

struct Query {
    char op;
    int a, b;
    void readquery(void) {
        scanf(" %c %d %d", &op, &a, &b);
        if (op == '!') {
            a--;
            values.insert(b);
        }
    }
};

int find_comp(int a)
{
    return (lower_bound(valnum.begin(), valnum.end(), a) - valnum.begin());
}

int n, q, valsize;
vector<int> salaries;
vector<Query> queries;
segtree st;

int main(void)
{
    scanf("%d %d", &n, &q);
    salaries.resize(n);
    queries.resize(q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &salaries[i]);
        values.insert(salaries[i]);
    }

    for (int i = 0; i < q; i++)
        queries[i].readquery();

    valsize = values.size();
    st.init(valsize);

    int cur = 0;
    for (auto v : values)
        valnum.push_back(v);

    vector<int> initial(valsize + 1);
    for (int i = 0; i < n; i++)
        initial[find_comp(salaries[i])]++;
    st.build(initial);

    for (int i = 0; i < q; i++) {
        auto cur = queries[i];
        if (cur.op == '!') {
            st.add(find_comp(salaries[cur.a]), -1);
            salaries[cur.a] = cur.b;
            st.add(find_comp(cur.b), 1);
        }
        else {
            int v1 = find_comp(cur.a);
            int v2 = find_comp(cur.b+1);

            printf("%d\n", st.sum(v1, v2));
        }
    }

    return 0;
}