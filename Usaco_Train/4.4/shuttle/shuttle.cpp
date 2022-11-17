/*
ID: panos.p1
LANG: C++11
TASK: shuttle
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 12

using namespace std;

vector<int> moves;
int space;
int holes[2 * MAXN + 1];
int should_go[2 * MAXN + 1];
char row[2 * MAXN + 1];
int n;
unordered_map<char, int> dest;

int dist(int a, int b)
{
    if (a > b)
        return a - b;
    else
        return b - a;
}

bool can_jump(int i, int dir)
{
    if (i < 0 || i >= 2 * n + 1)
        return false;

    char colour = row[i];
    char nxt = row[i + dir];

    if (colour != nxt && dist(i, dest[colour]) > dist(i + 2 * dir, dest[colour]))
        return true;
    
    return false;
}

int ttl_white_before(void)
{
    int cons = 0;
    for (int i = space - 1; i >= 0 && row[i] == 'W'; i--) {
        cons++;
        if (i == dest['B'])
            return INT_MAX;
    }

    return cons;
}

int ttl_black_after(void)
{
    int cons = 0;
    for (int i = space + 1; i < 2 * n + 1 && row[i] == 'B'; i++) {
        cons++;
        if (i == dest['W'])
            return INT_MAX;
    }

    return cons;
}

void make_next_move(void)
{
    int prevspace = space;
    // Check for jumps
    if (can_jump(space - 2, +1)) {
        swap(row[space - 2], row[space]);
        swap(holes[space - 2], holes[space]);

        if (dest[row[space]] == space)
            dest[row[space]]--;
        space -= 2;
    }
    else if (can_jump(space + 2, -1)) {
        swap(row[space + 2], row[space]);
        swap(holes[space + 2], holes[space]);

        if (dest[row[space]] == space)
            dest[row[space]]++;
        space += 2;
    }
    else {
        int conswhite = ttl_white_before();
        int consblack = ttl_black_after();

        if (conswhite >= consblack) {
            swap(row[space], row[space - 1]);
            swap(holes[space], holes[space - 1]);

            if (dest[row[space]] == space)
                dest[row[space]]--;
            space -= 1;
        }
        else {
            swap(row[space + 1], row[space]);
            swap(holes[space + 1], holes[space]);

            if (dest[row[space]] == space)
                dest[row[space]]++;
            space += 1;
        }
    }

    assert(space >= 0 && space < 2 * n + 1);
    moves.pb(space + 1);
}

int main(void)
{
    freopen("shuttle.in", "r", stdin);
    freopen("shuttle.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        row[i] = 'W';
        holes[i] = i + 1;
    }
    space = n;
    for (int i = n + 1; i < 2 * n + 1; i++) {
        row[i] = 'B';
        holes[i] = i + 1;
    }

    dest['B'] = 0;
    dest['W'] = 2 * n;

    while (dest['B'] != dest['W']) 
        make_next_move();

    int i = 0;
    for (auto m : moves) {
        i++;
        printf("%d", m);
        if (i % 20 != 0 && i != moves.size())
            printf(" ");
        else 
            printf("\n");
    }

    return 0;
}