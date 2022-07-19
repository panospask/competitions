/*
ID: panos.p1
LANG: C++11
TASK: contact
*/

#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

vector<string> ans[MAXN];
map<string, int> pattern;
int a, b, n;
string message;

bool stringcom(const string& a, const string& b)
{
    if (a.size() == b.size())
        return a < b;

    return a.size() < b.size();
}

int main(void)
{
    freopen("contact.in", "r", stdin);
    freopen("contact.out", "w", stdout);

    scanf("%d %d %d", &a, &b, &n);

    string x;
    while (getline(cin, x)) {
        message += x;
    }

    string cur;
    for (int i = a; i <= b && i <= message.size(); i++) {
        cur = message.substr(0, i);
        pattern[cur]++;
        for (int j = i; j < message.size(); j++) {
            cur.erase(cur.begin());
            cur.pb(message[j]);
            pattern[cur]++;
        }
    }

    int maxans = 0;
    for (auto& pat : pattern) {
        ans[pat.second].pb(pat.first);
        maxans = max(maxans, pat.second);
    }

    int cnt = 0;
    int i = maxans;
    while (cnt < n && i >= 0) {
        if (!ans[i].empty()) {
            sort(ans[i].begin(), ans[i].end(), stringcom);
            printf("%d\n", i);
            cnt++;
            int u = 0;
            for (auto j : ans[i]) {
                u++;
                cout << j;
                if (u == ans[i].size() || (u != 0 && u % 6 == 0))
                    cout << '\n';
                else 
                    cout << ' ';
            }
        }
        i--;
    }
    return 0;
}