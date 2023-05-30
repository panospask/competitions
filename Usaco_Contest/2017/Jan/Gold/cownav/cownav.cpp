#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define f first
#define s second

using namespace std;

typedef pair<int, int> pi;

struct SquareSit {
    pi square;
    pi headed;
};

bool operator < (const SquareSit& a, const SquareSit& b) {
    if (a.square == b.square)
        return a.headed < b.headed;

    return a.square < b.square;
}

typedef pair<SquareSit, SquareSit> SS;

int n;
queue<SS> q;
vector<vector<bool>> grid;

map<SS, int> dist;

SS initial;
pi dest;

pi turn(pi dir, int left)
{
    pi ndir;
    ndir.f = dir.s * (-left);
    ndir.s = dir.f * left;

    return ndir;
}

pi operator + (pi& a, pi& b)
{
    return mp(a.f + b.f, a.s + b.s);
}

bool inbound(pi square)
{
    return square.f >= 0 && square.s >= 0 && square.f < n && square.s < n;
}

pi endsquare(pi startsquare, pi& dir)
{
    if (startsquare == dest)
        return startsquare;

    pi ending = startsquare + dir;

    if (!inbound(ending) || !grid[ending.f][ending.s])
        return startsquare;

    return ending;
}

void insertq(SS& sit, int curd)
{
    if (dist.find(sit) == dist.end()) {
        dist[sit] = curd + 1;
        q.push(sit);
    }
}

int main(void)
{
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);

    scanf("%d", &n);
    grid.resize(n, vector<bool>(n));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            char c;
            scanf(" %c", &c);
            if (c == 'H')
                grid[i][j] = false;
            else
                grid[i][j] = true;
        }

    initial.f.square = initial.s.square = mp(n - 1, 0);
    initial.f.headed = mp(-1, 0);
    initial.s.headed = mp(0, 1);
    dist[initial] = 0;
    q.push(initial);
    dest = mp(0, n - 1);

    int ans = -1;
    while (!q.empty()) {
        SS cur = q.front();
        q.pop();

        int curd = dist[cur];

        if (cur.f.square == cur.s.square && cur.f.square == dest) {
            ans = curd;
            break;
        }

        // Move them forward
        SS nxt = cur;
        nxt.f.square = endsquare(cur.f.square, cur.f.headed);
        nxt.s.square = endsquare(cur.s.square, cur.s.headed);

        insertq(nxt, curd);

        nxt = cur;
        nxt.f.headed = turn(cur.f.headed, 1);
        nxt.s.headed = turn(cur.s.headed, 1);

        insertq(nxt, curd);

        nxt = cur;
        nxt.f.headed = turn(cur.f.headed, -1);
        nxt.s.headed = turn(cur.s.headed, -1);

        insertq(nxt, curd);
    }

    printf("%d\n", ans);
    return 0;
}