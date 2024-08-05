// Can be improved to O(n) if propagate is implemented using BFS and gradually adding the sources

#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int INF = 1e9;

const int DIRS = 4;
const int d_x[DIRS] = {1, 0, -1, 0};
const int d_y[DIRS] = {0, 1, 0, -1};

const int ROCK = 0;
const int STARTING = 1;
const int NONE = 2;

int N, D;
int ans;
vector<vector<int>> grid;

// Distance to a rock square
vector<vector<int>> rockdist;

// The minimum time needed for the main robot to reach current square from a starting position
vector<vector<int>> reach;

// Maximum growth of the robot in each square
vector<vector<int>> maxgrow;

bool inside(int i, int j)
{
    return min(i, j) >= 0 && max(i, j) < N;
}

void calculate_rockdist(void)
{
    rockdist.assign(N, vector<int>(N, INF));

    queue<pi> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == ROCK) {
                rockdist[i][j] = 0;
                q.push(mp(i, j));
            }
        }
    }

    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        for (int d = 0; d < DIRS; d++) {
            int n_i = i + d_y[d];
            int n_j = j + d_x[d];

            if (inside(n_i, n_j) && rockdist[n_i][n_j] == INF) {
                rockdist[n_i][n_j] = rockdist[i][j] + 1;
                q.push(mp(n_i, n_j));
            }
        }
    }
}

void calculate_reachable(void)
{
    reach.assign(N, vector<int>(N, INF));

    queue<pi> q;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == STARTING) {
                reach[i][j] = 0;
                q.push(mp(i, j));
            }
        }
    }

    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        int growth = reach[i][j] / D;
        if (growth == rockdist[i][j]) {
            // Cannot move further 
            continue;
        }

        for (int d = 0; d < DIRS; d++) {
            int n_i = i + d_y[d];
            int n_j = j + d_x[d];

            if (inside(n_i, n_j) && rockdist[n_i][n_j] > growth && reach[n_i][n_j] == INF) {
                reach[n_i][n_j] = reach[i][j] + 1;
                q.push(mp(n_i, n_j));
            }
        }
    }
}

void calculate_maxgrowth(void)
{
    maxgrow.assign(N, vector<int>(N, -1));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reach[i][j] == INF) {
                continue;
            }

            // The maximum growth will either be rockdist[i][j] - 1 or rockdist[i][j] - 2
            ll steps_needed = (ll)D * (rockdist[i][j] - 1);
            if ((steps_needed - reach[i][j]) % 2 == 0) {
                // We can always end here
                maxgrow[i][j] = rockdist[i][j] - 1;
            }
            else {
                bool geq = false;
                for (int d = 0; d < 4; d++) {
                    int n_i = i + d_y[d];
                    int n_j = j + d_x[d];

                    if (inside(n_i, n_j) && rockdist[n_i][n_j] >= rockdist[i][j]) {
                        geq = true;
                    }
                }

                maxgrow[i][j] = rockdist[i][j] - 2 + geq;
            }
        }
    }
}

void read(void)
{
    scanf("%d %d", &N, &D);

    grid.resize(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char c;
            scanf(" %c", &c);

            if (c == '#') {
                grid[i][j] = ROCK;
            }
            else if (c == 'S') {
                grid[i][j] = STARTING;
            }
            else {
                grid[i][j] = NONE;
            }
        }
    }
}

void propagate(void)
{
    priority_queue<pair<int, pi>> q;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maxgrow[i][j] != -1) {
                q.push(mp(maxgrow[i][j], mp(i, j)));
            }
        }
    }

    ans = 0;

    while (!q.empty()) {
        int m, i, j;
        auto res = q.top();
        q.pop();

        m = res.first;
        tie(i, j) = res.second;

        if (maxgrow[i][j] != m) {
            continue;
        }

        ans++;
        if (maxgrow[i][j] == 0) {
            continue;
        }

        for (int d = 0; d < DIRS; d++) {
            int n_i = i + d_y[d];
            int n_j = j + d_x[d];

            if (inside(n_i, n_j) && maxgrow[n_i][n_j] < m - 1) {
                maxgrow[n_i][n_j] = m - 1;
                q.push(mp(m - 1, mp(n_i, n_j)));
            }
        }
    }
}

int main(void)
{
    read();

    calculate_rockdist();

    calculate_reachable();

    calculate_maxgrowth();

    propagate();

    printf("%d\n", ans);

    return 0;
}