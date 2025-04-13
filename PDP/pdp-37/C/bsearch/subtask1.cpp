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

    while (Q--) {
        ll l, r;
        scanf("%lld %lld", &l, &r);

        ll ans = 0;
        for (int i = l; i <= r; i++) {
            ans += bsearch(i);
        }

        printf("%lld\n", ans);
    }

    return 0;
}