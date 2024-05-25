#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void)
{
    scanf("%d", &N);
    a.resize(N);

    int prv = -1;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        if (a[i] < prv) {
            cnt++;
        }
            prv = a[i];
    }

    if (cnt >= 2) {
        printf("No\n");
    }
    else if (cnt == 0 || a[0] >= a[N - 1]) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }

    return ;
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