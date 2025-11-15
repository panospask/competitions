#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

int N, M;

multiset<int> swords;
vector<pi> monsters;
vector<pi> good, bad;

int ans = 0;

void eliminate(pi m) {
    int b, c;
    tie(b, c) = m;

    auto it = swords.lower_bound(b);
    if (it == swords.end()) {
        return;
    }

    ans++;
    int v = *it;
    swords.erase(it);

    if (c != 0) {
        swords.insert(max(v, c));
    }
}

void solve(void) {
    scanf("%d %d", &N, &M);

    ans = 0;
    good.clear();
    bad.clear();
    swords.clear();
    monsters.resize(M);

    for (int i = 0; i < N; i++) {
        int s;
        scanf("%d", &s);
    
        swords.insert(s);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &monsters[i].first);
    }
    for (int i = 0; i < M; i++) {
        scanf("%d", &monsters[i].second);

        if (monsters[i].second == 0) {
            bad.push_back(monsters[i]);
        } 
        else {
            good.push_back(monsters[i]);
        }
    }

    sort(good.begin(), good.end());
    sort(bad.begin(), bad.end());

    for (int i = 0; i < good.size(); i++) {
        eliminate(good[i]);
    }
    for (int i = 0; i < bad.size(); i++) {
        eliminate(bad[i]);
    }
    
    printf("%d\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}