#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

const int MAXLOG = 25;

typedef long long ll;
typedef pair<int, ll> pi;

int N;
vector<int> S, P, W, L;

vector<int> dist;
vector<vector<pi>> ancestor;

bool sub1;

void calculate_ancestor(void)
{
    for (int up = 1; up < MAXLOG; up++)
        for (int i = 0; i <= N; i++) {
            int u = ancestor[up - 1][i].first;
            ancestor[up][i].first = ancestor[up - 1][u].first;
            ancestor[up][i].second = ancestor[up - 1][i].second + ancestor[up - 1][u].second;
        }
}

void init(int n, vector<int> s, vector<int> p, vector<int> w, vector<int> l)
{
    N = n;
    S = s;
    P = p;
    W = w;
    L = l;

    sub1 = true;
    for (int i = 1; i < N; i++)
        sub1 = sub1 && S[i] == S[i - 1];

    ancestor.resize(MAXLOG, vector<pi>(N + 1));
    for (int i = 0; i < N; i++)
        ancestor[0][i] = mp(L[i], P[i]);
    ancestor[0][N] = mp(N, 1);
    calculate_ancestor();

    dist.resize(N + 1);
    dist[N] = 0;
    for (int i = N - 1; i >= 0; i--)
        dist[i] = dist[W[i]] + 1;
}

ll simulate(int x, ll z)
{
    if (x == N)
        return z;

    if (z >= S[x])
        return simulate(W[x], z + S[x]);
    else
        return simulate(L[x], z + P[x]);
}

pi get_right_after(int u, int z)
{
    ll r = z;
    for (int up = MAXLOG - 1; up >= 0; up--) {
        ll v = ancestor[up][u].second;
        int nxt = ancestor[up][u].first;
        if (v + r < S[0] && nxt != N) {
            r += v;
            u = nxt;
        }
    }

    r += ancestor[0][u].second;
    u = ancestor[0][u].first;

    return mp(u, r);
}

ll subtask_1(int x, int z)
{
    ll v = z;

    if (z < S[0]) {
        tie(x, v) = get_right_after(x, z);
    }

    v += (ll)dist[x] * S[0];

    return v;
}

ll simulate(int x, int z)
{
    if (sub1)
        return subtask_1(x, z);

    return simulate(x, (ll)z);
}