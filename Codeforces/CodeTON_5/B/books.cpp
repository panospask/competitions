#include <bits/stdc++.h>

using namespace std;

int n, x;
vector<int> a;
vector<int> a_bit_first;

vector<int> b;
vector<int> b_bit_first;

vector<int> c;
vector<int> c_bit_first;

void solve(void)
{
    scanf("%d %d", &n, &x);
    a.resize(n);
    a_bit_first.assign(32, n);

    b.resize(n);
    b_bit_first.assign(32, n);

    c.resize(n);
    c_bit_first.assign(32, n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);

        for (int pos = 0; pos < 32; pos++) {
            if (a_bit_first[pos] != n)
                continue;

            if (a[i] & (1 << pos))
                a_bit_first[pos] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &b[i]);

        for (int pos = 0; pos < 32; pos++) {
            if (b_bit_first[pos] != n)
                continue;

            if (b[i] & (1 << pos))
                b_bit_first[pos] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &c[i]);

        for (int pos = 0; pos < 32; pos++) {
            if (c_bit_first[pos] != n)
                continue;

            if (c[i] & (1 << pos))
                c_bit_first[pos] = i;
        }
    }

    int a_min, b_min, c_min;
    a_min = b_min = c_min = n;

    for (int pos = 0; pos < 32; pos++) {
        if (!(x & (1<<pos))) {
            a_min = min(a_min, a_bit_first[pos]);
            b_min = min(b_min, b_bit_first[pos]);
            c_min = min(c_min, c_bit_first[pos]);
        }
    }

    int v = 0;
    for (int i = 0; i < a_min; i++)
        v = v | a[i];
    for (int i = 0; i < b_min; i++)
        v = v | b[i];
    for (int i = 0; i < c_min; i++)
        v = v | c[i];

    if (v == x)
        printf("Yes\n");
    else
        printf("No\n");

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