#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, R, K, L;

vector<int> A;
vector<vector<int>> adj_list;

int main(void) {
    scanf("%d %d %d %d", &N, &R, &K, &L);
    R--;

    A.resize(N);
    adj_list.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    ll p1 = 0, p2 = 0;
    ll s1 = 0, s2 = 0;
    ll cur = 0;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        cur += A[i];

        if (i == R) {
            break;
        }

        if (i < K) {
            p1 = max(p1, cur);
        }
        if (i < L) {
            p2 = max(p2, cur);
        }
        if (i < K + L) {
            ans = max(ans, cur);
        }
    }

    cur = 0;
    for (int i = N - 1; i >= 0; i--) {
        cur += A[i];

        if (i == R) {
            break;
        }

        if (N - i - 1 < K) {
            s1 = max(s1, cur);
        }
        if (N - i - 1 < L) {
            s2 = max(s2, cur);
        }
        if (N - i - 1 < K + L) {
            ans = max(ans, cur);
        }
    }

    ans = max(ans, s1 + p2);
    ans = max(ans, s2 + p1);

    printf("%lld\n", ans);

}