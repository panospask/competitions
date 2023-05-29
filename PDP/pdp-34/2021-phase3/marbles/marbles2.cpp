#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

int n, m, t;
unordered_map<ll, pair<ll, int>> pmove;
vector<ll> npow;
vector<pi> moves;

vector<int> cur;
ll initial = 0, dest = 0;

void decode(ll code)
{
    for (int i = 0; i < n; i++) {
        cur[i] = code % n;
        code /= n;
    }
}

void solve(void)
{
    scanf("%d", &m);
    pmove.clear();
    moves.clear();
    moves.resize(m);

    initial = 0;
    for (int i = 0; i < n; i++) {
        int num;
        scanf("%d", &num);
        num--;

        initial += num * npow[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        moves[i] = mp(a, b);
    }

    queue<ll> q;
    q.push(initial);

    int ans = -1;
    while (!q.empty()) {
        ll code = q.front();
        q.pop();

        if (code == dest) {
            ans = 1;
            break;
        }

        decode(code);
        for (int mv = 0; mv < m; mv++) {
            pi p = moves[mv];
            ll nxt = code;
            nxt += cur[p.f] * (npow[p.s] - npow[p.f]);
            nxt += cur[p.s] * (npow[p.f] - npow[p.s]);

            if (pmove.find(nxt) == pmove.end()) {
                pmove[nxt] = mp(code, mv);
                q.push(nxt);
            }
        }
    }

    if (ans == -1) {
        printf("IMPOSSIBLE\n");
    }
    else {
        stack<int> path;
        ll node = dest;
        while (node != initial) {
            path.push(pmove[node].second);
            node = pmove[node].first;
        }

        printf("MOVES %d\n", (int)path.size());
        while (!path.empty()) {
            printf("%d\n", path.top() + 1);
            path.pop();
        }
    }
}

int main(void)
{
    freopen("marbles.in", "r", stdin);
    freopen("marbles.out", "w", stdout);

    scanf("%d %d", &t, &n);

    npow.resize(n + 1);
    cur.resize(n + 1);
    npow[0] = 1;
    dest = 0;

    for (int i = 0; i < n; i++) {
        npow[i + 1] = npow[i] * n;
        dest += i * npow[i];
    }

    while(t--)
        solve();

    return 0;
}