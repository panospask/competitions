#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N, M;
vector<pi> cameras;
vector<pi> ans;

vector<vector<int>> events1;
vector<vector<int>> events2;

map<ll, vector<pi>> covered;

vector<ll> value;

// Add the range [a, b] to the answer (assuming gap)
void add(int a, int b) {
    if (b < a) {
        // We're not needed
        return;
    }

    int i = 1;
    int cur = 2;
    int L = b - (a - 1);
    ans.push_back({i + (a - 1), i + (a - 1)});
    while (i <= L) {
        ans.back().second = i + (a - 1);
        if (i % 2 == 0) {
            cur = 0;
            ans.push_back({i + (a - 1), i + (a - 1)});
        }
        i++;
    }
}

void solve(void) {
    scanf("%d %d", &N, &M);

    ans.clear();
    cameras.resize(M);
    value.assign(M, 0);
    covered.clear();
    events1.assign(N, vector<int>());
    events2.assign(N, vector<int>());
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &cameras[i].first, &cameras[i].second);
        cameras[i].first--;
        cameras[i].second--;
        
        events1[cameras[i].first].push_back(i);
        events2[cameras[i].second].push_back(i);
    }
    for (int i = 0; i < M; i++) {
        value[i] = (ll)RAND_MAX * rand() + rand();
    }

    ll prev = -1;
    ll cur = 0;
    int s = -1;
    for (int i = 0; i < N; i++) {
        // Process events
        for (auto x : events1[i]) {
            cur ^= value[x];
        }

        if (cur != prev) {
            if (i) {
                covered[prev].push_back({s, i - 1});
            }
            s = i;
        }
        prev = cur;

        for (auto x : events2[i]) {
            cur ^= value[x];
        }
    }
    covered[prev].push_back({s, N - 1});

    for (auto [mask, v] : covered) {
        // Did I use the "blank"?
        int used = 0;
        for (auto r : v) {
            int len = r.second - r.first + 1;
            if (!used && (len % 2 == 0 || len == 1)) {
                // Use it and skip a number
                add(r.first + 1, r.second);
                used = 1;
            }
            else {
                // No point in skips
                add(r.first, r.second);
            }
        }
    }
    
    
    printf("%d\n", (int)ans.size());
    for (auto [a, b] : ans) {
        printf("%d %d\n", a + 1, b + 1);
    }
}

int main(void) {
    int t;
    scanf("%d", &t);
    srand(time(NULL));

    while (t--) {
        solve();
    }
}