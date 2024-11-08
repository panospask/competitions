#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;
vector<int> b;

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    int ans = 0 ;
    vector<int> opt(N);
    for (int i = 0; i < N; i++) {
        opt[i] = INT_MAX;
        for (int j = 0; j < N; j++) {
            opt[i] = min(opt[i], abs(a[i] - b[j]));
        }

        ans = max(ans, opt[i]);
    }

    printf("%d\n", ans);

    return 0;
}