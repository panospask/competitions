#include <bits/stdc++.h>

using namespace std;

const int MAXLOG = 21;

typedef long long ll;

int N, K;
ll M;
vector<int> ancestor[MAXLOG];
vector<ll> pos;
vector<bool> vis;
vector<bool> in_cycle;
vector<int> sz;
stack<int> cur;

int jump(int v, int cnt)
{
    for (int l = 0; l < MAXLOG; l++)
        if (cnt & (1 << l))
            v = ancestor[l][v];

    return v;
}

bool inside(int i, int src)
{
    int l = src - i;
    int r = K - i + 1 + src;

    if (l < 0)
        return false;
    if (r >= N)
        return true;

    return abs(pos[l] - pos[src]) <= abs(pos[r] - pos[src]);
}

void generate_edge(int i)
{
    if (vis[i]) {
        if (sz[i] == -1) {
            sz[i] = 1;
            while (cur.top() != i) {
                sz[i]++;
                in_cycle[cur.top()] = true;
                cur.pop();
            }
            in_cycle[i] = true;
        }

        return;
    }

    vis[i] = true;
    // How much from the are SURELY NOT outside until you choose
    int l = 0;
    int r = K + 1;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (inside(mid, i))
            l = mid;
        else
            r = mid;
    }

    ll v1 = abs(pos[i] - pos[i - l]);
    ll v2 = abs(pos[i] - pos[i + K - l]);

    if (v1 >= v2) {
        ancestor[0][i] = i - l;
    }
    else {
        ancestor[0][i] = i + K - l;
    }

    cur.push(i);
    generate_edge(ancestor[0][i]);
    sz[i] = sz[ancestor[0][i]];
}

int main(void)
{
    scanf("%d %d %lld", &N, &K, &M);

    pos.resize(N);
    vis.resize(N);
    ancestor[0].resize(N);
    sz.assign(N, -1);
    in_cycle.assign(N, false);

    for (int i = 0; i < N; i++)
        scanf("%lld", &pos[i]);

    for (int i = 0; i < N; i++) {
        generate_edge(i);
    }

    for (int up = 1; up < MAXLOG; up++) {
        ancestor[up].resize(N);
        for (int i = 0; i < N; i++)
            ancestor[up][i] = ancestor[up - 1][ancestor[up - 1][i]];
    }

    for (int i = 0; i < N; i++) {
        ll R = M;
        int v = i;
        if (!in_cycle[v]) {
            v = jump(v, min((ll)N, R));
            R -= min((ll)N, R);
        }

        R %= sz[v];

        v = jump(v, R);

        printf("%d ", v + 1);
    }
    printf("\n");

    return 0;
}