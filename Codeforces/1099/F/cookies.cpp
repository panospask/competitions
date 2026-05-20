#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;

int N;
ll T;
vector<int> t, x, l, p;
vector<vector<int>> kids;

ll cost = 0;
ll gain = 0;
ll ans = 0;
map<ll, int> good;

vector<vector<pli>> removed;

vector<int> win;

struct SegTree {
    vector<pli> tree;
};

void take(ll v, int c, map<ll, int>& m) {
    m[v] -= c;
    if (m[v] == 0) {
        m.erase(v);
    }
}

// Ensure rollback
void insert(ll v, int c) {
    // Check if it improves upon anything good

    good[v] += c;
    cost += v * c;
    gain += c;

    removed.push_back({});

    while (cost > T) {
        auto cur = *good.rbegin();
        int cnt = (cost - T + cur.first - 1) / cur.first;
        
        if (cnt > cur.second) {
            cnt = cur.second;
        }

        take(cur.first, cnt, good);
        cost -= cur.first * cnt;
        gain -= cnt;

        removed.back().push_back({cur.first, cnt});
    }
}

void rollback(ll v, int c) {
    cost -= v * c;
    take(v, c, good);
    gain -= c;

    for (auto [v1, cnt] : removed.back()) {
        cost += v1 * cnt;
        good[v1] += cnt;
        gain += cnt;
    }
    removed.pop_back();
}

void dfs(int node) {
    if (T < 0) {
        return;
    }
    insert(t[node], x[node]);
    ans = max(ans, gain);

    win[node] = gain;

    for (auto kid : kids[node]) {
        T -= 2 * l[kid];
        dfs(kid);
        T += 2 * l[kid];
    }

    rollback(t[node], x[node]);
}

void dfs2(int node) {
    vector<int> v;
    for (auto kid : kids[node]) {
        dfs2(kid);
        v.push_back(win[kid]);
    }
    sort(v.rbegin(), v.rend());

    if (v.size() >= 2) {
        if (node) {
            win[node] = max(win[node], v[1]);
        }
    }
    if (node == 0 && v.size() >= 1) {
        win[node] = max(win[node], v[0]);
    }
}

int main(void) {
    scanf("%d %lld", &N, &T);

    x.resize(N);
    t.resize(N);
    p.resize(N);
    l.resize(N);
    win.resize(N);
    kids.resize(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &x[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 1; i < N; i++) {
        scanf("%d %d", &p[i], &l[i]);
        p[i]--;
        kids[p[i]].push_back(i);
    }

    dfs(0);
    dfs2(0);

    printf("%d\n", win[0]);
}