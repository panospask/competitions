#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, K, Q;
vector<int> A; 
vector<pi> minqueries;
vector<pi> mexqueries;

vector<bool> minrange;
vector<bool> mexrange;

pi intersect(pi a, pi b) {
    return mp(max(a.first, b.first), min(a.second, b.second));
}

bool contain(int v, pi a) {
    return a.first <= v && v <= a.second;
}

bool rangesort(pi a, pi b) {
    return a.second < b.second;
}

void solve(void) {
    scanf("%d %d %d", &N, &K, &Q);

    A.assign(N, N);
    minrange.assign(N, false);
    mexrange.assign(N, false);

    minqueries.clear();
    mexqueries.clear();

    for (int i = 0; i < Q; i++) {
        int c, l, r;
        scanf("%d %d %d", &c, &l, &r);
        l--; r--;

        if (c == 1) {
            minqueries.pb(mp(l, r));
        }
        else {
            mexqueries.pb(mp(l, r));
        }
    }

    for (int i = 0; i < minqueries.size(); i++) {
        for (int j = minqueries[i].first; j <= minqueries[i].second; j++) {
            minrange[j] = true;
        }
    }

    for (int i = 0; i < mexqueries.size(); i++) {
        for (int j = mexqueries[i].first; j <= mexqueries[i].second; j++) {
            mexrange[j] = true;
        }
    }

    sort(mexqueries.begin(), mexqueries.end(), rangesort);

    if (mexqueries.size() == 0) {
        mexqueries.pb(mp(0, -1));
    }

    int idx = 0;
    for (int j = mexqueries[0].second; j >= mexqueries[0].first; j--) {
        if (idx == K || minrange[j]) {
            continue;
        }
        
        A[j] = idx;
        idx++;
    }

    int l1 = mexqueries[0].first, r1 = mexqueries[0].second;
    
    for (int i = 1; i < mexqueries.size(); i++) {
        int l2 = mexqueries[i].first, r2 = mexqueries[i].second;

        int j2 = r2;

        for (int j1 = l1; j1 <= min(r1, l2 - 1); j1++) {
            if (A[j1] != N) {
                // We need this

                while (A[j2] != N || minrange[j2]) {
                    j2--;
                }

                A[j2] = A[j1];
            }
        }

        if (l2 > l1) {
            l1 = l2;
            r1 = r2;
        }
    }

    for (int i = 0; i < minqueries.size(); i++) {
        int v = minqueries[i].first;

        while (mexrange[v]) {
            v++;
        }

        A[v] = K;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(void) {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
}