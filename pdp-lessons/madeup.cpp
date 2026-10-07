#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N;
vector<int> A, B, C;

int main(void) {
    scanf("%d", &N);

    A.resize(N + 1);
    B.resize(N + 1);
    C.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N;i ++) {
        scanf("%d", &B[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &C[i]);
    }

    map<int, int> m1, m2;

    for (int i = 1; i <= N; i++) {
        m1[A[i]]++;
    }
    for (int k = 1; k <= N; k++) {
        m2[C[k]]++;
    }

    ll total = 0;
    for (int j = 1; j <= N; j++) {
        int v = B[j];
        ll current = (ll)m1[v] * m2[j];
        total += current;
    }

    printf("%lld\n", total);
}