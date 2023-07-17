#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct BITree {
    int size;
    vector<int> tree;

    void clear(void) {
        tree.assign(size, 0);
    }
    void init(int n) {
        size = n;
        tree.resize(size);
    }

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
    int rget(int l) {
        return get(l, size);
    }
};

struct Query {
    int l, r, id;
};

int N, Q;
int BLOCK_SIZE;
vector<int> a;
vector<vector<Query>> blocks;
vector<int> compress;
BITree vals;
vector<ll> ans;

void process_block(int b)
{
    vals.clear();

    ll cur_ans = 0;
    int nxt = BLOCK_SIZE * b;

    for (int i = 0; i < blocks[b].size(); i++) {
        int l = blocks[b][i].l;
        int r = blocks[b][i].r;
        int id = blocks[b][i].id;

        while (nxt <= r) {
            cur_ans += vals.rget(a[nxt] + 1);
            vals.add(a[nxt], 1);

            nxt++;
        }

        ans[id] = cur_ans;

        for (int j = BLOCK_SIZE * b; j < l; j++) {
            vals.add(a[j], -1);
            ans[id] -= vals.get(a[j] - 1);
        }
        for (int j = BLOCK_SIZE * b; j < l; j++) {
            vals.add(a[j], 1);
        }
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    ans.resize(Q);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        compress.push_back(a[i]);
    }
    sort(compress.begin(), compress.end());
    compress.resize(unique(compress.begin(), compress.end()) - compress.begin());

    for (int i = 0; i < N; i++) {
        a[i] = lower_bound(compress.begin(), compress.end(), a[i]) - compress.begin();
    }
    vals.init(compress.size());

    BLOCK_SIZE = sqrt(N);
    // BLOCK_SIZE + 2, not 1
    blocks.resize(BLOCK_SIZE + 2);
    for (int i = 0; i < Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        r--;

        blocks[l / BLOCK_SIZE].push_back({l, r, i});
    }

    for (int b = 0; b < BLOCK_SIZE + 2; b++) {
        sort(blocks[b].begin(), blocks[b].end(), [] (const Query& a, const Query& b) {return a.r < b.r;});
        process_block(b);
    }

    for (int i = 0; i < Q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}