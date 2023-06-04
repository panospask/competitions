#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;

const ll INF = 1e18;

pi start, dest;
int n;
int total_nodes = 0;
map<pi, int> code;
vector<vector<pi>> adj_list;
vector<bool> visited;
vector<ll> dist;

vector<pair<int, pi>> vert_sides;
vector<pair<pi, int>> hor_sides;

int find(int i, int j)
{
    if (code.find(mp(i, j)) == code.end()) {
        code[mp(i, j)] = total_nodes++;
        adj_list.pb(vector<pi>(0));
    }

    return code[mp(i, j)];
}

// Return first square that is after (x, y) with same y
pll get_horizontal_squares(int x, int y)
{
    ll close_left = INF, close_right = INF;

    for (int i = 0; i < vert_sides.size(); i++) {
        if (y < vert_sides[i].s.f || y > vert_sides[i].s.s)
            continue;

        if (vert_sides[i].f < x) {
            // Check left

            if (abs(x - close_left) > abs(x - vert_sides[i].f))
                close_left = vert_sides[i].f;
        }
        else if (vert_sides[i].f > x) {
            // Check right

            if (abs(x - close_right) > abs(x - vert_sides[i].f))
                close_right = vert_sides[i].f;
        }
    }

    return mp(close_left, close_right);
}

// Return squares that are close to (x, y) with same x
pll get_vertical_squares(int x, int y)
{
    ll close_up = INF, close_down = INF;

    for (int i = 0; i < hor_sides.size(); i++) {
        if (x < hor_sides[i].f.f || x > hor_sides[i].f.s)
            continue;

        if (y > hor_sides[i].s) {
            // Check down
            if (abs(y - hor_sides[i].s) < abs(y - close_down))
                close_down = hor_sides[i].s;
        }
        else if (y < hor_sides[i].s) {
            // Check up
            if (abs(y - hor_sides[i].s) < abs(y - close_up))
                close_up = hor_sides[i].s;
        }
    }

    return mp(close_down, close_up);
}

map<int, bool> seen;

void proccess_square(int x, int y, bool find_ver, bool force)
{
    int c = find(x, y);
    if (seen[c] && !force)
        return;
    seen[c] = true;

    pll possible;
    if (find_ver)
        possible = get_vertical_squares(x, y);
    else
        possible = get_horizontal_squares(x, y);

    if (possible.f != INF) {
        int nx, ny;
        if (find_ver) {
            nx = y;
            ny = possible.f;
        }
        else {
            nx = possible.f;
            ny = y;
        }

        int c1 = find(nx, ny);
        int w = abs(x - nx + y - ny);
        adj_list[c1].pb(mp(c, w));
        adj_list[c].pb(mp(c1, w));

        proccess_square(nx, ny, !find_ver, false);
    }
    if (possible.s != INF) {
        int nx, ny;
        if (find_ver) {
            nx = y;
            ny = possible.s;
        }
        else {
            nx = possible.s;
            ny = y;
        }

        int c1 = find(nx, ny);
        int w = abs(x - nx + y - ny);
        adj_list[c1].pb(mp(c, w));
        adj_list[c].pb(mp(c1, w));

        proccess_square(nx, ny, !find_ver, false);
    }
}

void solve(void)
{
    code.clear();
    adj_list.clear();
    dist.clear();
    seen.clear();
    vert_sides.clear();
    hor_sides.clear();
    visited.clear();
    total_nodes = 0;

    scanf("%d %d %d %d", &start.f, &start.s, &dest.f, &dest.s);
    scanf("%d", &n);

    int s_code = find(start.f, start.s);
    int d_code = find(dest.f, dest.s);


    vert_sides.pb(mp(start.f, mp(start.s, start.s)));
    hor_sides.pb(mp(mp(start.f, start.f), start.s));
    vert_sides.pb(mp(dest.f, mp(dest.s, dest.s)));
    hor_sides.pb(mp(mp(dest.f, dest.f), dest.s));

    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        if (x1 > x2)
            swap(x1, x2);
        if (y1 > y2)
            swap(y1, y2);

        vert_sides.pb(mp(x1, mp(y1, y2)));
        vert_sides.pb(mp(x2, mp(y1, y2)));
        hor_sides.pb(mp(mp(x1, x2), y1));
        hor_sides.pb(mp(mp(x1, x2), y2));
    }

    proccess_square(start.f, start.s, true, true);
    proccess_square(start.f, start.s, false, true);

    visited.assign(total_nodes, false);
    dist.assign(total_nodes, INF);

    priority_queue<pli, vector<pli>, greater<pli>> q;

    dist[find(start.f, start.s)] = 0;
    q.push(mp(0, find(start.f, start.s)));

    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;

        if (v == d_code)
            break;

        for (auto e : adj_list[v]) {
            if (dist[e.f] > dist[v] + e.s) {
                dist[e.f] = dist[v] + e.s;
                q.push(mp(dist[e.f], e.f));
            }
        }
    }

    if (dist[d_code] == INF)
        printf("No Path\n");
    else
        printf("%lld\n", dist[d_code]);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
        solve();

    return 0;
}