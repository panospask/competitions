#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> s, t;

int main(void) {
    scanf("%d", &N);
    
    s.resize(N);
    t.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%1d", &s[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%1d", &t[i]);
    }


    int ans = 0;
    int maxpref = 0, minpref = 0;
    int p = 0;

    for (int i = 0; i <  N; i++) {
        if (s[i] == t[i]) {
            continue;
        }

        p = p + (s[i] == 1 ? 1 : -1);
        ans = max(ans, abs(p - minpref));
        ans = max(ans, abs(p - maxpref));

        minpref = min(p, minpref);
        maxpref = max(p, maxpref);
    }

    if (p == 0) {
        printf("%d\n", ans);
    }
    else {
        printf("-1\n");
    }
}