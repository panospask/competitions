#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, K;
vector<bool> unlimited;
vector<int> c;
vector<int> need_calculate;
vector<vector<int>> contribute_to;
vector<vector<int>> mix_requirements;
vector<ll> minimum_cost;

void solve(void)
{
    c.clear();
    need_calculate.clear();
    contribute_to.clear();
    mix_requirements.clear();
    minimum_cost.clear();

    scanf("%d %d", &N, &K);

    unlimited.assign(N, false);
    c.resize(N);
    contribute_to.resize(N);
    minimum_cost.resize(N);
    mix_requirements.resize(N);
    need_calculate.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 0; i < K; i++) {
        int pos;
        scanf("%d", &pos);
        pos--;

        unlimited[pos] = true;
    }

    queue<int> curcalc;
    for (int i = 0; i < N; i++) {
        int m;
        scanf("%d", &m);
        mix_requirements[i].resize(m);
        need_calculate[i] = m;

        for (int j = 0; j < m; j++) {
            int num;
            scanf("%d", &num);
            num--;
            mix_requirements[i][j] = num;
            contribute_to[num].push_back(i);
        }

        if (!m)
            curcalc.push(i);
    }

    while (!curcalc.empty()) {
        int v = curcalc.front();
        curcalc.pop();

        // Remove from all necessary
        for (auto u : contribute_to[v]) {
            need_calculate[u]--;
            if (!need_calculate[u])
                curcalc.push(u);
        }

        // Calculate optimal thing
        minimum_cost[v] = c[v];
        if (unlimited[v]) {
            minimum_cost[v] = 0;
        }
        else if (mix_requirements[v].size() != 0) {
            ll a = 0;
            for (auto u : mix_requirements[v])
                a += minimum_cost[u];
            minimum_cost[v] = min(minimum_cost[v], a);
        }
    }

    for (int i = 0; i < N; i++)
        printf("%lld ", minimum_cost[i]);
    printf("\n");
    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();
}