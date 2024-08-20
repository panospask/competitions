#include <bits/stdc++.h>
#include "skolib.h"
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int DIRS = 8;
const int d_i[DIRS] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int d_j[DIRS] = {-1, 1, 2, 2, 1, -1, -2, -2};

const int INF = 1000;

int N;
int rem;
vector<vector<bool>> good;
vector<vector<int>> dist;
vector<vector<vector<int>>> cnt;

bool inside(int i, int j)
{
    return min(i, j) >= 0 && max(i, j) < N;
}

void calculate_dist(pi source)
{
    dist.assign(N, vector<int>(N, INF));
    dist[source.first][source.second] = 0;

    queue<pi> q;
    q.push(source);
    while (!q.empty()) {
        int i, j;
        tie(i, j) = q.front();
        q.pop();

        cnt[i][j][dist[i][j]]++;

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
}

int main(void) 
{
    N = daj_n();
    rem = N * N;
    good.assign(N, vector<bool>(N, true));
    cnt.resize(N, vector<vector<int>>(N, vector<int>(N, 0)));

    process(0 , 0);
    process(N - 1, 0);

    while (rem > 1) {
        int x, y;
        int opt = INF;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cnt[i][j].assign(N, 0);
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (good[i][j]) {
                    calculate_dist(mp(i, j));
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int cur = 0;
                for (int k = 0; k < N; k++) {
                    cur = max(cur, cnt[i][j][k]);
                }

                if (cur < opt) {
                    opt = cur;
                    x = i;
                    y = j;
                }
            }
        }

        process(x, y);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (good[i][j]) {
                odpowiedz(i + 1, j + 1);
            }
        }
    }

    exit(1);
}