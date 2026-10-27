#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

int N, M;
vector<set<pi>> adj_list;
vector<int> cnt;

int main(void) {
    scanf("%d", &N);

    adj_list.resize(N);
    cnt.assign(N, 0);
    for (int i = 0; i < N - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].insert({v, w});
        adj_list[v].insert({u, w});
    }

    scanf("%d", &M);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;
        cnt[u]++;
        cnt[v]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (adj_list[i].size() == 1) {
            q.push(i);
        }
    }

    ll ans = 0;
    int rem = N;
    while (rem > 1) {
        int u = q.front();
        q.pop();

        int p, w;
        tie(p, w) = *adj_list[u].begin();

        if (cnt[u] % 2 == 1) {
            // Take the edge
            cnt[p]++;
            ans += w;
        }
        // Remove from parent
        adj_list[p].erase({u, w});
        if (adj_list[p].size() == 1) {
            q.push(p);
        }

        rem--;
    }

    printf("%lld\n", ans);
}