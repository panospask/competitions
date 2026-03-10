#include <bits/stdc++.h>

using namespace std;

const int LETTERS = 26;

int M;
string s;
vector<int> b;
vector<int> cnt;
vector<bool> visited;

void solve(void) {
    cin >> s;
    cin >> M;

    b.resize(M);
    string t(M, 'a');
    cnt.assign(LETTERS, 0);
    visited.assign(M, false);

    for (int i = 0; i < M; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
    }


    int l = LETTERS - 1;
    vector<int> cost(M, 0);
    int fixed = 0;
    while (fixed < M) {
        vector<int> p;

        for (int i = 0; i < M; i++) {
            if (!visited[i] && cost[i] == b[i]) {
                p.push_back(i);
            }
        }
        
        while (cnt[l] < p.size()) {
            l--;
        }
        for (auto pos : p) {
            fixed++;
            visited[pos] = true;
            t[pos] = l + 'a';

            for (int i = 0; i < M; i++) {
                cost[i] += abs(i - pos);
            }
        }

        l--;
    }

    cout << t << endl;
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