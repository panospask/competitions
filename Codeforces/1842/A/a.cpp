#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<int> a, b;

void solve(void)
{
    scanf("%d", &n);
    a.resize(n);
    scanf("%d", &m);
    b.resize(m);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for (int j = 0; j < m; j++)
        scanf("%d", &b[j]);

    long long a_sum = 0;
    for (int i = 0; i < n; i++)
        a_sum += a[i];
    long long b_sum = 0;
    for (int j = 0; j < m; j++)
        b_sum += b[j];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    if (a_sum > b_sum)
        printf("Tsondu\n");
    else if (b_sum > a_sum)
        printf("Tenzing\n");
    else
        printf("Draw\n");
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}