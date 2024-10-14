#include <bits/stdc++.h>

using namespace std;

string a, b;

void solve(void)
{
    cin >> a >> b;

    if (a.size() > b.size()) {
        swap(a, b);
    }

    int i = 0;
    while (i < a.size() && a[i] == b[i]) {
        i++;
    }

    cout << min(a.size() + b.size() - i + 1, a.size() + b.size()) << endl;
}

int main(void)
{
    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}