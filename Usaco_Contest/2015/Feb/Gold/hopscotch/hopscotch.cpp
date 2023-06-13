#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MOD ((int)1e9 + 7)

using namespace std;

typedef long long ll;

struct SegTree {

    int size;
    vector<ll> tree;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(2 * size, 0);
    }

    void add(int i, ll v, int x, int lx, int rx) {
        if (lx == rx - 1) {
            tree[x] += v;
            tree[x] %= MOD;
            return;
        }

        int mid = (lx + rx) / 2;
        if (i < mid)
            add(i, v, 2 * x + 1, lx, mid);
        else
            add(i, v, 2 * x + 2, mid, rx);

        tree[x] = (tree[2 * x + 1] + tree[2 * x + 2]) % MOD;
    }
    void add(int i, ll v) {
        add(i, v, 0, 0, size);
    }

    ll get(int l, int r, int x, int lx, int rx) {
        if (l >= rx || lx >= r) {
            // Disjoint ranges
            return 0;
        }
        else if (l <= lx && rx <= r) {
            // Fully contained
            return tree[x];
        }

        int mid = (lx + rx) / 2;
        ll s1 = get(l, r, 2 * x + 1, lx, mid);
        ll s2 = get(l, r, 2 * x + 2, mid, rx);

        return (s1 + s2) % MOD;
    }
    ll get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};

int r, c, k;
vector<ll> val;
vector<vector<int>> row_of_val;
vector<vector<int>> grid;
vector<SegTree> special;

int find(int i, int j)
{
    int col = grid[i][j];

    return lower_bound(row_of_val[col].begin(), row_of_val[col].end(), j) - row_of_val[col].begin();
}

int main(void)
{
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);

    scanf("%d %d %d", &r, &c, &k);

    grid.assign(r, vector<int>(c));
    row_of_val.resize(k);
    special.resize(k);
    val.resize(c);

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            scanf("%d", &grid[i][j]);
            grid[i][j]--;

            bool isgood = true;
            for (auto col : row_of_val[grid[i][j]])
                if (col == j) {
                    isgood = false;
                    break;
                }

            if (isgood)
                row_of_val[grid[i][j]].push_back(j);
        }

    for (int i = 0; i < k; i++) {
        sort(row_of_val[i].begin(), row_of_val[i].end());
        special[i].init(row_of_val[i].size());
    }

    SegTree total;
    total.init(c);

    total.add(0, 1);
    special[grid[0][0]].add(find(0, 0), 1);

    for (int i = 1; i < r; i++) {
        for (int j = 1; j < c; j++) {
            val[j] = total.get(0, j);

            int col = grid[i][j];
            val[j] -= special[col].get(0, find(i, j));

            val[j] = (val[j] + MOD) % MOD;
        }

        for (int j = 1; j < c; j++) {
            total.add(j, val[j]);

            int col = grid[i][j];
            special[col].add(find(i, j), val[j]);
        }
    }

    printf("%lld\n", val.back());

    return 0;
}