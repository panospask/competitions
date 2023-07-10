#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<int> tree;

    void add(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] += v;
    }

    int get(int i) {
        int res = 0;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res += tree[x];
        return res;
    }
    int get(int l, int r) {
        return get(r - 1) - get(l - 1);
    }

    void init(int n) {
        size = n;
        tree.resize(size, 0);
    }
};

struct Query {
    int time;
    int pos;
    int val;
};

bool pos_sort(const Query& a, const Query& b)
{
    return a.pos < b.pos;
}

int n;
BITree freq;
vector<int> a;
vector<int> p;
vector<Query> initial;
vector<ll> ans;

void calculate(vector<Query>& queries)
{
    if (queries.size() == 1) {
        // No inversions
        return;
    }

    int mid = queries.size() / 2;
    vector<Query> q1(mid), q2(queries.size() - mid);
    for (int i = 0; i < mid; i++)
        q1[i] = queries[i];
    for (int i = mid; i < queries.size(); i++)
        q2[i - mid] = queries[i];

    calculate(q1);
    calculate(q2);

    sort(q1.begin(), q1.end(), pos_sort);
    sort(q2.begin(), q2.end(), pos_sort);

    int curp = 0;
    for (auto q : q2) {
        while (curp < mid && q1[curp].pos < q.pos) {
            freq.add(q1[curp].val, 1);
            curp++;
        }

        int inv_cnt = freq.get(q.val + 1, n);
        ans[q.time] += inv_cnt;
    }
    curp--;
    while (curp >= 0) {
        freq.add(q1[curp].val, -1);
        curp--;
    }

    reverse(q1.begin(), q1.end());
    reverse(q2.begin(), q2.end());
    curp = 0;
    for (auto q : q2) {
        while (curp < mid && q1[curp].pos > q.pos) {
            freq.add(q1[curp].val, 1);
            curp++;
        }

        int inv_cnt = freq.get(0, q.val);
        ans[q.time] += inv_cnt;
    }
    curp--;
    while (curp >= 0) {
        freq.add(q1[curp].val, -1);
        curp--;
    }
}

int main(void)
{
    scanf("%d", &n);

    a.resize(n);
    ans.assign(n, 0);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    p.resize(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        p[i]--;

        initial.push_back({i, p[i], a[p[i]]});
    }

    freq.init(n);

    calculate(initial);

    ll pref_ans = 0;
    for (int i = 0; i < n; i++) {
        pref_ans += ans[i];
        printf("%lld\n", pref_ans);
    }

    return 0;
}