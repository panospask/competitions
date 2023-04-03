#include <bits/stdc++.h>

using namespace std;

map<char, int> latest_oc;
int n;
string cur;

void solve(void)
{
    scanf("%d", &n);

    latest_oc.clear();

    cin >> cur;
    for (int i = 0; i < cur.size(); i++)
        latest_oc[cur[i]] = i;

    pair<char, int> ans;
    for (auto i : latest_oc) {
        ans = i;
        break;
    }

    cout << ans.first;
    for (int i = 0; i < n; i++)
        if (i != ans.second)
            cout << cur[i];
    cout << endl;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}