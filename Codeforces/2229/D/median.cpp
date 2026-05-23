#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int N;
vector<int> a, b;
vector<int> c, d;
set<int> active;
set<pi> merges;

int val(int i1, int i2) {
    return c[i1] + d[i1] + c[i2] + d[i2];
}

void erase(int i1, int i2) {
    merges.erase({val(i1, i2), i1});
}

void add(int i1, int i2) {
    merges.insert({val(i1, i2), i1});
}

bool test(int x) {
    c.resize(N);
    d.resize(N);
    active.clear();
    merges.clear();
    for (int i = 0; i < N; i++) {
        if (a[i] >= x) {
            c[i] = 0;
        }
        else {
            c[i] = -1;
        }

        if (b[i] >= x) {
            d[i] = 0;
        }
        else {
            d[i] = -1;
        }
        active.insert(i);
        if (i) {
            add(i - 1, i);
        }
    }

    while (active.size() > 1) {
        int i1 = (*merges.begin()).second;
        auto it = active.find(i1);
        int i2 = *(next(it));
        merges.erase(merges.begin());

        int res = val(i1, i2);
        // Remove some connections
        if (it != active.begin()) {
            erase(*prev(it), i1);
        }
        it++;
        if (next(it) != active.end()) {
            erase(i2, *next(it));
        }

        // Update
        active.erase(i2);
        if (res >= -2) {
            d[i1] = 0;
        }
        else {
            d[i1] = -1;
        }
        if (res >= -1) {
            c[i1] = 0;
        }
        else {
            c[i1] = -1;
        }
        
        // Add connections
        it = active.find(i1);
        if (it != active.begin()) {
            add(*prev(it), i1);
        }
        if (next(it) != active.end()) {
            add(i1, *next(it));
        }
    }

    return c[*active.begin()] == 0;
}

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    b.resize(N);
    active.clear();
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        active.insert(i);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
        }
    }

    int l = 0;
    int r = 2 * N + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        if (test(mid)) {
            l = mid;
        }
        else {
            r = mid;
        }
    }

    printf("%d\n", l);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}