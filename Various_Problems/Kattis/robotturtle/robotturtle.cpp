#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

const int n = 8;
const int INF = 1e6;

typedef pair<int, int> pi;
typedef pair<int, string> pis;
typedef pair<pi, string> pps;

// adding 1 is turning right
// subtracting 1 is turning left
const int DIRS = 4;
const int d_i[] = {0, 1, 0, -1};
const int d_j[] = {1, 0, -1, 0};

vector<vector<pps>> adj_list;
vector<int> dist;
vector<bool> visited;
vector<vector<int>> grid(n, vector<int>(n));
string path;
vector<pis> par;

int code(int i, int j, int dir)
{
    return (n * n) * dir + (i * n + j);
}

bool inbound(int i, int j)
{
    return i >= 0 && i < n && j >= 0 && j < n;
}

bool isdiamond(int codename)
{
    codename %= n * n;

    int i = codename / n;
    int j = codename % n;

    return grid[i][j] == 2;
}

void create_ans(int sq)
{
    while (sq != -1) {
        path += par[sq].s;
        sq = par[sq].f;
    }
}

int main(void)
{

    adj_list.resize(DIRS * n * n);
    dist.assign(DIRS * n * n, INF);
    visited.assign(DIRS * n * n, false);
    par.resize(DIRS * n * n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c", &c);

            if (c == 'C')
                grid[i][j] = 0;
            else if (c == 'D')
                grid[i][j] = 2;
            else if (c == 'I')
                grid[i][j] = 3;
            else
                grid[i][j] = 1;

            for (int dir = 0; dir < DIRS; dir++) {
                int nxt = (dir + 1) % DIRS;

                adj_list[code(i, j, dir)].push_back(mp(mp(code(i, j, nxt), 1), "R"));
                adj_list[code(i, j, nxt)].push_back(mp(mp(code(i, j, dir), 1), "L"));
            }
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (!grid[i][j])
                continue;

            for (int dir = 0; dir < DIRS; dir++) {
                int ni = i + d_i[dir];
                int nj = j + d_j[dir];

                if (!inbound(ni, nj) || !grid[ni][nj])
                    continue;

                if (grid[ni][nj] == 1 || grid[ni][nj] == 2)
                    adj_list[code(i, j, dir)].push_back(mp(mp(code(ni, nj, dir), 1), "F"));
                else
                    adj_list[code(i, j, dir)].push_back(mp(mp(code(ni, nj, dir), 2), "FX"));
            }
        }

    dist[code(n - 1, 0, 0)] = 0;
    priority_queue<pi, vector<pi>, greater<pi>> q;
    q.push(mp(0, code(n - 1, 0, 0)));
    par[code(n - 1, 0, 0)]  = mp(-1, "");

    bool ans = false;
    while (!q.empty()) {
        int v = q.top().s;
        q.pop();

        if (visited[v])
            continue;
        visited[v] = true;
        if (dist[v] == INF)
            break;

        if (isdiamond(v)) {
            ans = true;
            create_ans(v);
            break;
        }

        for (auto e : adj_list[v]) {
            if (dist[e.f.f] > dist[v] + e.f.s) {
                dist[e.f.f] = dist[v] + e.f.s;
                par[e.f.f] = mp(v, e.s);

                q.push(mp(dist[e.f.f], e.f.f));
            }
        }
    }

    if (ans) {
        reverse(path.begin(), path.end());
        for (auto c : path)
            printf("%c", c);
        printf("\n");
    }
    else {
        printf("no solution\n");
    }

    return 0;
}