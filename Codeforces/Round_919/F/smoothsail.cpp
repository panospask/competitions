#include <bits/stdc++.h>
#define f first
#define s second
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int DIRS = 4;
const int d_i[4] = {1, 0, -1, 0};
const int d_j[4] = {0, 1, 0, -1};

int N, M;


vector<vector<int>> dist;
vector<vector<bool>> visited;
vector<vector<bool>> island;
vector<pi> volcanoes;
pi hor_block;

int allow, t_i, t_j;

bool check_inside(int i, int j)
{
    return 0 <= i && i < N && 0 <= j && j < M;
}

bool in_block(int j)
{
    return hor_block.f <= j && j <= hor_block.s;
}

bool dfs(int i, int j, bool start)
{
    visited[i][j] = true;

    for (int dir = 0; dir < DIRS; dir++) {
        int n_i = i + d_i[dir];
        int n_j = j + d_j[dir];

        if (!check_inside(n_i, n_j))
            continue;
        if (visited[n_i][n_j] || dist[n_i][n_j] < allow)
            continue;
        if (n_i == t_i && in_block(j)) {
            if (dir != 3) {
                return true;
            }
            else {
                continue;
            }
        }
    }

    return false;
}

void calculate_distances(void)
{
    queue<pi> q;

    dist.assign(N, vector<int>(M, -1));

    for (auto v : volcanoes) {
        dist[v.f][v.s] = 0;
        q.push(v);
    }

    while (!q.empty()) {
        pi cur = q.front(); q.pop();

        int i, j;
        tie(i, j) = cur;

        for (int dir = 0; dir < DIRS; dir++) {
            int n_i = i + d_i[dir];
            int n_j = j + d_j[dir];

            if (!check_inside(n_i, n_j) || island[n_i][n_j] || dist[n_i][n_j] >= 0)
                continue;

            dist[n_i][n_j] = dist[i][j] + 1;
            q.push(mp(n_i, n_j));
        }
    }
}

void block_horizontal(void)
{
    hor_block.f = hor_block.s = t_j;
    for (int j = t_j; j >= 0; j--) {
        if (island[t_i][j])
            break;

        hor_block.f = j;
    }
    for (int j = t_j + 1; j < M; j++) {
        if (island[t_i][j])
            break;

        hor_block.s = j;
    }
}

void query(void)
{
    scanf("%d %d", &t_i, &t_j);
    t_i--;
    t_j--;

    block_horizontal();

    int l = 0; //
}

int main(void)
{
    ;
}