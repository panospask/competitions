#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M, Q;
vector<vector<int>> adj_list;
vector<vector<int>> revlist;

// winner[u][s]: If player s plays at u, who wins? 
vector<vector<int>> winner;
// cnt[u][s]: If player s plays at u, how many moves lead to the winning combo?
vector<vector<int>> cnt;

void update(int x) {
    queue<pi> q;
    if (winner[x][0] == 0) {
        winner[x][0] = 1;
        q.push(mp(x, 0));
    }
    if (winner[x][1] == 0) {
        winner[x][1] = 1;
        q.push(mp(x, 1));
    }

    while (!q.empty()) {
        // We know river wins in the state (u, s)
        int u, s;
        tie(u, s) = q.front();
        q.pop();

        for (auto v : revlist[u]) {
            if (winner[v][!s]) {
                continue;
            }
            
            if (!s == 1) {
                // River can choose to come here
                winner[v][!s] = 1;
                q.push(mp(v, !s));
            }
            else {
                // Cry just loses an option
                cnt[v][!s]--;
                if (cnt[v][!s] == 0) {
                    winner[v][!s] = 1;
                    q.push(mp(v, !s));
                }
            }
        }
    }
}

void solve(void) {
    scanf("%d %d %d", &N, &M, &Q);

    adj_list.assign(N, vector<int>());
    revlist.assign(N, vector<int>());

    winner.assign(N, vector<int>(2, 0));
    cnt.assign(N, vector<int>(2, 0));

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        revlist[v].pb(u);
    }

    for (int i = 0; i < N; i++) {
        cnt[i][0] = adj_list[i].size();
    }

    while (Q--) {
        int type, x;
        scanf("%d %d", &type, &x);
        x--;
        if (type == 1) {
            update(x);
        }
        else {
            if (winner[x][0] == 0) {
                printf("YES\n");
            }
            else {
                printf("NO\n");
            }
        }
    }
}

int main(void) {
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}