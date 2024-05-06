#include <bits/stdc++.h>

using namespace std;

int N, Q;
vector<int> a;
vector<int> pref;
vector<int> vals;
vector<vector<int>> idx;

int code(int a)
{
    return lower_bound(vals.begin(), vals.end(), a) - vals.begin();
}

void solve(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    pref.resize(N + 1);

    pref[0] = 0;
    vals.push_back(0);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        pref[i + 1] = a[i] ^ pref[i];
        vals.push_back(pref[i + 1]);
    }

    sort(vals.begin(), vals.end());
    vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

    idx.assign(vals.size(), vector<int>());
    for (int i = 0; i <= N; i++) {
        idx[code(pref[i])].push_back(i);
    }

    while (Q--) {
        int l, r;
        scanf("%d %d", &l, &r);

        int c1 = code(pref[l - 1]);
        int c2 = code(pref[r]);

        int a1 = idx[c2][lower_bound(idx[c2].begin(), idx[c2].end(), l) - idx[c2].begin()];
        int a2 = idx[c1][upper_bound(idx[c1].begin(), idx[c1].end(), r) - idx[c1].begin() - 1];

        if (a1 <= a2) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }
    printf("\n");

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}