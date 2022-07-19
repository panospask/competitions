/*
ID: panos.p1
LANG: C++11
TASK: agrinet
*/

#include <bits/stdc++.h>
#define MAXN 100
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n;
long long int ans;

int treesize = 0;
long long int treecost = 0;

int adj_matrix[MAXN][MAXN];
int dist[MAXN];
bool used[MAXN];

int find_smallest(void)
{
    int smallval = INT_MAX;
    int smallnum;
    for (int i = 0; i < n; i++) {
        if (!used[i] && dist[i] < smallval) {
            smallval = dist[i];
            smallnum = i;
        }
    }

    return smallnum;
}

void enter_in_tree(int a)
{
    treecost += dist[a];
    treesize++;
    used[a] = true;

    for (int j = 0; j < n; j++)
        if (dist[j] > adj_matrix[a][j])
            dist[j] = adj_matrix[a][j];
}

void prim_alg(void)
{
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        used[i] = false;
    }

    dist[0] = 0;
    enter_in_tree(0);

    int cur;
    while (treesize < n) {
        cur = find_smallest();
        enter_in_tree(cur);
    }

    ans = treecost;
}

int main(void)
{
    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);

    scanf("%d", &n);

    int cur;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &cur);
            adj_matrix[i][j] = cur;
        }


    prim_alg();

    printf("%lld\n", ans);
    return 0;
}