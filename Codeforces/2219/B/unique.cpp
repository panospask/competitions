#include <bits/stdc++.h>

using namespace std;

int N;

int query(vector<int> v) {
    printf("? %d", (int)v.size());
    for (auto p : v) {
        printf(" %d", p);
    }
    printf("\n");

    fflush(stdout);

    int ans;
    scanf("%d", &ans);
    return ans;
}

vector<int> v;

int search(int ub) {
    int l = 0;
    int r = ub;

    while (l + 1 < r) {
        int mid = (l + r) / 2;

        for (int i = 1; i <= mid; i++) {
            v.push_back(i);
        }
        int tot = v.size();
        int res = query(v);
        for (int i = 1; i <= mid; i++) {
            v.pop_back();
        }

        if (res % 2 == tot % 2) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    return r;
}

void solve(void) {
    scanf("%d", &N);

    v.clear();
    int a = search(2 * N + 1);
    v.push_back(a);
    int b = search(a - 1);
    v.push_back(b);
    int c = search(b - 1);

    printf("! %d %d %d\n", c, b, a);
    fflush(stdout);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}