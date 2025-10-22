#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;

bool query(int i, int j) {
    printf("%d %d\n", i, j);
    fflush(stdout);

    int res;
    scanf("%d", &res);
    return res;
}

bool merge(vector<int> a, vector<int> b) {
    for (auto i : a) {
        for (auto j : b) {
            if (query(i, j)) {
                return true;
            }
        }
    }

    return false;
}

void solve(void) {
    scanf("%d", &N);

    vector<vector<int>> cur;
    for (int i = 1; i <= N; i++) {
        cur.pb({i});
    }

    while (cur.size() > 1) {
        vector<vector<int>> nxt;

        while (cur.size() >= 2) {
            vector<int> a = cur.back();
            cur.pop_back();
            vector<int> b = cur.back();
            cur.pop_back();

            if (merge(a, b)) {
                return;
            }

            nxt.pb(a);
            nxt.back().insert(nxt.back().end(), b.begin(), b.end());
        }

        if (cur.size()) {
            nxt.pb(cur.back());
        }

        swap(nxt, cur);
    }

    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}