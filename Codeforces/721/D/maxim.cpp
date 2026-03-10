#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

int N, K, X;
vector<ll> A;
set<pli> res;

void solve(void) {
    scanf("%d %d %d", &N, &K, &X);

    A.resize(N);
    res.clear();

    int neg = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
        res.insert({abs(A[i]), i});
        
        neg += (A[i] < 0);
    }

    // Deal with 0's
    while ((*res.begin()).first == 0 && K > 0) {
        int idx = (*res.begin()).second;
        res.erase(res.begin());
        if (neg % 2 == 0) {
            A[idx] -= X;
            neg++;
        }
        else {
            A[idx] += X;
        }
        res.insert({abs(A[idx]), idx});
        K--;
    }

    if (neg % 2 == 0) {
        int idx = (*res.begin()).second;
        res.erase(res.begin());
        int prv = A[idx];
        while (A[idx] * prv >= 0 && K > 0) {
            if (prv > 0) {
                A[idx] -= X;
            }
            else {
                A[idx] += X;
            }
            K--;
        }
        res.insert({abs(A[idx]), idx});
    }
    for (int t = 0; t < K; t++) {
        ll v;
        int i;
        tie(v, i) = *res.begin();
        res.erase(res.begin());
        v += X;
        if (A[i] < 0) {
            A[i] -= X;           
        }
        else {
            A[i] += X;
        }
        res.insert({v, i});
    }

    for (int i = 0; i < N; i++) {
        printf("%lld ", A[i]);
    }
    printf("\n");
}

int main(void) {
    int t = 1;

    while (t--) {
        solve();
    }
}