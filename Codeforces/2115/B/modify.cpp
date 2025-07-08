#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e9;

int N, Q;
vector<int> b;
vector<int> idx;
vector<int> ans;

vector<int> opt;
vector<pi> parents;

vector<vector<int>> kids;

void solve(void) {
    scanf("%d %d", &N, &Q);

    b.resize(N);
    idx.resize(N);
    parents.resize(N + Q);
    kids.assign(N + Q, vector<int>());
    opt.assign(N + Q, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    // Initialize the first N elements(array A)
    for (int i = 0; i < N; i++) {
        idx[i] = i;
        parents[i] = mp(-1, -1);
    }

    for (int i = 0; i < Q; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--; z--;

        int X = idx[x];
        int Y = idx[y];
        idx[z] = N + i;

        int Z = idx[z];
        parents[Z] = mp(X, Y);
        kids[X].pb(Z);
        kids[Y].pb(Z);
    }

    for (int i = 0; i < N; i++) {
        opt[idx[i]] = b[i];
    }

    for (int u = N + Q - 1; u >= 0; u--) {
        for (auto k : kids[u]) {
            if (min(opt[parents[k].first], opt[parents[k].second]) > opt[k]) {
                printf("-1\n");
                return;
            }
        }

        if (u >= N) {
            opt[parents[u].first] = max(opt[parents[u].first], opt[u]);
            opt[parents[u].second] = max(opt[parents[u].second], opt[u]);
        }
    }

    for (int i = 0; i < N; i++) {
        if (opt[idx[i]] != b[i]) {
            printf("-1\n");
            return;
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", opt[i]);
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