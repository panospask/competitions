#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
string s;

int main(void) {
    freopen("whereami.in", "r", stdin);
    freopen("whereami.out", "w", stdout);

    cin >> N >> s;

    int K = 1;
    while (K < N) {
        // Test if K works

        bool are_equal = false;

        // O(N * logN) comparisons
        map<string, int> m;
        for (int i = 0; i < N - K + 1 && !are_equal; i++) {
            string t = s.substr(i, K);

            // O(logN) comparisons
            m[t]++;
            if (m[t] >= 2) {
                are_equal = true;
            }
        }

        // Are they equal or not?
        if (are_equal) {
            // This K is not good enough
            K++;
        }
        else {
            // This K is good enough
            break;
        }
    }

    cout << K << endl;
}