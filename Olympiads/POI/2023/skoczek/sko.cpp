#include <bits/stdc++.h>
#include "skolib.h"
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;

const int DIRS = 8;
const int d_i[DIRS] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int d_j[DIRS] = {-1, 1, 2, 2, 1, -1, -2, -2};

const int INF = 1000000;
const int BORDER = 2;

int N;
int rem;
vector<vector<bool>> good;
vector<vector<int>> dist;

int MIN_X, MAX_X, MIN_Y, MAX_Y;

bool inside(int i, int j)
{
    return i >= max(MIN_X - BORDER, 0) && i <= min(N - 1, MAX_X + BORDER) && j >= max(0, MIN_Y - BORDER) && j <= min(N - 1, MAX_Y + BORDER);
}

void calculate_dist(pi source)
{
    dist[source.first][source.second] = 0;

    queue<pi> q;
    q.push(source);
    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        for (int d = 0; d < DIRS; d++) {
            int n_i = i + d_i[d];
            int n_j = j + d_j[d];

            if (inside(n_i, n_j) && dist[n_i][n_j] == INF) {
                dist[n_i][n_j] = dist[i][j] + 1;
                q.push(mp(n_i, n_j));
            }
        }
    }
}

void process(int x, int y)
{
    calculate_dist(mp(x, y));
    int d = pytanie(x + 1, y + 1);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (good[i][j] && dist[i][j] != d) {
                good[i][j] = false;
                rem--;
            }
        }
    }

    dist.assign(N, vector<int>(N, INF));
}

void clear_distance(void)
{
    for (int i = max(MIN_X - BORDER, 0); i <= min(N - 1, MAX_X + BORDER); i++) {
        for (int j = max(MIN_Y - BORDER, 0); j <= min(N - 1, MAX_Y + BORDER); j++) {
            dist[i][j] = INF;
        }
    }
}

bool recursively(vector<pi> candidates, int rem, bool execute)
{
    if (candidates.size() == 0) {
        return true;
    }
    if (rem == 0) {
        if (execute) {
            odpowiedz(candidates.front().first + 1, candidates.front().second + 1);
        }
        return candidates.size() <= 1;
    }

    int PMNX = MIN_X, PMXX = MAX_X, PMNY = MIN_Y, PMXY = MAX_Y;

    for (auto c : candidates) {
        MIN_X = min(c.first, MIN_X);
        MIN_Y = min(c.second, MIN_Y);
        MAX_X = max(c.first, MAX_X);
        MAX_Y = max(c.second, MAX_Y);
    }

    for (int i = max(MIN_X - BORDER, 0); i <= min(N - 1, MAX_X + BORDER); i++) {
        for (int j = max(MIN_Y - BORDER, 0); j <= min(N - 1, MAX_Y + BORDER); j++) {
            calculate_dist(mp(i, j));

            bool good = true;
            vector<vector<pi>> by_distance(MAX_X - MIN_X + MAX_Y - MIN_Y + 2 * BORDER);

            for (auto c : candidates) {
                by_distance[dist[c.first][c.second]].pb(c);
            }

            clear_distance();

            for (int d = 0; d < by_distance.size(); d++) {
                good = good && recursively(by_distance[d], rem - 1, false);
            }

            if (good) {
                if (execute) {
                    int d = pytanie(i + 1, j + 1);
                    recursively(by_distance[d], rem - 1, true);
                }

                return true;
            }
        }
    }

    MAX_X = PMXX;
    MAX_Y = PMXY;
    MIN_X = PMNX;
    MIN_X = PMNX;


    return false;
}

int main(void) 
{
    N = daj_n();
    rem = N * N;
    good.assign(N, vector<bool>(N, true));

    MIN_X = 0;
    MAX_X = N - 1;
    MIN_Y = 0;
    MAX_Y = N - 1;

    dist.assign(N, vector<int>(N, INF));
    process(0 , 0);
    process(N - 1, 0);
    process(0, N - 1);

    vector<pi> candidates;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (good[i][j]) {
                candidates.pb(mp(i, j));
            }
        }
    }

    MIN_X = MIN_Y = N - 1;
    MAX_X = MAX_Y = 0;
    recursively(candidates, 3, true);
}