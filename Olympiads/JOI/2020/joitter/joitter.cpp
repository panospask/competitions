#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef long long ll;

typedef pair<int, int> pi;

int N, M;
ll ans = 0;
vector<int> rep;
vector<int> sz;

queue<pi> next_merge;

// Connections to and from component with rep i
vector<set<int>> to, from;

// Individuals following i
vector<set<int>> follows;

int tot_size(int a)
{
    return to[a].size() + from[a].size() + follows[a].size();
}

// insert edge from a to b
void insert_edge(int a, int b)
{
    from[a].insert(b);
    to[b].insert(a);

    if (to[a].find(b) != to[a].end())
        next_merge.push(mp(a, b));
}

int find(int a)
{
    if (rep[a] != a) {
        rep[a] = find(rep[a]);
    }

    return rep[a];
}

void unite(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b)
        return;

    // Create a strong link between component a and b
    if (tot_size(a) < tot_size(b))
        swap(a, b);

    // Everyone following A will also follow B
    // and vice versa
    ans += follows[a].size() * (ll)sz[b];
    ans += follows[b].size() * (ll)sz[a];

    for (auto v : follows[b]) {
        if (follows[a].find(v) != follows[a].end()) {
            // We doublecounted
            ans -= sz[a] + sz[b];
        }
        follows[a].insert(v);
    }

    sz[a] += sz[b];
    rep[b] = a;

    to[a].erase(b);
    from[a].erase(b);
    to[b].erase(a);
    from[b].erase(a);

    for (auto c : to[b]) {
        // There is weak edge c -> b
        from[c].erase(b);
        insert_edge(c, a);
    }
    for (auto d : from[b]) {
        // There is weak edge b -> d
        to[d].erase(b);
        insert_edge(a, d);
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    rep.resize(N);
    to.resize(N);
    from.resize(N);
    follows.resize(N);
    sz.assign(N, 1);

    for (int i = 0; i < N; i++) {
        rep[i] = i;
        follows[i].insert(i);
    }

    while (M--) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        int c1 = find(u);
        int c2 = find(v);

        if (c1 == c2 || follows[c2].count(u)) {
            printf("%lld\n", ans);
            continue;
        }

        // u can now follow everyone in c2
        ans += sz[c2];
        follows[c2].insert(u);

        insert_edge(c1, c2);

        while (next_merge.empty() == false) {
            unite(next_merge.front().first, next_merge.front().second);
            next_merge.pop();
        }

        printf("%lld\n", ans);
    }

    return 0;
}