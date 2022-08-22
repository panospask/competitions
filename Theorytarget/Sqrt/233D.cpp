#include <bits/stdc++.h>
#define MAXN 50005
// #define DEBUG

using namespace std;

set<int> neigh[MAXN];
bool ison[MAXN];
bool isheavy[MAXN];
set<int> heavy_neigh[MAXN];
int on_friends[MAXN];
int cuttout;
int n, m, q;
int now = 0;

string que[250000];

// RETURNS SIZE
int rnumber(string& s, int start, int& num)
{
    int sz = 0;
    num = 0;
    for (int i = start; !isspace(s[i]) && !(s[i] == '\0'); i++) {
        num *= 10;
        num += s[i] - '0';
        sz++;
    }

    return sz;
}

void make_heavy(int u)
{
    isheavy[u] = true;

    on_friends[u] = 0;
    for (auto v : neigh[u]) {
        if (ison[v])
            on_friends[u]++;
        heavy_neigh[v].insert(u);
    }
}

void make_light(int u)
{
    isheavy[u] = false;
    
    for (auto v : neigh[u]) {
        heavy_neigh[v].erase(u);
    }
}

void online(void)
{
    int u;
    rnumber(que[now], 2, u);

    ison[u] = true;
    for (auto h : heavy_neigh[u])
        on_friends[h]++;
}

void offline(void)
{
    int u;
    rnumber(que[now], 2, u);

    ison[u] = false;
    for (auto h : heavy_neigh[u])
        on_friends[h]--;
}

void add_friend(void)
{
    int u, v;
    int sz = rnumber(que[now], 2, u);
    rnumber(que[now], 2 + sz + 1, v);

    neigh[u].insert(v);
    neigh[v].insert(u);

    if (neigh[u].size() == cuttout)
        make_heavy(u);
    else if (neigh[u].size() > cuttout) {
        if (ison[v]) on_friends[u]++;
        heavy_neigh[v].insert(u);
    }
    if (neigh[v].size() == cuttout)
        make_heavy(v);
    else if (neigh[v].size() > cuttout) {
        if (ison[u]) on_friends[v]++;
        heavy_neigh[u].insert(v);
    }
}

void remove_friend(void)
{
    int u, v;
    int sz = rnumber(que[now], 2, u);
    rnumber(que[now], 2 + sz + 1, v);

    neigh[u].erase(v);
    neigh[v].erase(u);

    if (neigh[u].size() == cuttout -1) {
        make_light(u);
        heavy_neigh[v].erase(u);
    }
    else if (neigh[u].size() >= cuttout) {
        if (ison[v]) on_friends[u]--;
        heavy_neigh[v].erase(u);
    }
    if (neigh[v].size() == cuttout -1) {
        make_light(v);
        heavy_neigh[u].erase(v);
    }
    else if (neigh[v].size() >= cuttout) {
        if (ison[u]) on_friends[v]--;
        heavy_neigh[u].erase(v);
    }
}

int query(void)
{
    int u;
    rnumber(que[now], 2, u);

    if (isheavy[u])
        return on_friends[u];

    int ttl = 0;
    for (auto v : neigh[u])
        ttl += ison[v];

    return ttl;
}   

int main(void)
{
    #ifdef DEBUG
        freopen("233D.in", "r", stdin);
        freopen("233D.out", "w", stdout);
    #endif

    scanf("%d %d %d", &n, &m, &q);

    int n1;
    scanf("%d", &n1);
    int cur;
    for (int i = 0; i < n1; i++) {
        scanf("%d", &cur);
        ison[cur] = true;
    }

    int u, v;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        neigh[u].insert(v);
        neigh[v].insert(u);
    }
    getchar();
    for (int i = 0; i < q; i++) {
        getline(cin, que[i]);
        if (que[i][0] == 'A')
            m++;
    }

    cuttout = (int)sqrt(m);
    for (int i = 1; i <= n; i++)
        if (neigh[i].size() >= cuttout)
            make_heavy(i);

    char type;
    for (now = 0; now < q; now++) {
        switch (que[now][0]) {
            case 'O': online(); break;
            case 'F': offline(); break;
            case 'A': add_friend(); break;
            case 'D': remove_friend(); break;
            default : printf("%d\n", query()); break;
        }
    }

    return 0;
}