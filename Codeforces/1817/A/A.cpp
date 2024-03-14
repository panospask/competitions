#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<string> members;

void solve(void)
{
    cin >> n >> m;
    members.resize(n);
    for (int i = 0; i < n; i++)
        cin >> members[i];

    int ans = 0;
    for (int i = 0; i < n; i++)
        ans += members[i] == members[0];

    printf("%d\n", ans);
}

int t;
int main(void)
{
    iostream::sync_with_stdio(false);
    cin >> t;
    while (t--)
        solve();
}