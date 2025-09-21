#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e9;

int N;
vector<vector<int>> A;

set<int> exist;
map<int, bool> running;

vector<int> ans;

void solve(void) {
    scanf("%d", &N);

    A.assign(N, vector<int>());
    exist.clear();
    running.clear();
    ans.clear();

    for (int i = 0; i < N; i++) {
        int k;
        scanf("%d", &k);

        A[i].resize(k);
        for (int j = 0; j < k; j++) {
            scanf("%d", &A[i][j]);
        }
        exist.insert(i);
        running[i] = true;
    }

    int p = 0;
    while (exist.size()) {
        int opt = INF;
        
        vector<int> del;
        for (auto i : exist) {
            if (running[i]) {
                opt = min(opt, A[i][p]);
            }
            if (A[i].size() == p + 1) {
                del.pb(i);
            }
        }

        ans.pb(opt);

        bool fix = false;
        for (auto i : del) {
            if (running[i] && A[i][p] == opt) {
                // Everything is good now
                fix = true;
            }
            exist.erase(i);
        }

        for (auto i : exist) {
            if (fix) {
                running[i] = true;
            }
            else if (A[i][p] > opt) {
                running[i] = false;
            }
        }

        p++;
    }

    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", (int)ans[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}