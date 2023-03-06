#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 20

using namespace std;

typedef pair<int, int> ii;

int n;
char grid[MAXN + 2][MAXN + 2];
bool visited[MAXN + 2][MAXN + 2];
unordered_map<char, int> components;
int dir_ver[4] = {1, 0, -1, 0};
int dir_hor[4] = {0, 1, 0, -1};

int mini, minj, maxi, maxj;

struct pcl {
    int i1, j1, i2, j2;
};
typedef struct pcl PCL;
vector<PCL> cowlocs;
vector<bool> counts;

bool is_inside(PCL& a, PCL& b)
{
    if (a.i1 >= b.i1 && a.j1 >= b.j1 && a.i2 <= b.i2 && a.j2 <= b.j2)
        return true;
    return false;
}

void floodfill(int i, int j)
{
    char col = grid[i][j];

    stack<ii> tiles;
    tiles.push(mp(i,j));

    int cur_i, cur_j;
    while (!tiles.empty()) {
        tie(i, j) = tiles.top();
        tiles.pop();

        if (i < mini || i > maxi || j < minj || j > maxj)
            continue;
        if (visited[i][j] || grid[i][j] != col)
            continue;
        
        visited[i][j] = true;
        for (int x = 0; x < 4; x++)
            tiles.push(mp(i + dir_ver[x], j + dir_hor[x]));
    }
}

bool is_pcl(int i1, int j1, int i2, int j2)
{
    mini = i1, minj = j1, maxi = i2, maxj = j2; 
    components.clear();
    memset(visited, false, sizeof(visited));

    for (int i = i1; i <= i2; i++)
        for (int j = j1; j <= j2; j++)
            if (!visited[i][j]) {
                floodfill(i,j);
                components[grid[i][j]]++;
            }

    if (components.size() > 2)
        return false;

    if (i1 == 0 && i2 == 1 && j1 == 4 && j2 == 7)
        cerr << "here";

    bool have_one = false, have_two = false;
    for (auto& c : components) {
        have_one = have_one || c.second == 1;
        have_two = have_two || c.second >= 2;
    }

    return have_one && have_two;
}

void prnt_pcl(PCL a)
{
    for (int i = a.i1; i <= a.i2; i++) {
        for (int j = a.j1; j <= a.j2; j++)
            putchar(grid[i][j]);
        putchar('\n');
    }
    putchar('\n');
}

int main(void)
{
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        getchar();
        for (int j = 0; j < n; j++)
            grid[i][j] = getchar();
    }

    PCL cur;
    for (int i1 = 0; i1 < n; i1++)
        for (int i2 = i1; i2 < n; i2++)
            for (int j1 = 0; j1 < n; j1++)
                for (int j2 = j1; j2 < n; j2++) {
                    if (is_pcl(i1, j1, i2, j2)) {
                        cur.i1 = i1;
                        cur.i2 = i2;
                        cur.j1 = j1;
                        cur.j2 = j2;

                        cowlocs.pb(cur);
                        counts.pb(true);
                    }
                }

    for (int i = 0; i < cowlocs.size(); i++)
        for (int j = 0; j < cowlocs.size(); j++)
            if (counts[i] && i != j && is_inside(cowlocs[i], cowlocs[j]))
                counts[i] = false;

    int ans = 0;
    for (int i = 0; i < counts.size(); i++)
        if (counts[i]) {
            // cerr << cowlocs[i].i1 << ' ' << cowlocs[i].j1 << ' ' << cowlocs[i].i2 << ' ' << cowlocs[i].j2 << '\n';
            ans++;
            // prnt_pcl(cowlocs[i]);
        }

    printf("%d\n", ans);
    return 0;
}