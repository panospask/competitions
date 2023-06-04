#include <bits/stdc++.h>

using namespace std;

struct segtree {

    vector<bool> tree;
    int size;

    void init(int n) {
        size = 1;
        while (size < n)
            size *= 2;

        tree.assign(size * 2, false);
    }

    void build(vector<int>& a, int x, int l_x, int r_x) {
        if (l_x == r_x - 1) {
            if (l_x < a.size())
                tree[x] = false;
            else
                tree[x] = false;

            return;
        }

        int mid = (l_x + r_x) / 2;
        build(a, 2 * x + 1, l_x, mid);
        build(a, 2 * x + 2, mid, r_x);

        tree[x] = tree[2 * x + 1] || tree[2 * x + 2];
    }
    void build(vector<int>& a) {
        build(a, 0, 0, size);
    }

    void set(int pos, int val, int x, int l, int r) {
        if (l == r - 1) {
            tree[x] = val;
            return;
        }

        int mid = (l + r) / 2;
        if (pos < mid)
            set(pos, val, 2 * x + 1, l, mid);
        else
            set(pos, val, 2 * x + 2, mid, r);

        tree[x] = tree[2 * x + 1] || tree[2 * x + 2];
    }
    void set(int pos, int val) {
        set(pos, val, 0, 0, size);
    }

    bool calc(int l, int r, int x, int l_x, int r_x) {
        if (l >= r_x || l_x >= r) {
            // Non intersecting segments
            return 0;
        }
        if (l <= l_x && r_x <= r) {
            // The query range is fully contained
            return tree[x];
        }

        int mid = (l_x + r_x) / 2;
        auto s1 = calc(l, r, 2 * x + 1, l_x, mid);
        auto s2 = calc(l, r, 2 * x + 2, mid, r_x);

        return s1 || s2;
    }
    long long int calc(int l, int r) {
        return calc(l, r, 0, 0, size);
    }
};

int n, q;
vector<int> diff;
vector<int> seq;
int total_diff;
segtree continuous_left;
segtree continuous_right;

void solve(void)
{
    scanf("%d %d", &n, &q);

    diff.resize(n + 5);
    seq.resize(n + 5);
    continuous_left.init(n + 5);
    continuous_right.init(n + 5);

    diff[0] = 0;
    for (int i = 1; i <= n; i++) {
        char c;
        scanf(" %c", &c);
        if (c == '(')
            seq[i] = 1;
        else
            seq[i] = -1;
        total_diff += seq[i];

        if (i != 0 && seq[i - 1] == seq[i]) {
            if (seq[i] == 1) {
                continuous_left.set(i, true);
            }
            else
                continuous_right.set(i, true);
        }


        diff[i + 1] = total_diff;
    }

    for (int j = -1; j < q; j++) {
        int i;

        if (j != -1) {
            scanf("%d", &i);
            i--;

            if (seq[i] == 1) {
                total_diff -= 2;

                seq[i] = -1;
                continuous_left.set(i, false);

                if (i != 0 && seq[i] == seq[i - 1])
                    continuous_right.set(i, true);

                if (i != n - 1) {
                    continuous_left.set(i + 1, false);

                    if (seq[i] == seq[i + 1])
                        continuous_right.set(i + 1, true);
                }
            }
            else {
                total_diff += 2;
                seq[i] = 1;
                continuous_right.set(i, false);

                if (i != 0 && seq[i] == seq[i - 1])
                    continuous_left.set(i, true);

                if (i != n - 1) {
                    continuous_right.set(i + 1, false);

                    if (seq[i] == seq[i + 1])
                        continuous_left.set(i + 1, true);
                }
            }
        }

        if (seq[0] == -1 || seq[n - 1] == 1) {
            printf("NO\n");
            continue;
        }
        if (total_diff % 2) {
            printf("NO\n");
            continue;
        }
        if (total_diff < 0 && !continuous_left.calc(0, n)) {
            printf("NO\n");
            continue;
        }
        if (total_diff > 0 && !continuous_right.calc(0, n)) {
            printf("NO\n");
            continue;
        }

        printf("YES\n");
    }

    return;
}

int main(void)
{
    solve();
}