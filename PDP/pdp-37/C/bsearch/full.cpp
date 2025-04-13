#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll INF = 1e15 + 2;

int subtask;

int N, Q;
vector<ll> A;

//value[i]: Value of bsearch(A[i])
vector<int> value;

//before[i]: Value of bsearch(v) for A[i-1] <= v <= A[i]
vector<int> before;

//pref[i]: Sum of bsearch(v) for v <= A[i]
vector<ll> pref;

void process(int l, int r, int counter) {
    if (l > r) {
        before[l] = counter;
        return;
    }
    
    counter++;
    int m = (l + r) / 2;

    value[m] = counter;
    process(m + 1, r, counter);
    process(l, m - 1, counter);
}

// Returns sum of bsearch(v) for i <= v <= j
ll sum(int i, int j) {
    return pref[j] - pref[i] + value[i];
}

ll query(ll l, ll r) {
    // Find first and last elements of the array inside the range
    int a = lower_bound(A.begin(), A.end(), l) - A.begin();
    int b = upper_bound(A.begin(), A.end(), r) - A.begin() - 1;

    if (a == N) {
        return (ll)before[N] * (r - l + 1);
    }
    if (A[a] > r) {
        return (ll)before[a] * (r - l + 1);
    }

    return sum(a, b) + (ll)before[a] * (A[a] - l) + (ll)before[b + 1] * (r - A[b]);
}

int main(void) {
    scanf("%d", &subtask);
    scanf("%d %d", &N, &Q);

    A.resize(N);
    value.resize(N);
    before.resize(N + 1);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &A[i]);
    }

    process(0, N - 1, 0);

    pref.resize(N);
    pref[0] = value[0];
    for (int i = 1; i < N; i++) {
        pref[i] = pref[i - 1] + (ll)before[i] * (A[i] - A[i - 1] - 1) + value[i];
    }

    while (Q--) {
        ll l, r;
        scanf("%lld %lld", &l, &r);
        printf("%lld\n", query(l, r));
    }

    return 0;
}