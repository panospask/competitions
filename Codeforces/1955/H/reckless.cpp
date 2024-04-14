#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define CHECK_BIT(val, pos) ((1 << pos) & val)

using namespace std;

typedef pair<vector<short int>, int> pvi;
typedef pair<int, int> pi;
typedef long long ll;

struct Tower {
    pi loc;
    int p;
    int id;

    vector<int> net;

    void read(int i) {
        id = i;
        scanf("%d %d %d", &loc.first, &loc.second, &p);
        loc.first--;
        loc.second--;
    }
};

struct State {
    vector<int> chosen;
    int h;
    int r;
};
const State INIT = {{}, 0, 0};

const int MAXR = 11;
const int DEFAULT = 1e9;

int NEW_MAX = 0;


int N, M, K;

//dp[s][i]:
// Best way to cover the radii in the subset s using the first i towers
vector<vector<int>> dp;
vector<vector<bool>> grid;
vector<Tower> towers;
vector<int> best;

int V;
bool towercomp(const int& a, const int& b)
{
    bool f = towers[a].net.size() <= V;
    bool s = towers[b].net.size() <= V;

    if (s) {
        return false;
    }
    else if (f) {
        return true;
    }
    else {
        int val = (towers[a].net[V] - towers[b].net[V]);
        // if (V) {
        //     val -= towers[a].net[V - 1] - towers[b].net[V - 1];
        // }
        return val < 0;
    }
}

int distsq(pi a, pi b)
{
    return (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);
}

// Calculate net for tower i
void calculate(Tower& t)
{
    t.net.assign(MAXR, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!grid[i][j]) {
                continue;
            }

            int d = distsq(t.loc, mp(i, j));
            int r = 1;
            while (r <= MAXR && r * r < d) {
                r++;
            }

            if (r <= MAXR) {
                t.net[r - 1] += t.p;
            }
        }
    }

    for (int r = 0; r < MAXR - 1; r++) {
        t.net[r + 1] += t.net[r];
    }
    int rm = 3;
    int loc_max = 0;
    for (int r = 0; r < MAXR; r++) {
        t.net[r] -= rm;
        t.net[r] = max(t.net[r], 0);
        rm *= 3;

        if (t.net[r]) {
            loc_max = r + 1;
        }
    }

    t.net.resize(loc_max);
    NEW_MAX = max(NEW_MAX, loc_max);

    return;
}

void read_input(void)
{
    scanf("%d %d %d", &N, &M, &K);

    grid.assign(N, vector<bool>(M, false));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            char cur;
            scanf(" %c", &cur);

            if (cur == '#') {
                grid[i][j] = true;
            }
        }

    towers.resize(K);
    for (int i = 0; i < K; i++) {
        towers[i].read(i);
    }
}

void solve(void)
{
    NEW_MAX = 0;
    read_input();

    for (int i = 0; i < K; i++) {
        calculate(towers[i]);
    }
    for (int i = 0; i < K; i++) {
        towers[i].net.resize(NEW_MAX);
    }

    int ans = 0;
    dp.assign(1 << NEW_MAX, vector<int>(K + 1, 0));
    for (int s = 0; s < (1 << NEW_MAX); s++) {
        for (int i = 1; i <= K; i++) {
            dp[s][i] = dp[s][i - 1];

            for (int r = 0; r < NEW_MAX; r++) {
                if (CHECK_BIT(s, r)) {
                    dp[s][i] = max(dp[s][i], dp[s - (1 << r)][i - 1] + towers[i - 1].net[r]);
                }
            }
            ans = max(ans, dp[s][i]);
        }
    }

    printf("%d\n", ans);

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--)
    {
        solve();
    }

    return 0;
}