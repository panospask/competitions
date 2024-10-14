#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 1e9 + 7;
const int MAXV = 2e5;

int t;
vector<ll> twopow;
vector<int> A, B;

void solve(int i)
{
    int n = A[i], k = B[i];
    scanf("%d %d", &n, &k);

    if (n == k) {
        printf("1\n");
    }
    else {
        printf("%lld\n", twopow[k]);
    }
}

int main(void)
{
    scanf("%d", &t);

    twopow.resize(MAXV + 1);
    A.resize(t);
    B.resize(t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < t; i++) {
        scanf("%d", &B[i]);
    }

    twopow[0] = 1;
    for (int i = 1; i <= MAXV; i++) {
        twopow[i] = twopow[i - 1] * 2 % MOD;
    }

    for (int i = 0; i < t; i++) {
        solve(i);
    }

    return 0;
}