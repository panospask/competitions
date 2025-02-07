#include <bits/stdc++.h>

using namespace std;

int N;
string s;

void solve(void)
{
    cin >> s;
    N = s.size();

    int ans = 0;
    for (int i = 0; i < N; i++) {
        ans += s[i] == '1';
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
    
    return 0;
}