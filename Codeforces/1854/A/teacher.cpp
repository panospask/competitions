#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;
void solve(void)
{
    scanf("%d", &N);

    a.resize(N + 1);
    for (int i = 1; i <= N; i++)
        scanf("%d", &a[i]);

    bool swap = false;
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (a[i] == i) {
            cnt++;
        }
    }

    printf("%d\n", cnt / 2 + cnt % 2);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
        solve();
}