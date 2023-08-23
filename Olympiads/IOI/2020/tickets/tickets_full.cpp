#include <bits/stdc++.h>
#include "tickets.h"
#define mp make_pair

using namespace std;

typedef long long ll;

struct Add_Positive {
    int colour;
    int rm;
    int add;
};

int N, M, K;
vector<vector<int>> x;
vector<vector<int>> s;

priority_queue<Add_Positive> q;

vector<vector<int>> pl;
vector<vector<int>> mi;

bool plus_sort(const int& a, const int& b)
{
    return pl[a].size() < pl[b].size();
}

bool operator < (const Add_Positive&a, const Add_Positive& b) {
    if (x[a.colour][a.rm] + x[a.colour][a.add] == x[b.colour][b.add] + x[b.colour][b.rm]) {
        if (a.colour == b.colour)
            return a.rm < b.rm;
        return a.colour < b.colour;
    }

    return x[a.colour][a.rm] + x[a.colour][a.add] < x[b.colour][b.add] + x[b.colour][b.rm];
}

ll find_maximum(int k, vector<vector<int>> X)
{
    N = X.size();
    M = X[0].size();
    x = X;
    K = k;

    s.assign(N, vector<int>(M, -1));

    pl.resize(N);
    mi.resize(N);

    int begin_pos = M - K;
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            ans -= x[i][j];
            mi[i].push_back(j);
        }
        q.push({i, K - 1, M - 1});
    }

    for (int cnt = 0; cnt < K * N / 2; cnt++) {
        // Swap a negative for a positive
        auto cur = q.top();
        q.pop();

        ans += x[cur.colour][cur.add] + x[cur.colour][cur.rm];


        mi[cur.colour].pop_back();
        // To add the plus, the minus must be surely gone
        pl[cur.colour].push_back(cur.add);

        if (!mi[cur.colour].empty()) {
            int i = cur.colour;
            q.push({i, mi[i].back(), mi[i].back() + begin_pos});
        }
    }

    for (int r = 0; r < K; r++) {
        vector<int> p;
        for (int i = 0; i < N; i++)
            p.push_back(i);
        sort(p.begin(), p.end(), plus_sort);

        for (int i = 0; i < N / 2; i++) {
            int v = p[i];
            s[v][mi[v].back()] = r;
            mi[v].pop_back();
        }
        for (int i = N / 2; i < N; i++) {
            int v = p[i];
            s[v][pl[v].back()] = r;
            pl[v].pop_back();
        }
    }

    allocate_tickets(s);

    return ans;
}