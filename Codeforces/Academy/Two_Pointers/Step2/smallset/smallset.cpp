#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXV = 1e5;

int N, K;
vector<int> a;
vector<int> cnt;

int main(void)
{
    scanf("%d %d", &N, &K);

    a.resize(N);
    cnt.assign(MAXV + 1, 0);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    int num = 0, r = -1;
    ll ans = 0;
    for (int l = 0; l < N; l++) {
        while (num <= K && r < N) {            
            r++;
            if (r == N) {
                break;
            }

            cnt[a[r]]++;
            if (cnt[a[r]] == 1) {
                num++;
            }
        }

        // Calculate all segments that start on l and have at most K unique elements
        ans += r - l;

        cnt[a[l]]--;
        if (cnt[a[l]] == 0) {
            num--;
        }
    }

    printf("%lld\n", ans);

    return 0;
}