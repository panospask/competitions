#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e15;

int N;
vector<int> A;

// dp[i][c]: Max/Min for the first positions, given that there are c (parity) operations
vector<vector<ll>> maxs;
vector<vector<ll>> mins;
vector<int> operations;

void retrieve(int i, bool mx) {
    if (i == 0) {
        return;
    }
    int parity = operations.size() % 2;
    int v = (parity == 0) ? A[i] : -A[i];

    if (v < 0) {
        retrieve(i - 1, mx);
    }
    else {
        if (mx) {
            ll a = maxs[i - 1][parity] + v;
            ll b = maxs[i - 1][!parity] - v;
            ll c = -mins[i - 1][parity] - v;

            if (a > b && a > c) {
                retrieve(i - 1, mx);
            }
            else if (b >= c) {
                operations.push_back(i);
                retrieve(i - 1, mx);
            }
            else {
                retrieve(i - 1, !mx);
                operations.push_back(i);
            }
        }
        else {
            ll a = mins[i - 1][parity] + v;
            ll b = mins[i - 1][!parity] - v;
            ll c = -maxs[i - 1][parity] - v;

            if (a < b && a < c) {
                retrieve(i - 1, mx);
            }
            else if (b <= c) {
                operations.push_back(i);
                retrieve(i - 1, mx);
            }
            else {
                retrieve(i - 1, !mx);
                operations.push_back(i);
            }
        }
    }
}

void solve(void) {
    scanf("%d", &N);

    A.resize(N + 1);
    maxs.assign(N + 1, vector<ll>(2, -INF));
    mins.assign(N + 1, vector<ll>(2, -INF));
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    maxs[0][0] = maxs[0][1] = 0;
    mins[0][0] = mins[0][1] = 0;
    for (int i = 1; i <= N; i++) {
        for (int c = 0; c < 2; c++) {
            // We can either choose to make operation here or not
            int v = c == 0 % 2 ? A[i] : -A[i];
            maxs[i][c] = maxs[i - 1][c] + v;
            mins[i][c] = mins[i - 1][c] + v;

            // Operation only allowed if v > 0
            if (v > 0) {
                maxs[i][c] = max(maxs[i][c], maxs[i - 1][!c] - v);
                maxs[i][c] = max(maxs[i][c], -mins[i - 1][c] - v);

                mins[i][c] = min(mins[i][c], mins[i - 1][!c] - v);
                mins[i][c] = min(mins[i][c], -maxs[i - 1][c] - v);
            }
        }
    }  

    operations.clear();
    retrieve(N, true);

    printf("%d\n", (int)operations.size());
    for (auto i : operations) {
        printf("%d ", i);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}