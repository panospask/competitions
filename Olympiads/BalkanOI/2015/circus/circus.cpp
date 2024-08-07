#include <bits/stdc++.h>
#include "circus.h"
#define mp make_pair

using namespace std;

const int INF = 1e9 + 1;

typedef pair<int, int> pi;

struct State {
    int node;
    bool forward;
    int minlen;
};

bool operator > (const State& a, const State& b)
{
    return a.minlen > b.minlen;
}

int N, M;
vector<int> p;

// nxt[i]: Next rope in the path from p[i] to M
vector<vector<int>> nxt;

/* minlen[i][fw]:
 * The minimum length of rope needed in position p[i] to reach M.
 * fw is a boolean variable denoting if the first step is forwards or backwards
 */
vector<vector<int>> minlen;
vector<int> tot;

/* change[i][fw]:
 * The maximum/minimum position at which i becomes a better choice than i - 1
 */
vector<vector<int>> change;

priority_queue<State, vector<State>, greater<State>> q;

// Test if j can become the optimal next rope in the path from p[i] to M
void test(int i, int j)
{
    if (i < 0 || i >= N) {
        return;
    }

    bool fw = (i < j);

    if (abs(p[i] - p[j]) >= tot[j] && abs(p[i] - p[j]) < minlen[i][fw]) {
        minlen[i][fw] = abs(p[i] - p[j]);
        nxt[i][fw] = j;

        q.push({i, fw, minlen[i][fw]});
    }

    // If test fails then j cannot be used as a first step anymore(in the given direction)
}

void init(int n, int m, int P[]){
    N = n;
    M = m;

    p.resize(N + 1);
    minlen.assign(N + 1, vector<int>(2, INF));
    nxt.resize(N + 1, vector<int>(2));
    tot.assign(N + 1, INF);
    change.resize(2, vector<int>(N + 1));

    for (int i = 0; i < N; i++) {
        p[i] = P[i];
    }
    p[N] = M;
    minlen[N][1] = 0;
    nxt[N][1] = N;

    sort(p.begin(), p.end());

    q.push({N, true, 0});

    while (!q.empty()) {
        int i, d;
        bool fw;
        auto res = q.top();
        q.pop();

        i = res.node;
        d = res.minlen;
        fw = res.forward;

        if (minlen[i][fw] < d) {
            continue;
        }

        tot[i] = min(tot[i], minlen[i][fw]);

        // Advance nxt[i][fw]
        int j;
        if (fw) {
            // Move more back
            j = i - 1;
        }
        else {
            // Move more front
            j = i + 1;
        }
        test(j, nxt[i][fw]);

        if (minlen[i][fw] != tot[i]) {
            continue;
        }

        // Advance i
        int p_l = upper_bound(p.begin(), p.end(), p[i] - tot[i]) - p.begin() - 1;
        int p_r = lower_bound(p.begin(), p.end(), p[i] + tot[i]) - p.begin();

        test(p_l, i);
        test(p_r, i);
    }

    // Calculate the optimal first step forwards and backwards for each possile position
    for (int i = 0; i <= N; i++) {
        change[false][i] = p[i] + tot[i];
        change[true][i] = p[i] - tot[i];
    }
    for (int i = 1; i <= N; i++) {
        // If a rope further back allows a later forward step, propagate it
        change[true][i] = max(change[true][i], change[true][i - 1]);
    }
    for (int i = N - 1; i >= 0; i--) {
        // If a rope further font allows an earlier backward step, propagate it
        change[false][i] = min(change[false][i], change[false][i + 1]);
    }
}

int minLength(int D) {
    // Find the positions that allow the best possible forward and backward steps
    int f_pos = lower_bound(change[true].begin(), change[true].end(), D) - change[true].begin();
    int b_pos = upper_bound(change[false].begin(), change[false].end(), D) - change[false].begin() - 1;

    int ans = p[f_pos] - D;
    if (b_pos >= 0) {
        ans = min(ans, D - p[b_pos]);
    }

    return ans;
}