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

    int M = 0, m = 0;
    for (int i = 1; i < N; i++) {
        if (a[i] > a[M]) {
            M = i;
        }
        if (a[i] < a[m]) {
            m = i;
        }
    }

    if (a[m] == a[M]) {
        printf("No\n");
    }
    else {
        printf("Yes\n");
        for (int i = 0; i < N; i++) {
            if (i != M) {
                printf("1 ");
            }
            else {
                printf("2 ");
            }
        }
        printf("\n");
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