#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

int N;
vector<int> x;

void solve(void) {
    scanf("%d", &N);

    x.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }

    int ans = 0;
    int Rmin = 0;
    int Rmax = INF;
    for (int i = 0; i < N - 1; i++) {
        int d = x[i + 1] - x[i];
        
        if (Rmin >= d) {
            // We have to cancel at least one
            Rmin = 0;
            Rmax = d;
        }
        else {
            ans++;
            int NewMin = max(0, d - Rmax);
            int NewMax = d - Rmin;
            Rmin = NewMin;
            Rmax = NewMax;
        }
    }

    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        solve();
    }
}