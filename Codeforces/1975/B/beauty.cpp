#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

void solve(void)
{
    scanf("%d", &N);
    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    sort(a.begin(), a.end());

    int f = a[0];
    int s = -1;
    bool good = true;
    for (int i = 1; i < N; i++) {
        if (a[i] % f != 0) {
            if (s == -1) {
                s = a[i];
            }
            else if (a[i] % s != 0) {
                good = false;
            }
        }
    }

    if (good) {
        printf("Yes\n");
    }
    else {
        printf("No\n");
    }
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}