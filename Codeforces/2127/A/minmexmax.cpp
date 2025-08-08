#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void) {
    scanf("%d", &N);
    a.resize(N);

    int num = -1;
    bool good = true;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);

        if (a[i] != -1) {
            if (num != -1) {
                good = good && (a[i] == num);
            }
            else {
                num = a[i];
            }
        }
    }

    if (!good || num == 0) {
        printf("NO\n");
    }
    else {
        printf("YES\n");
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