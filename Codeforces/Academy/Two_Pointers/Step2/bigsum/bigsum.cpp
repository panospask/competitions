#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int INF = 1e9;

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
    int ans = INF, r = 0;
    for (int l = 0; l < N; l++) {
        while (r < N && cursum + a[r] < S) {
            cursum += a[r];
            r++;
        }

        if (r < N && cursum + a[r] >= S) {
            ans = min(ans, r - l + 1);
        }
        
        cursum -= a[l];
    }

    if (ans == INF) {
        ans = -1;
    }
    printf("%d\n", ans);

    return 0;
}