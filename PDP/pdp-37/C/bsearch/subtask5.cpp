#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e15 + 2;

int subtask;

int N, Q;
vector<ll> A;

int bsearch(ll target) {
    int l = 0;
    int r = N - 1;
    int counter = 0;
  
    while (l <= r) {
      ++counter;
      int m = (l+r)/2;
  
      if (A[m] == target) return counter;
      else if (A[m] < target) l = m+1;
      else r = m-1;
    }
  
    return counter;
}

int main(void) {
    scanf("%d", &subtask);
    scanf("%d %d", &N, &Q);

    A.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    // Q is 1
    while (Q--) {
        ll l, r;
        scanf("%lld %lld", &l, &r);

        int a = lower_bound(A.begin(), A.end(), l) - A.begin();
        int b = upper_bound(A.begin(), A.end(), r) - A.begin() - 1;

        ll ans = 0;

        if (a == N) {
            ans = (ll)(r - l + 1) * bsearch(l);
        }   
        else if (A[a] > r) {
            ans = (ll)(r - l + 1) * bsearch(l);
        }     
        else {
            ans = (ll)(A[a] - l) * bsearch(l);
            for (int i = a; i <= b; i++) {
                ans += bsearch(A[i]);
                if (i != b) {
                    ans += (A[i + 1]- A[i] - 1) * bsearch(A[i] + 1);
                }
            }
            ans += (r - A[b]) * bsearch(r);
        }
        printf("%lld\n", ans);
    }

    return 0;
}