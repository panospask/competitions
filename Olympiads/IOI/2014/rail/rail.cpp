#include "rail.h"
#include "grader.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6 + 1;
const int MAXV = 1e6;

int N;
vector<vector<int>> d;
vector<int> at;
int s1, s2;

int westmost, eastmost;

void calculate_distance(int s)
{
    d[s][s] = 0;
    for (int i = 0; i < N; i++) {
        if (d[s][i] == INF) {
            d[s][i] = d[i][s] = getDistance(s, i);
        }
    }
}

int closer(int i)
{
    int id = -1;
    int v = INF;

    for (int j = 0; j < N; j++) {
        if (j != i && d[i][j] < v) {
            v = d[i][j];
            id = j;
        }
    }

    return id;
}

bool distancesort(const int& a, const int& b)
{
    return d[a] < d[b];
}

int calculate(int i, int j)
{
    if (d[i][j] == INF) {
        d[i][j] = d[j][i] = getDistance(i, j);
    }
 
    return d[i][j];
}

bool inside(int l)
{
    return l >= 0 && l <= MAXV;
}

bool WestType2(int u, int location[])
{
    int loc = location[westmost] + d[westmost][u];
    if (!inside(loc) || loc >= location[0]) {
        return false;
    }

    int switchdist = d[u][eastmost] - (location[eastmost] - loc);
    if (switchdist % 2) {
        return false;
    }
    switchdist /= 2;

    int switch_pos = loc - switchdist;
    if (switch_pos >= 0 && switch_pos <= MAXV && at[switch_pos] == 1) {
        return true;
    }

    return false;
}

bool EastType1(int u, int location[])
{
    int loc = location[eastmost] - d[u][eastmost];
    if (!inside(loc) || loc <= location[s1]) {
        return false;
    }

    int switchdist = d[u][westmost] - (loc - location[westmost]);
    if (switchdist % 2) {
        return false;
    }
    switchdist /= 2;

    int switch_pos = loc + switchdist;
    if (switch_pos <= MAXV && at[switch_pos] == 2) {
        return true;
    }

    return false;
}

bool Between(int u, int location[])
{
    if (westmost != 0) {
        return false;
    }

    int loc = location[s1] - (d[0][u] - d[0][s1]);
    if (loc <= location[0] || loc >= location[s1]) {
        return false;
    }

    if (d[eastmost][u] == location[eastmost] - loc && d[westmost][u] == d[0][u] + location[0] - location[westmost]) {
        return true;
    }
    return false;
}

bool WestType1(int u, int location[]) 
{
    int loc = location[eastmost] - d[u][eastmost];
    if (!inside(loc)) {
        return false;
    }

    if (d[u][0] == location[s1] - loc + d[0][s1]) {
        return true;
    }
    return false;
}

void findLocation(int n, int first, int location[], int stype[])
{
    N = n;
    d.assign(N, vector<int>(N, INF));
    at.assign(MAXV + 1, 0);

    location[0] = first;
    stype[0] = 1;
    at[location[0]] = 1;

    calculate_distance(0);
    s1 = closer(0);
    location[s1] = first + d[s1][0];
    stype[s1] = 2;
    at[location[s1]] = 2;

    vector<int> trav;

    for (int i = 0; i < N; i++) {
        if (i != 0 && i != s1) {
            trav.pb(i);
        }
    }

    sort(trav.begin(), trav.end(), distancesort);

    westmost = 0;
    eastmost = s1;
    for (int i = 0; i < trav.size(); i++) {
        int u = trav[i];

        calculate(u, eastmost);
        calculate(u, westmost);
        calculate(u, 0);

        int loc;
        int switched;

        if (Between(u, location)) {
            location[u] = location[s1] - (d[0][u] - d[0][s1]);
            stype[u] = 1;

            at[location[u]] = 1;
        }
        else if (WestType2(u, location)) {
            location[u] = location[westmost] + d[westmost][u];
            stype[u] = 2;

            at[location[u]] = 2;
        }
        else if (EastType1(u, location)) {
            location[u] = location[eastmost] - d[eastmost][u];
            stype[u] = 1;

            at[location[u]] = 1;
        }
        else {
            // Either new westmost or new eastmost
            if (!WestType1(u, location)) {
                location[u] = location[westmost] + d[westmost][u];
                stype[u] = 2;

                at[location[u]] = 2;
                eastmost = u;
            }
            else {
                location[u] = location[eastmost] - d[eastmost][u];
                stype[u] = 1;

                at[location[u]] = 1;
                westmost = u;
            }
        }
    }
}