/*
ID: panos.p1
LANG: C++11
TASK: cowtour
*/

#include <bits/stdc++.h>
#define MAXN 150
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;
ii points[MAXN];
double weight[MAXN][MAXN];
long double dist[MAXN][MAXN];
int n;
long double longest_from[MAXN];
int rep[MAXN];
long double maxof[MAXN];
int maxofnum;

void init(void)
{
    for (int i = 0; i < n; i++)
        rep[i] = i;
}

int find_rep(int i)
{
    if (rep[i] == i)
        return i;

    rep[i] = find_rep(rep[i]);
    return rep[i];
}

void join(int i, int j)
{
    rep[find_rep(i)] = find_rep(j);
}

long double find_dist(int i, int j)
{
    ii a = points[i], b = points[j];
    long long int pivot = (a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second);

    return sqrt((long double) pivot);
}

void floyd_wassal(void)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != -1 && dist[j][k] != -1) {
                    if (dist[i][j] > dist[i][k] + dist[j][k] || dist[i][j] == - 1) {
                        dist[i][j] = dist[i][k] + dist[j][k];
                        if (dist[i][j] != -1 && dist[i][j] > longest_from[i]) {
                            longest_from[i] = dist[i][j];
                            if (dist[i][j] > maxof[find_rep(i)]) {
                                maxof[find_rep(i)] = dist[i][j];
                                maxofnum = i;
                            }
                        }
                        if (dist[i][j] != -1 && dist[i][j] > longest_from[j]) {
                            longest_from[j] = dist[i][j];
                        }
                    }
                }
            }
}

void flo2(void)
{
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != -1 && dist[j][k] != -1) {
                    if (dist[i][j] > dist[i][k] + dist[j][k] || dist[i][j] == -1)
                        dist[i][j] = dist[i][k] + dist[j][k];
                }
}

void find_reps(void)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (dist[i][j] != -1) {
                longest_from[i] = max(longest_from[i], dist[i][j]);
                maxof[find_rep(i)] = max(maxof[find_rep(i)], dist[i][j]);
            }
}

int main(void)
{
    freopen("cowtour.in", "r", stdin);
    freopen("cowtour.out", "w", stdout);

    scanf("%d", &n);

    init();

    for (int i = 0; i < n; i++)
        scanf("%d %d", &points[i].first, &points[i].second);

    int cur;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%1d", &cur);

            if (cur == 1) {
                dist[i][j] = find_dist(i, j);
                join(i, j);
                longest_from[i] = max(longest_from[i], dist[i][j]);
            }
            else {
                if (i == j)
                    dist[i][j] = 0;
                else 
                    dist[i][j] = -1;
            }
        }

    // floyd_wassal();
    flo2();
    find_reps();

    long double minfield = LONG_LONG_MAX;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            if (dist[i][j] == -1) {
                long double d = max(longest_from[i] + longest_from[j] + find_dist(i, j), max(maxof[find_rep(i)], maxof[find_rep(j)]));
                if (d < minfield)
                    minfield = d;
            }
        }

    printf("%.6Lf\n", minfield);
    return 0;
}