#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

int N;
vector<pi> edges;
vector<int> p;

void solve(void) {
    scanf("%d", &N);

    p.resize(N);
    edges.clear();

    for (int i = 0; i < N; i++) {
        scanf("%d", &p[i]);
    }

    stack<int> s;
    s.push(N + 1);


    for (int i = 0; i < N; i++) {
        int mn = p[i];

        while (s.top() < p[i]) {
            mn = min(mn, s.top());
            edges.pb(mp(s.top(), p[i]));
            s.pop();
        }

        s.push(mn);
    }

    if (edges.size() != N - 1) {
        printf("No\n");
        return;
    }

    printf("Yes\n");
    for (int i = 0; i < N - 1; i++) {
        printf("%d %d\n", edges[i].first, edges[i].second);
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