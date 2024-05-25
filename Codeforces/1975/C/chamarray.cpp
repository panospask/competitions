#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;

int triplemid(int i)
{
    int f = a[i];
    int s = a[i - 1];
    if (f < s) {
        swap(f, s);
    }

    if (a[i - 2] > s) {
        s = a[i - 2];
        if (f < s) {
            swap(f, s);
        }
    }

    return s;
}

void solve(void)
{
    scanf("%d", &N);
    a.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int ans = 0;
    for (int i = 1; i < N; i++) {
        ans = max(ans, min(a[i], a[i - 1]));
    }
    for (int i = 2; i < N; i++) {
        ans = max(ans, triplemid(i));
    }

    printf("%d\n", ans);
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