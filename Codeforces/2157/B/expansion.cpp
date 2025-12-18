#include <bits/stdc++.h>

using namespace std;

int N;
string s;
int X, Y;

void solve(void) {
    cin >> N >> X >> Y;
    cin >> s;

    X = abs(X);
    Y = abs(Y);

    for (int i = 0; i < N; i++) {
        if (Y > X) {
            swap(X, Y);
        }

        if (s[i] == '4') {
            X--;
        }
        else {
            X--;
            Y--;
        }
    }

    if (max(X, Y) > 0) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
    }
}

int main(void) {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}