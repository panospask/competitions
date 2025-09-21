#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> s;

vector<vector<vector<int>>> dp;

void solve(void) {
    scanf("%d", &N);

    s.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        scanf("%1d", &s[i]);
    }
    
    int ans = 1;
    int prv_left = 1;
    int prv_right = 0;
    int flower = 0;
    for (int i = 1; i <= N; i++) {
        if (s[i]) {
            flower++;
        }
        else {
            int c_left = 0, c_right = 0;
            if ((prv_left && !flower) || (prv_right && flower <= 1)) {
                c_left = 1;
            }
            if ((prv_left) || (prv_right && !flower)) {
                c_right = 1;
            }
            flower = 0;

            prv_left = c_left;
            prv_right = c_right;
        }
    }

    if (ans && (prv_left || (prv_right && !flower))) {
        printf("YES\n");
    }
    else {
        printf("NO\n");
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}