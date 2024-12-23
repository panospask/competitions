#include <bits/stdc++.h>
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

pi dirs[4] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

const int WALL = -1;
const int NONE = 0;
const int BOX = 1;

struct Box {
    // Top left and bottom right squares
    pi tl;
    pi br;
    int id;
};

int N, M;
vector<vector<int>> grid;
queue<pi> moves;
vector<Box> boxes;

void print(void);

pi operator + (pi a, pi b)
{
    return {a.first + b.first, a.second + b.second};
}

// Act is a boolean variable denoting weather to actually push the box or not
bool push(Box& b, pi d, bool act)
{
    pi ntl = b.tl + d;
    pi nbr = b.br + d;

    vector<int> found;
    for (int i = ntl.first; i <= nbr.first; i++) {
        for (int j = ntl.second; j <= nbr.second; j++) {
            if (grid[i][j] == WALL) {
                return false;
            }
            else if (grid[i][j] > 0 && grid[i][j] != b.id) {
                found.pb(grid[i][j]);
            }
        }
    }

    sort(found.begin(), found.end());
    found.resize(unique(found.begin(), found.end()) - found.begin());

    bool s = true;
    for (auto f : found) {
        s = s && push(boxes[f - 1], d, act);
    }

    if (!s) {
        return false;
    }

    if (act) {
        for (int i = b.tl.first; i <= b.br.first; i++) {
            for (int j = b.tl.second; j <= b.br.second; j++) {
                grid[i][j] = 0;
            }
        }
        b.tl = ntl;
        b.br = nbr;
        for (int i = ntl.first; i <= nbr.first; i++) {
            for (int j = ntl.second; j <= nbr.second; j++) {
                grid[i][j] = b.id;
            }
        }
    }
    return true;
}

void move(Box& robot)
{
    if (moves.empty()) {
        return;
    }

    pi original = robot.tl;
    pi d = moves.front();
    moves.pop();
    if (push(robot, d, false)) {
        push(robot, d, true);

        grid[original.first][original.second] = 0;
    }

    // print();
    move(robot);
}

void print(void)
{
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 0) {
                printf(".");
            }
            else if (grid[i][j] == -1) {
                printf("#");
            }
            else if (grid[i][j] == boxes.size()) {
                printf("H");
            }
            else {
                printf("O");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(void)
{
    freopen("robot.in", "r", stdin);

    pi start;
    int c = 0;
    int i = 0, j = 0;
    while ((c = getchar()) != '\n') {
        ungetc(c, stdin);
        grid.pb({});

        j = 0;
        while ((c = getchar()) != '\n') {
            int v1 = 0, v2 = 0;
            if (c == '#') {
                v1 = v2 = WALL;
            }
            else if (c == 'O') {
                v1 = v2 = boxes.size() + 1;
                boxes.pb({{i, j}, {i, j + 1}, (int)boxes.size() + 1});
            }
            else {
                v1 = v2 = 0;
                if (c == '@') {
                    start = {i, j};
                }
            }
            grid.back().pb(v1);
            grid.back().pb(v2);
            j += 2;
        }
        i++;
    }

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            continue;
        }
        if (c == '>') {
            moves.push(dirs[0]);
        }
        else if (c == '<') {
            moves.push(dirs[2]);
        }
        else if (c == '^') {
            moves.push(dirs[1]);
        }
        else {
            moves.push(dirs[3]);
        }
    }

    boxes.pb({start, start, (int)boxes.size() + 1});
    grid[start.first][start.second] = boxes.size();
    move(boxes.back());

    ll ans = 0;
    for (auto r : boxes) {
        if (r.id == boxes.size()) {
            continue;
        }
        ans += 100 * r.tl.first + r.tl.second;
    }

    // print();

    printf("%lld\n", ans);
    
    return 0;
}