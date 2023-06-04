#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;

const int STEPS = 3;
const ll INF = 1e18;
const int DIRS = 4;
const int d_i[] = {1, 0, -1, 0};
const int d_j[] = {0, 1, 0, -1};

int n, t;
int start;
vector<vector<int>> adj_list;
vector<vector<int>> grid;
vector<vector<bool>> visited;
vector<vector<ll>> dist;

int code(int i, int j)
{
    return n * i + j;
}
pi decode(int code)
{
    code %= n * n;
    return mp(code / n, code % n);
}

bool inbound(int i, int j)
{
    return min(i, j) >= 0 && max(i, j) < n;
}

int main(void)
{
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);

    scanf("%d %d", &n, &t);
    grid.resize(n, vector<int>(n));
    dist.assign(n * n, vector<ll>(3, INF));
    visited.assign(n * n, vector<bool>(3, false));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &grid[i][j]);

    start = code(0, 0);
    int ending = code(n - 1, n - 1);
    priority_queue<pair<ll, pi>, vector<pair<ll, pi>>, greater<pair<ll, pi>>> q;
    dist[0][0] = 0;
    q.push(mp(0, mp(0, 0)));

    while (!q.empty()) {
        int sq, step;
        tie(sq, step) = q.top().s;
        q.pop();

        if (visited[sq][step])
            continue;
        visited[sq][step] = true;

        int i, j;
        tie(i, j) = decode(sq);

        if (!step && start != sq)
            dist[sq][step] += grid[i][j];

        int nstep = (step + 1) % 3;
        for (int dir = 0; dir < DIRS; dir++) {
            int ni = i + d_i[dir];
            int nj = j + d_j[dir];

            if (inbound(ni, nj)) {
                int c2 = code(ni, nj);
                if (!visited[c2][nstep] && dist[c2][nstep] > dist[sq][step] + t) {
                    dist[c2][nstep] = dist[sq][step] + t;
                    q.push(mp(dist[c2][nstep], mp(c2, nstep)));
                }
            }
        }
    }

    ll ans = INF;
    for (int st = 0; st < 3; st++)
        ans = min(ans, dist[ending][st]);

    printf("%lld\n", ans);
}