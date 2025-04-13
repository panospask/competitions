#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e15 + 2;

int subtask;

int N, Q;
vector<ll> A;
vector<ll> pref;
vector<int> value;

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
    value.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    for (int i = 0; i < N; i++) {
        value[i] = bsearch(A[i]);
    }

    pref.resize(N + 1);
    pref[0] = 0;
    for (int i = 0; i < N; i++) {
        pref[i + 1] = pref[i] + value[i];
    }

    // Calculate the values for outside the array
    int T = (N + 1) / 2;
    int outside = 0;
    while (T) {
        T /= 2;
        outside++;
    }

    while (Q--) {
        ll l, r;
        scanf("%lld %lld", &l, &r);

        int a = lower_bound(A.begin(), A.end(), l) - A.begin();
        int b = upper_bound(A.begin(), A.end(), r) - A.begin() - 1;
        
        ll ans;
        if (a == N) {
            ans = outside * (r - l + 1);
        }
        else if (A[a] > r) {
            ans = outside * (r - l + 1);
        }
        else {
            ans = pref[b + 1] - pref[a];
            ans += outside * ((r - l + 1) - (b - a + 1));
        }

        printf("%lld\n", ans);
    }

    return 0;
}