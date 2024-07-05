#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e18 + 1;

int N;
ll K;
vector<ll> a;
deque<ll> big, small;

int main(void)
{
    scanf("%d %lld", &N, &K);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    big.push_back(0);
    small.push_back(INF);

    ll ans = 0;
    int r = -1;
    for (int l = 0; l < N; l++) {
        while (r < N && big.front() - small.front() <= K) {
            r++;
            if (r == N) {
                break;
            }

            while (!big.empty() && big.back() < a[r]) {
                big.pop_back();
            }
            big.push_back(a[r]);
            while (!small.empty() && small.back() > a[r]) {
                small.pop_back();
            }
            small.push_back(a[r]);
        }

        // Count segments starting at l
        ans += r - l;

        if (a[l] == big.front()) {
            big.pop_front();
            if (big.empty()) {
                big.push_back(0);
            }
        }
        if (a[l] == small.front()) {
            small.pop_front();
            if (small.empty()) {
                small.push_back(INF);
            }
        }
    }

    printf("%lld\n", ans);

    return 0;
}