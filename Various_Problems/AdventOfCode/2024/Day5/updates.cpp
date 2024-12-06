#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MAXN = 101;

vector<int> cnt;
vector<bool> used;
vector<vector<int>> after;

bool correct(vector<int> update)
{
    used.assign(MAXN, false);

    for (auto id : update) {
        for (auto v : after[id]) {
            if (used[v]) {
                return false;
            }
        }

        used[id] = true;
    }

    return true;
}

void fix(vector<int>& update)
{
    cnt.assign(MAXN, 0);
    used.assign(MAXN, false);

    vector<int> l = update;

    for (auto u : l) {
        used[u] = true;
    }
    for (auto u : l) {
        for (auto v : after[u]) {
            if (used[v]) {
                cnt[v]++;
            }
        }
    }

    queue<int> q;
    for (auto u : l) {
        if (cnt[u] == 0) {
            q.push(u);
        }
    }

    update.clear();
    while(!q.empty()) {
        int u = q.front();
        q.pop();

        update.pb(u);

        for (auto v : after[u]) {
            if (used[v]) {
                cnt[v]--;
                if (cnt[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
}

int main(void)
{
    freopen("updates.in", "r", stdin);
    freopen("updates.out", "w", stdout);

    after.resize(MAXN);

    int c = 0;
    while ((c = getchar()) != '\n') {
        ungetc(c, stdin);

        int u, v;
        scanf("%d|%d", &u, &v);
        c = getchar();

        after[u].pb(v);
    }

    int ans = 0;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        int p;
        vector<int> cur;
        scanf("%d", &p);
        cur.pb(p);

        while ((c = getchar()) == ',') {
            scanf("%d", &p);
            cur.pb(p);
        }

        if (!correct(cur)) {
            fix(cur);
            ans += cur[cur.size() / 2];
        }
    }

    printf("%d\n", ans);

    return 0;
}