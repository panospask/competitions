#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int MAXV = 1e6 + 5;

int N;
vector<vector<int>> A;
vector<set<pi>> B;

vector<pi> occur[MAXV];

vector<int> ans;

void solve(void) {
    scanf("%d", &N);

    ans.clear();
    A.assign(N, vector<int>());
    B.assign(N, set<pi>());
    vector<int> remaining;
    for (int i = 0; i < N; i++) {
        int l;
        scanf("%d", &l);
        remaining.push_back(i);

        A[i].resize(l);
        for (int j = 0; j < l; j++) {
            scanf("%d", &A[i][j]);
        }
        reverse(A[i].begin(), A[i].end());
        for (int j = 0 ; j < l; j++) {
            occur[A[i][j]].push_back({i, j});
            B[i].insert({j, A[i][j]});
        }
    }

    while (remaining.size() >= 1) {
        vector<int> candidates = remaining;
        while (true) {
            int nxt = MAXV;
            vector<int> whohas;
            for (int c = 0; c < candidates.size(); c++) {
                int v = B[candidates[c]].size() == 0 ? -1 : (*B[candidates[c]].begin()).second;
                if (v < nxt) {
                    nxt = v;
                    whohas.clear();
                }
                if (v == nxt) {
                    whohas.push_back(candidates[c]);
                }
            }

            // Update the optimals
            candidates = whohas;

            if (nxt != -1) {
                ans.push_back(nxt);
                // Remove all occurences
                for (auto [i, j] : occur[nxt]) {
                    B[i].erase({j, nxt});
                }
            }
            else {
                break;
            }
        }
        
        // Remove all current candidates
        for (auto c : candidates) {
            remaining.erase(find(remaining.begin(), remaining.end(), c));
        }
    }

    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");


    for (int i = 0; i < ans.size(); i++) {
        occur[ans[i]].clear();
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}