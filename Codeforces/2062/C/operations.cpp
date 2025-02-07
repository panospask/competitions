#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll calculate(vector<ll>& A, bool first)
{
    if (A.size() == 0) {
        return LLONG_MIN;
    }

    int N = A.size();
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        sum += A[i];
    }
    
    // Create the difference array of A
    vector<ll> diff(N - 1);
    for (int i = 0; i < N - 1; i++) {
        diff[i] = A[i + 1] - A[i];
    }

    if (!first) {
        sum = abs(sum);
    }
    return max(sum, calculate(diff, false));
}

void solve(void)
{
    int N;
    vector<ll> A;

    scanf("%d", &N);
    A.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    printf("%lld\n", calculate(A, true)); 
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