#include <bits/stdc++.h>

using namespace std;

string s;
void solve(void)
{
    int max_w_out = INT_MAX;
    cin >> s;

    for (char c = 'a'; c <= 'z'; c++) { 
        int curm = 0;
        int latest = -1;
        s.push_back(c);
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == c) {
                curm = max(curm, i - latest - 1);
                latest = i;
            }
        }
        s.pop_back();
        max_w_out = min(max_w_out, curm);
    }

    int ans = 0;
    while (max_w_out) {
        ans++;
        max_w_out /= 2;
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();

    return 0;
}