#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<pi> A;

vector<pi> ans;

void solve(void) {
    scanf("%d %d", &N, &M);

    A.resize(N);
    ans.clear();
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i].first);
        A[i].second = i;
    }
    sort(A.begin(), A.end());

    int p = N / 2;
    if (N - M < p + N % 2) {
        printf("-1\n");
        return;
    }

    int l = N / 2 - 1;
    int r = N / 2;

    deque<int> line;
    if (N % 2) {
        line.pb(r);
        r++;
    }

    while (p > M) {
        line.push_front(l);
        line.push_back(r);
        l--;
        r++;
        p--;
    }

    if (M > 0) {
        for (auto x : line) {
            ans.pb(mp(x, x - 1));
        }
        int p = r;
        if (line.size()) {
            p++;
            ans.pb(mp(line.back() + 1, line.back()));
        }

        for (int i = p; i < N; i++) {
            ans.pb(mp(i, N - i - 1));
        }
    }
    else {
        // Tricky part, always shoot N - 1
        int p = -1;
        for (int i = N - 2; i >= 0; i--) {
            if (A[i].first >= A[N - 1].first) {
                p = i;
                break;
            }
            ans.pb(mp(i, N - 1));
            A[N - 1].first -= A[i].first;
        }

        if (p == -1) {
            printf("-1\n");
            return;
        }

        for (int i = 0; i < p; i++) {
            ans.pb(mp(i, i + 1));
        }
        ans.pb(mp(N - 1, p));
    }

    printf("%d\n", (int)ans.size());
    for (auto [x, y] : ans) {
        printf("%d %d\n", A[x].second + 1, A[y].second + 1);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}