#include <bits/stdc++.h>

using namespace std;

int N;
vector<string> A;

void solve(void) {
    cin >> N;

    A.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    string ans;
    for (int i = 0; i < N; i++) {
        string a1 = ans, a2 = ans;
        a1.append(A[i]);
        a2.insert(a2.begin(), A[i].begin(), A[i].end());

        if (a1 < a2) {
            ans = a1;
        }
        else {
            ans = a2;
        }
    }

    cout << ans << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}