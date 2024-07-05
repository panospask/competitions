#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> a;
ll S;

int main(void)
{
    scanf("%d %lld", &N, &S);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    ll cursum = 0;
    int r = 0, ans = 0;
    for (int l = 0; l < N; l++) {
        while (r < N && a[r] + cursum <= S) {
            cursum += a[r];
            r++;
        }

        ans = max(ans, r - l);
        cursum -= a[l];
    }

    printf("%d\n", ans);

    return 0;
}