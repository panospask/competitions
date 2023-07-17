#include <bits/stdc++.h>

using namespace std;

int n, ans;
vector<int> a, b;

int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);

    while (b)
        swap(b, a %= b);

    return a;
}

void set_ans(int v)
{
    if (ans == -1)
        ans = v;
    else if (ans != v)
        ans = 0;
}

bool check_ans(void)
{
    return ans;
}

void solve(void)
{
    ans = -1;
    scanf("%d", &n);

    a.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    b.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d", &b[i]);

    for (int i = 0; i < n; i++) {
        if (a[i] == 0 && b[i] == 0)
            continue;

        int g = gcd(a[i], b[i]);
        a[i] /= g;
        b[i] /= g;

        if (a[i] % 2) {
            if (b[i] % 2)
                set_ans(1);
            else
                set_ans(2);
        }
        else
            set_ans(3);
    }

    if (check_ans())
        printf("YES\n");
    else
        printf("NO\n");
}

int main(void)
{
    int t;

    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}