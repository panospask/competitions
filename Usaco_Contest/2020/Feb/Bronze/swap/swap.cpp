#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 100

using namespace std;

typedef pair<int, int> ii;

int n, k;
int a_start, a_end, b_start, b_end;
bool visited[MAXN];
vector<int> cycles[MAXN];
ii belong_to[MAXN];
int final_pos[MAXN];
int cyclenum;

void calc_cycle(int node) 
{
    cycles[cyclenum].pb(node);
    belong_to[node] = mp(cyclenum, cycles[cyclenum].size() - 1);
    visited[node] = true;

    if (a_start <= node && a_end >= node) {
        // Execute first excersise 
        node = a_end - node + a_start;
    }
    if (b_start <= node && b_end >= node) {
        // Execute second excersise
        node = b_end - node + b_start;
    }

    if (!visited[node])
        calc_cycle(node);
}

int find_final(int node)
{
    int cycle = belong_to[node].first;
    int pos = belong_to[node].second;
    int sz = cycles[cycle].size();

    return cycles[cycle][(pos + (k % sz)) % sz];
}

int main(void)
{
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);

    scanf("%d %d", &n, &k);
    scanf("%d %d %d %d", &a_start, &a_end, &b_start, &b_end);
    a_start--; a_end--; b_start--; b_end--;

    memset(visited, false, sizeof(visited));
    cyclenum = 0;
    for (int i = 0; i < n; i++)
        if (!visited[i]) {
            calc_cycle(i);
            cyclenum++;
        }

    for (int i = 0; i < n; i++)
        final_pos[find_final(i)] = i;

    for (int i = 0; i < n; i++)
        printf("%d\n", final_pos[i] + 1);
    return 0;
}