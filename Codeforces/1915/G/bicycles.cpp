#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

struct State {
    int city;
    ll time;
    int slow;

    bool wins(const State& b) {
        return this->time <= b.time && this->slow <= b.slow;
    }
};
const State BAD = {-1, INT_MAX, INT_MAX};

bool operator < (const State& a, const State& b)
{
    return a.time < b.time;
}
bool operator > (const State& a, const State& b)
{
    return a.time > b.time;
}

int N, M;
vector<vector<pi>> adj_list;
vector<int> s;
vector<State> latest;

void solve(void)
{
    scanf("%d %d", &N, &M);

    adj_list.assign(N, vector<pi>());
    latest.assign(N, BAD);
    s.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        u--; v--;

        adj_list[u].pb(mp(v, w));
        adj_list[v].pb(mp(u, w));
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }

    priority_queue<State, vector<State>, greater<State>> q;
    q.push({0, 0, INT_MAX});

    ll ans = -1;
    while (ans == -1) {
        State cur = q.top();
        q.pop();

        cur.slow = min(cur.slow, s[cur.city]);
        if (latest[cur.city].wins(cur)) {
            continue;
        }
        latest[cur.city] = cur;

        if (cur.city == N - 1) {
            ans = cur.time;
            break;
        }

        for (auto [v, w] : adj_list[cur.city]) {
            ll new_time = cur.time + cur.slow * w;

            q.push({v, new_time, cur.slow});
        }
    }

    printf("%lld\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}