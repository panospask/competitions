#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


int N;
ll ans = 0;
string s;
vector<int> lat_oc;
vector<int> after;

void solve(void)
{
    cin >> N;
    cin >> s;

    ans = 0;
    lat_oc.assign(26, -1);
    after.assign(N, N);

    for (int i = 0; i < N; i++) {
        if (lat_oc[s[i] - 'a'] != -1)
            after[lat_oc[s[i] - 'a']] = i;
        lat_oc[s[i] - 'a'] = i;
    }

    for (int i = 0; i < N; i++) {
        ans += after[i] - i;
    }

    cout << ans << endl;

    return;
}

int main(void)
{
    int t;
    cin >> t;

    while (t > 0) {
        solve();
        t--;
    }

    return 0;
}