#include <bits/stdc++.h>
#define x first
#define y second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

struct BITree {
    int size;
    vector<int> tree;

    void add(int i, int l) {
        for (int v = i; v < size; v = v | (v + 1))
            tree[v] += l;
    }
    int get(int i) {
        int res = 0;
        for (int v = i; v >= 0; v = (v & (v + 1)) - 1)
            res += tree[v];
        return res;
    }
    int get(int l, int r) {
        return get(r) - get(l - 1);
    }

    void init(int n) {
        size = n;
        tree.resize(n, 0);
    }
};

struct Query {
    int l, r, i;
};

int n, q;
BITree rec;
vector<int> xcord;
vector<int> yval;
vector<int> ans;

vector<vector<Query>> start_at;
vector<vector<Query>> end_at;

int main(void)
{
    scanf("%d", &n);

    xcord.resize(n);
    yval.resize(n);
    ans.resize(n);
    rec.init(n);
    start_at.resize(n);
    end_at.resize(n);

    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;
        xcord[i] = num;
    }
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;
        yval[num] = i;
    }

    scanf("%d", &q);
    ans.resize(q);
    for (int i = 0; i < q; i++) {
        int l1, r1, l2, r2;
        scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
        l1--; r1--; l2--; r2--;

        start_at[l1].push_back({l2, r2, i});
        end_at[r1].push_back({l2, r2, i});
        ans[i] += r1 - l1 + 1;
    }

    for (int i = 0; i < n; i++) {
        for (auto v : start_at[i])
            ans[v.i] += rec.get(v.l, v.r);
        rec.add(yval[xcord[i]], 1);
        for (auto v : end_at[i])
            ans[v.i] -= rec.get(v.l, v.r);
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);
}