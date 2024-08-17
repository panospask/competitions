#include "rail.h"
#include "grader.h"
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const int INF = 1e6 + 1;

int N;
vector<vector<int>> d;
int s1, s2;

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

bool east_sort(const int& a, const int& b)
{
    return d[0][a] < d[0][b];
}

bool west_sort(const int& a, const int& b)
{
    return d[s1][a] < d[s1][b];
}

int calculate(int i, int j)
{
    if (d[i][j] == INF) {
        d[i][j] = d[j][i] = getDistance(i, j);
    }

    return d[i][j];
}

void findLocation(int n, int first, int location[], int stype[])
{
    N = n;
    d.assign(N, vector<int>(N, INF));

    location[0] = first;
    stype[0] = 1;

    calculate_distance(0);
    s1 = closer(0);
    int d1 = d[0][s1];

    location[s1] = first + d1;
    stype[s1] = 2;

    calculate_distance(s1);
    s2 = closer(s1);
    int d2 = d[s1][s2];

    location[s2] = location[s1] - d2;
    stype[s2] = 1;

    int p1 = location[s1] - location[0];
    int p2 = 2 * (location[s1] - location[s2]);

    vector<int> east;
    vector<int> west;

    for (int i = 0; i < N; i++) {
        if (i == s1 || i == s2 || i == 0) {
            continue;
        }
        if (d[0][i] + p2 == d[s1][i] + p1) {
            east.pb(i);
        }
        else {
            west.pb(i);
        }
    }  

    sort(east.begin(), east.end(), east_sort);
    int eastmost = s1;
    int opt = s2;
    for (int i = 0; i < east.size(); i++) {
        p1 = location[eastmost] - location[0];
        p2 = 2 * (location[eastmost] - location[opt]);

        int u = east[i];

        calculate(u, eastmost);

        if (d[0][u] + p2 <= d[eastmost][u] + p1) {
            // u is the new eastmost
            location[u] = location[0] + d[0][u];
            stype[u] = 2;

            eastmost = u;
        }
        else {
            // u is not more east than the current maximum
            location[u] = location[eastmost] - d[eastmost][u];
            stype[u] = 1;

            if (location[u] > location[opt]) {
                opt = u;
            }
        }
    }

    sort(west.begin(), west.end());
    int westmost = s2;
    opt = s1;
    for (int i = 0; i < west.size(); i++) {
        p1 = location[s1] - location[westmost];
        p2 = 2 * (location[opt] - location[westmost]);
        
        int u = west[i];
        calculate(u, westmost);

        if (d[s1][u] + p2 <= d[westmost][u] + p1) {
            // u is the new westmost
            location[u] = location[s1] - d[s1][u];
            stype[u] = 1;

            westmost = u;
        }
        else {
            location[u] = location[westmost] + d[westmost][u];
            stype[u] = 2;

            if (location[u] < location[opt]) {
                opt = u;
            }
        }
    }
}