#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50

using namespace std;

typedef pair<int, int> ii;

struct cow {
    ii coords;
    ii stopped = mp(INT_MAX, INT_MAX);
    char dir;

    void read_cow(void) {
        getchar();
        dir = getchar();
        scanf("%d %d", &coords.first, &coords.second);
    }
};
typedef struct cow Cow;

struct collision {
    ii colsquare;
    int cow1;
    int cow2;
    int dist;
};
typedef struct collision Collision;

Cow cowlist[MAXN + 5];
int dist_covered[MAXN + 5];
int colnum = 0;
set<Collision> possible_collisions;
int n;

bool operator < (Collision a, Collision b)
{
    if (a.dist != b.dist)
        return a.dist < b.dist;
    else if (a.cow1 != b.cow1)
        return a.cow1 < b.cow1;
    else 
        return a.cow2 < b.cow2;
}

bool check_cow_square(int cownum, ii square)
{
    if (cowlist[cownum].dir == 'N') {
        if (cowlist[cownum].coords.first != square.first)
            return false;
        else if (cowlist[cownum].coords.second > square.second)
            return false;
    }
    else {
        if (cowlist[cownum].coords.second != square.second)
            return false;
        else if (cowlist[cownum].coords.first > square.first)
            return false;
    }


    return true;
}

int dist_cow_square(int cownum, ii square)
{
    return square.first - cowlist[cownum].coords.first + square.second - cowlist[cownum].coords.second;
}

void create_collision(int c1, int c2)
{
    Collision cur_col;
    cur_col.cow1 = c1;
    cur_col.cow2 = c2;

    cur_col.colsquare = mp(max(cowlist[c1].coords.first, cowlist[c2].coords.first), max(cowlist[c1].coords.second, cowlist[c2].coords.second));

    bool good = true;
    good = good && check_cow_square(c1, cur_col.colsquare);
    good = good && check_cow_square(c2, cur_col.colsquare);

    if (good) {
        int dist1 = dist_cow_square(c1, cur_col.colsquare);
        int dist2 = dist_cow_square(c2, cur_col.colsquare);
        if (dist1 == dist2)
            cur_col.dist = INT_MAX;
        else 
            cur_col.dist = max(dist1, dist2);
    }
    else 
        cur_col.dist = INT_MAX;

    possible_collisions.insert(cur_col);
}

bool check_collision(Collision a)
{
    if (cowlist[a.cow1].stopped.first < a.colsquare.first || cowlist[a.cow1].stopped.second < a.colsquare.second)
        return false;
    if (cowlist[a.cow2].stopped.first < a.colsquare.first || cowlist[a.cow2].stopped.second < a.colsquare.second)
        return false;
    if (a.dist == INT_MAX)
        return false;
    return true;
}

void make_collision(Collision b)
{
    int dist1 = dist_cow_square(b.cow1, b.colsquare);
    int dist2 = dist_cow_square(b.cow2, b.colsquare);

    if (dist1 > dist2) {
        cowlist[b.cow1].stopped = b.colsquare;
        dist_covered[b.cow1] = dist1;
    }
    else {
        cowlist[b.cow2].stopped = b.colsquare;
        dist_covered[b.cow2] = dist2;
    }

    colnum++;
}

int main(void)
{
    // freopen("rutstuck.in", "r", stdin);
    // freopen("rutstuck.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        cowlist[i].read_cow();
        dist_covered[i] = INT_MAX;
    }

    for (int i = 0 ; i < n; i++) 
        for (int j = i + 1; j < n; j++) {
            create_collision(i, j);
        }

    for (auto col : possible_collisions) {
        if (colnum == n - 1) break;
        if (col.dist == INT_MAX) break;

        if (check_collision(col))
            make_collision(col);
    }

    for (int i = 0; i < n; i++) {
        if (dist_covered[i] != INT_MAX)
            printf("%d\n", dist_covered[i]);
        else 
            printf("Infinity\n");
    }

    return 0;
}