#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<vector<int>> grid;
vector<pi> positions[CHAR_MAX + 1];
vector<vector<bool>> antinode;

int gcd(int a, int b)
{
    if (a < b) {
        swap(a, b);
    }

    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

pi operator + (pi a, pi b)
{
    return mp(a.first + b.first, a.second + b.second);
}
pi operator - (pi a, pi b)
{
    return mp(a.first - b.first, a.second - b.second);
}

bool inside(pi sq)
{
    return sq.first >= 0 && sq.first < N && sq.second >= 0 && sq.second < M;
}

void line(pi u, pi v)
{
    if (u == v) {
        return;
    }

    pi dist = v - u;
    int g = gcd(abs(dist.first), abs(dist.second));
    dist.first /= g;
    dist.second /= g;

    pi cur = u;
    while (inside(cur)) {
        antinode[cur.first][cur.second] = true;

        cur = cur + dist;
    }
    cur = u;
    while (inside(cur)) {
        antinode[cur.first][cur.second] = true;

        cur = cur - dist;
    }
}

int main(void)
{
    freopen("antena.in", "r", stdin);
    freopen("antena.out", "w", stdout);

    int c;

    int i = 0, j = 0;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);
        j = 0;

        grid.pb({});
        while ((c = getchar()) != '\n') {
            grid.back().pb(c);

            if (c != '.') {
                positions[c].pb(mp(i, j));
            }

            j++;
        }
        i++;
    }

    N = grid.size();
    M = grid[0].size();

    antinode.assign(N, vector<bool>(M, false));

    for (c = 0; c < CHAR_MAX + 1; c++) {
        for (auto u : positions[c]) {
            for (auto v : positions[c]) {
                line(u, v);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ans += antinode[i][j];
        }
    }

    printf("%d\n", ans);

    return 0;
}