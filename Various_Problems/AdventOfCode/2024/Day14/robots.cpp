#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int WIDTH = 101;
const int HEIGHT = 103;
const int STEPS = 1;

pi operator + (pi a, pi b)
{
    return mp(a.first + b.first, a.second + b.second);
}
pi operator * (pi a, int b)
{
    return mp(a.first * b, a.second * b);
}

int N;
int cnt[3][3];
vector<vector<int>> grid(HEIGHT, vector<int>(WIDTH, 0));
vector<pi> positions;
vector<pi> velocities;

int cmp(int a, int b)
{
    if (a < b) {
        return -1;
    }
    else if (a > b) {
        return 1;
    }
    else {
        return 0;
    }
}

void process_robot(pi& pos, pi vel)
{
    pi res = pos + vel * STEPS;
    grid[pos.second][pos.first]--;

    res.first = (res.first % WIDTH + WIDTH) % WIDTH;
    res.second = (res.second % HEIGHT + HEIGHT) % HEIGHT;

    pos = res;
    grid[pos.second][pos.first]++;
}

void print_positions(void)
{
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j]) {
                printf("%d", grid[i][j]);
            }
            else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// At least half the robots should have above neighbours
bool possible_tree(void)
{
    int ans = 0;
    for (int i = 0; i < N; i++) {
        pi p = positions[i];
        if (p.second && grid[p.second - 1][p.first]) {
            ans++;
        }
    }

    return ans >= N / 4;
}

int main(void)
{
    freopen("robots.in", "r", stdin);

    int c = 0;
    while ((c = getchar()) != EOF) {
        ungetc(c, stdin);

        pi p, v;
        scanf("p=%d,%d v=%d,%d\n", &p.first, &p.second, &v.first, &v.second);

        positions.pb(p);
        velocities.pb(v);
        grid[p.second][p.first]++;
    }

    N = positions.size();

    for (int i = 0; i < 10000; i++) {
        for (int j = 0; j < N; j++) {
            process_robot(positions[j], velocities[j]);
        }
        
        if (possible_tree()) {
            printf("Steps: %d\n", i);
            print_positions();
        }
    }
    return 0;
}