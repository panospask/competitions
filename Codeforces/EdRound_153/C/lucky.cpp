#include <bits/stdc++.h>

using namespace std;

struct BITree {
    int size;
    vector<bool> tree;

    void init(int n) {
        size = n;
        tree.assign(size, true);
    }

    void set(int i, int v) {
        for (int x = i; x < size; x = x | (x + 1))
            tree[x] = tree[x] && v;
    }

    bool get(int i) {
        bool res = true;
        for (int x = i; x >= 0; x = (x & (x + 1)) - 1)
            res = res && tree[x];

        return res;
    }
};

int N;
vector<int> p;
BITree b;
int ans;

void solve(void)
{
    scanf("%d", &N);
    p.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
        p[i]--;
    }

    ans = 0;
    b.init(N);
    int smallest = INT_MAX;
    for (int i = 0; i < N; i++) {
        bool res;
        if (smallest < p[i])
            res = !b.get(p[i] - 1);
        else
            res = true;

        if (!res)
            ans++;

        smallest = min(smallest, p[i]);
        b.set(p[i], res);
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}