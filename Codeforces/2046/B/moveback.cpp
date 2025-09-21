#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e9 + 1;

int N;
vector<int> a;
vector<int> result;
multiset<int> skipped;

void solve(void) {
    scanf("%d", &N);

    a.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    result.clear();
    skipped.clear();
    skipped.insert(INF);

    for (int i = 0; i < N; i++) {
        while (!result.empty() && result.back() > a[i]) {
            skipped.insert(result.back() + 1);
            result.pop_back();
        }
        if (*skipped.begin() >= a[i]) {
            result.pb(a[i]);
        }
        else {
            skipped.insert(a[i] + 1);
        }
    }

    while (*skipped.begin() != INF) {
        result.pb(*skipped.begin());
        skipped.erase(skipped.begin());
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    return;
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }
}