#include <bits/stdc++.h>
#include "crocodile.h"
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const ll INF = 1e17;

vector<vector<ll>> plan;
vector<vector<pi>> adj_list;
vector<bool> visited;

int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
{
    adj_list.resize(N);

    for (int i = 0; i < M; i++) {
        adj_list[R[i][0]].pb(mp(R[i][1], L[i]));
        adj_list[R[i][1]].pb(mp(R[i][0], L[i]));
    }

    plan.assign(N, vector<ll>(2, INF));
    visited.assign(N, false);

    priority_queue<pi, vector<pi>, greater<pi>> q;

    for (int i = 0; i < K; i++) {
        plan[P[i]][0] = plan[P[i]][1] = 0;
        q.push(mp(0, P[i]));
    }

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        for (auto u : adj_list[v]) {
            ll curd = plan[v][1] + u.s;

            if (plan[u.f][0] > curd) {
                plan[u.f][1] = plan[u.f][0];
                plan[u.f][0] = curd;

                if (plan[u.f][1] != INF)
                    q.push(mp(plan[u.f][1], u.f));
            }
            else if (plan[u.f][1] > curd) {
                plan[u.f][1] = curd;

                q.push(mp(plan[u.f][1], u.f));
            }
        }
    }

    return plan[0][1];
}