#include <bits/stdc++.h>
#include "towers.h"

using namespace std;

typedef long long ll;

struct SegTree {
    int size;
    vector<int> tree;

    void init(int N) {
        size = 1;
        while (size < N)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void set(int i, int v, int x, int lx, int rx) {
        if (lx == rx - 1)  {
            tree[x] = v;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            set(i, v, 2 * x + 1, lx, mid);
        else
            set(i, v, 2 * x + 2, mid, rx);

        tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
    }
    void set(int i, int v) {
        set(i, v, 0, 0, size);
    }

    int get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            return 0;
        }
        else if (l <= lx && rx <= r) {
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        return max(get(l, r, 2 * x + 1, lx, mid), get(l, r, 2 *x + 2, mid, rx));
    }
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

// Complete subtask 1
int N, K;
bool sub1 = false;
vector<int> H;
vector<int> comp;
SegTree s1, s2;

int find(int v)
{
    return upper_bound(comp.begin(), comp.end(), v) - comp.begin() - 1;
}

bool gcomp(const int& a, const int& b)
{
    return a > b;
}

void init(int n, vector<int> h)
{
    N = n;
    H = comp = h;
    K = -1;
    sort(comp.begin(), comp.end());

    H.push_back(-1);
    for (int i = 0; i < N ; i++) {
        if (H[i] > H[i + 1] && K == -1) {
            sub1 = true;
            K = i;
        }
        else if (K != -1 && H[i] < H[i + 1]) {
            sub1 = false;
        }
    }
    H.pop_back();
}

int first_task(int L, int R, int D)
{
    if (L >= K || R <= K)
        return 1;

    if (H[L] <= H[K] - D && H[R] <= H[K] - D)
        return 2;
    else
        return 1;
}

int max_towers(int L, int R, int D)
{
    if (sub1)
        return first_task(L, R, D);

    vector<ll> dp(N);
    vector<ll> prv_accept(N);

    s1.init(N);
    s2.init(N);
    ll ans = 1;
    s1.set(find(H[L]), 0);
    s2.set(find(H[L]), 1);

    for (int i = L + 1; i <= R; i++) {
        dp[i] = s1.get(find(H[i] + D) + 1, N);

        prv_accept[i] = s2.get(0, find(H[i] - D) + 1);

        dp[i]++;

        s1.set(find(H[i]), prv_accept[i]);
        s2.set(find(H[i]), dp[i]);
        ans = max(ans, dp[i]);
    }

    return ans;
}