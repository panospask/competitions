#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());
    int known = 0;
    int p = 0;
    int cnt = 0;
    int prv = -1;
    bool found = false;

    while (p < a.size() && !found) {
        if (a[p] - prv > 1) {
            known = 0;
        }
        
        cnt = 1;
        while (p + 1 < a.size() && a[p + 1] == a[p]) {
            cnt++;
            p++;
        }

        if (cnt >= 4) {
            found = true;
        }
        else if (cnt >= 2) {
            if (known) {
                found = true;
            }
            else {
                known = 1;
            }
        }

        prv = a[p];
        p++;
    }

    if (found) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
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