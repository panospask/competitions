// This is the fast implementation, not the one in usaco guide.

#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int MAXA = 1e6 + 1;

int N;
vector<int> cnt;
vector<int> a;
vector<pi> op;

bool check(int x)
{
    op.clear();
    for (int i = 0; i < 2 * N; i++) {
        cnt[a[i]] = 0;
    }
    for (int i = 0; i < 2 * N; i++) {
        cnt[a[i]]++;
    }

    // Find the maximum by going backwards at a each time
    for (int i = 2 * N - 1; i >= 0; i--) {
        if (cnt[a[i]] == 0)
            continue;

        int big = a[i];
        cnt[big]--;

        int small = x - big;
        if (cnt[small] == 0) {
            return false;
        }
        cnt[small]--;

        op.pb(mp(big, small));
        x = big;
    }

    return true;
}

void solve(void)
{
    scanf("%d", &N);

    a.resize(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());

    bool found = false;
    for (int i = 0; i < 2 * N && !found; i++) {
        found = check(a[2 * N - 1] + a[i]);
    }

    if (found) {
        printf("YES\n%d\n", op[0].first + op[0].second);
        for (int i = 0; i < N; i++) {
            printf("%d %d\n", op[i].first, op[i].second);
        }
    }
    else {
        printf("NO\n");
    }

    // Don't forget to clear the count array
    for (int i = 0; i < 2 * N; i++)
        cnt[a[i]] = 0;

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    cnt.assign(MAXA + 1, 0);

    while (t--)
        solve();

    return 0;
}