#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Component {
    // Classic [l, r)
    int l, r;
    bool ineven = false;
    bool inodd = false;
};

bool operator < (Component a, Component b) {
    return a.l < b.l;
}

int N;

map<int, vector<int>> values;
set<Component> components;

int maxComponents = 0;
int reduceMaxComponents = 0;
int total = 0;

Component merge(const Component a, const Component b) {
    // We assume that a.r == b.l

    Component c;
    c.l = a.l;
    c.r = b.r;

    bool bodd = b.inodd;
    bool beven = b.ineven;
    int a_size = a.r - a.l;
    if (a_size % 2 == 1) {
        swap(bodd, beven);
    }
    c.ineven = a.ineven || beven;
    c.inodd = a.inodd || bodd;

    return c;
}

void modify(Component a, int m) {
    int size = a.r - a.l;
    total += ((size + 1) / 2) * m;
    if (a.inodd || a.ineven) {
        maxComponents += 1 * m;
        if (size % 2 && a.inodd == false) {
            reduceMaxComponents += 1 * m;
        }
    }
}

void insert_component(Component cur) {
    auto it = components.lower_bound(cur);
    if (it != components.end() && (*it).l == cur.r) {
        // Perform merge
        modify(*it, -1);
        cur = merge(cur, *it);
        components.erase(it);
    }

    it = components.lower_bound(cur);
    if (it != components.begin()) {
        it = prev(it);
        if ((*it).r == cur.l) {
            modify(*it, -1);
            cur = merge(*it, cur);
            components.erase(it);
        }
    }

    modify(cur, 1);
    components.insert(cur);
}

void solve(void) {
    scanf("%d", &N);

    components.clear();
    maxComponents = 0;
    reduceMaxComponents = 0;
    total = 0;
    values.clear();

    int mx = 0;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        mx = max(mx, x);
        values[x].push_back(i);
    }

    ll ans = 0;
    for (auto it = values.rbegin(); it != values.rend(); it++) {
        vector<int> pos = (*it).second;
        int v = (*it).first;

        for (auto i : pos) {
            Component cur;
            cur.l = i; cur.r = i + 1;
            cur.ineven = false;
            cur.inodd = (v == mx);

            insert_component(cur);
        }

        ll res = (ll)mx + v + total;
        if (maxComponents == reduceMaxComponents) {
            res--;
        }
        ans = max(ans, res);
    }

    printf("%lld\n", ans);
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}