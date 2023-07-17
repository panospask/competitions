#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int n, q, p;
vector<int> v;
int size_a, size_b;
vector<vector<ll>> mul_at;

void d_c(int l, int r, int lev)
{
    if (l == r - 1) {
        return;
    }

    int mid = (l + r) / 2;

    mul_at[lev][mid - 1] = v[mid - 1] % p;
    for (int i = mid - 2; i >= l; i--)
        mul_at[lev][i] = v[i] * mul_at[lev][i + 1] % p;

    mul_at[lev][mid] = v[mid] % p;
    for (int i = mid + 1; i < r; i++)
        mul_at[lev][i] = mul_at[lev][i - 1] * v[i] % p;

    d_c(l, mid, lev + 1);
    d_c(mid, r, lev + 1);
}

void solve(void)
{
    v.clear();
    mul_at.clear();

    scanf("%d %d %d", &n, &p, &q);

    v.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &v[i]);

    size_a = 1; size_b = 0;
    while (size_a < n) {
        size_a *= 2;
        size_b++;
    }
    for (int i = n; i < size_a; i++)
        v.push_back(0);

    mul_at.resize(size_b, vector<ll>(size_a));

    d_c(0, size_a, 0);

    vector<int> b(q / 64 + 2);


    int p_l, p_r;
    int x = 0;
    for (int i = 0; i < q / 64 + 2; i++) {
        scanf("%d", &b[i]);
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        if (i % 64 == 0) {
            l = (b[i / 64] + x) % n;
            r = (b[i / 64 + 1] + x) % n;
            if (l > r)
                swap(l, r);
        }
        else {
            l = (p_l + x) % n;
            r = (p_r + x) % n;
            if (l > r)
                swap(l, r);
        }

        int diff = 32 - __builtin_clz(l ^ r);
        int lev = size_b - diff;

        if (l != r)
            x = (mul_at[lev][l] * mul_at[lev][r]) % p;
        else
            x = v[l] % p;

        x = (x + 1) % p;
        p_l = l;
        p_r = r;
    }

    printf("%d\n", x);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}