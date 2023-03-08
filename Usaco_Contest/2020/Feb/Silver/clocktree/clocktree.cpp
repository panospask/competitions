#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100000

using namespace std;

int n;
vector<int> adj_list[MAXN + 2];
int clockface[MAXN + 2];
bool visited[MAXN + 2];

int coloursum[2];
int coloursize[2];

void split_graph(int node, int col)
{
    if (visited[node])
        return;

    visited[node] = true;
    coloursum[col] += clockface[node];
    coloursize[col]++;

    for (auto neigh : adj_list[node])
        split_graph(neigh, !col);

    return;
}

int main(void)
{
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &clockface[i]);
        clockface[i] %= 12;
    }
    
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    split_graph(0, 0);
    if (coloursum[0] % 12 == coloursum[1] % 12)
        printf("%d\n", n);
    else if (coloursum[0] % 12 == (coloursum[1] - 1) % 12)
        printf("%d\n", coloursize[1]);
    else if (coloursum[1] % 12 == (coloursum[0] - 1) % 12)
        printf("%d\n", coloursize[0]);
    else 
        printf("0\n");

    return 0;
}