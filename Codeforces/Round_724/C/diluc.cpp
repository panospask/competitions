#include <bits/stdc++.h>

using namespace std;

int n;
unordered_map<int, unordered_map<int, int>> pieces_split;
string s;

int gcd(int a, int b)
{
    if (a < b)
        swap(a, b);

    while (b != 0)
        swap(b, a %= b);

    return a;
}

void solve(void)
{
    pieces_split.clear();

    scanf("%d", &n);
    s.resize(n);

    for (int i = 0; i < n; i++)
        scanf(" %c", &s[i]);

    int d_freq = 0;
    int k_freq = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'D')
            d_freq++;
        else
            k_freq++;

        int g = gcd(d_freq, k_freq);
        int d_reduced = d_freq / g;
        int k_reduced = k_freq / g;

        int ans = pieces_split[d_reduced][k_reduced]++ + 1;
        printf("%d ", ans);
    }
    printf("\n");

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