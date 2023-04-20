#include <bits/stdc++.h>

using namespace std;

int n;

void solve(void)
{
    string s;
    cin >> s;

    long long ans = 1;
    if (s[0] == '?')
        ans *= 9;
    else if (s[0] == '0') {
        printf("0\n");
        return;
    }
    
    for (int i = 1; i < s.size(); i++)
        if (s[i] == '?')
            ans *= 10;

    printf("%lld\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}