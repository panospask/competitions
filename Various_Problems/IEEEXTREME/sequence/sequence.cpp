#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> S;
vector<vector<int>> idx;

vector<vector<int>> sequences;

int p1 = 0;
int p2 = 0;
int p3 = 0;

void solve(void) {
    string s;
    cin >> s;
    N = s.size();

    idx.assign(4, vector<int>());
    S.resize(s.size());
    sequences.assign(s.size() / 6, vector<int>(6, -1));
    for (int i = 0; i < s.size(); i++) {
        S[i] = s[i] - '0';
        idx[S[i]].push_back(i);

        if (S[i] == 2) {
            int j = idx[1].back();

            idx[3].push_back(j);
            S[j] = 3;
            idx[1].pop_back();

        }
    }

    for (int i = 0; i < 4; i++) {
        reverse(idx[i].begin(), idx[i].end());
    }

    p1 = p2 = p3 = 0;
    for (int i = 0; i < N; i++) {
        if (S[i] != 1 && S[i] != 3) {
            // Already used, only rely on 1s
            continue;
        }

        if (S[i] == 1) {
            sequences[p1][0] = i;
            p1++;
        }
        else {
            if (p2 != p1) {
                // Find 120
                sequences[p2][1] = i;
                sequences[p2][2] = idx[2].back();
                idx[2].pop_back();
                sequences[p2][3] = idx[0].back();
                idx[0].pop_back();

                p2++;
            }
            else {
                // Find 12
                sequences[p3][4] = i;
                sequences[p3][5] = idx[2].back();
                idx[2].pop_back();
                p3++;
            }
        }
    }

    for (int i = 0; i < N / 6; i++) {
        for (int s = 0; s < 6; s++) {
            cout << sequences[i][s] + 1 << ' ';
        }
        cout << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);

    int T;
    cin >> T;

    while (T--) {
        solve();
    }
}