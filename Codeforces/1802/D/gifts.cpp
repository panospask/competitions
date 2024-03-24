#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;

const int BIG = 1e9;

int N;
vector<pi> stores;
multiset<int> options;
int forced;

int find_best(int v)
{
    auto it = options.lower_bound(v);
    int ans = INT_MAX;

    ans = min(ans, abs(forced - v));
    if (it != options.end()) {
        ans = min(ans, abs(max(*it, forced) - v));
    }
    if (it != options.begin()) {
        it--;
        ans = min(ans, abs(v - max(*it, forced)));
    }

    return ans;
}

void transfer(int i)
{
    options.erase(options.find(stores[i].second));
}

void solve(void)
{
    options.clear();
    forced = -BIG;

    scanf("%d", &N);

    stores.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &stores[i].first, &stores[i].second);
        options.insert(stores[i].second);
    }
    sort(stores.rbegin(), stores.rend());

    int ans = INT_MAX;
    int i = 0;
    while (i < N) {
        int m1 = stores[i].first;
        if (i == N - 1 || stores[i + 1].first != stores[i].first) {
            // Special case
            // First remove then calculate

            transfer(i);
            ans = min(ans, find_best(m1));

            forced = max(forced, stores[i].second);
            i++;
        }
        else {
            ans = min(ans, find_best(m1));
            while (i < N && stores[i].first == m1) {
                transfer(i);
                forced = max(forced, stores[i].second);
                i++;
            }
        }
    }

    printf("%d\n", ans);
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}