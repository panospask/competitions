#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int LETTERS = 26;

int N, K;
string s, t;

vector<int> positions[LETTERS];

vector<string> operations;

void solve(void) {
    cin >> N >> K;
    cin >> s >> t;

    for (int l = 0; l < LETTERS; l++) {
        positions[l].clear();
    }
    operations.assign(K + 1, string(N, '?'));

    for (int i = 0; i < N; i++) {
        positions[s[i] - 'a'].pb(i);
    }

    // Last "source" in s;
    int last = N - 1;
    int ans = 0;
    for (int i = N - 1; i >= 0; i--) {
        int v = t[i] - 'a';

        int idx = upper_bound(positions[v].begin(), positions[v].end(), min(i, last)) - positions[v].begin() - 1;
        if (idx == -1) {
            cout << -1 << endl;
            return;
        }

        // We have found our new "source" position
        int pos = positions[v][idx];
        int moves = i - pos;
        last = pos;

        if (moves > K) {
            // Exceeded move limit
            cout << -1 << endl;
            return;
        }

        ans = max(ans, moves);
        for (int j = 0; j <= moves; j++) {
            operations[j][pos + j] = t[i];
        }
    }

    // Fix final operations
    operations[0] = s;
    for (int j = 1; j <= ans; j++) {
        for (int i = 0; i < N; i++) {
            if (operations[j][i] == '?') {
                operations[j][i] = operations[j - 1][i];
            }
        }
    }

    cout << ans << endl;
    for (int j = 1; j <= ans; j++) {
        cout << operations[j] << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}