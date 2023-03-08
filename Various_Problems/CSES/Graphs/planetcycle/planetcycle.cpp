#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back

using namespace std;

int ans[MAXN + 2];
int p[MAXN + 2];
int is_cycle[MAXN + 2];
bool visited[MAXN + 2];
vector<int> curpath;
int cycle_lengths[MAXN + 2];
int total_cycles = 0;
int n;

int find_ans_for(int node)
{
    if (ans[node] != -1)
        return ans[node];

    if (is_cycle[node] == -1 && visited[node]) {
        // We create a new cycle
        for (auto it = curpath.rbegin(); it != curpath.rend(); it++) {
            int planet = *it;
            if (planet == node)
                break;
            is_cycle[planet] = total_cycles;
            cycle_lengths[total_cycles]++;
        }
        is_cycle[node] = total_cycles;
        cycle_lengths[total_cycles++]++;
    }
    else if (is_cycle[node] == -1) {
        visited[node] = true;
        curpath.pb(node);
        find_ans_for(p[node]);
        curpath.pop_back();
    }    
    
    if (is_cycle[node] != -1) {
        ans[node] = cycle_lengths[is_cycle[node]];
        return -1; // Indicates a cycle was found
    }
    else {
        ans[node] = ans[p[node]] + 1;
    }

    return 0;
}

int main(void)
{
    scanf("%d", &n);

    int dest;
    for (int i = 0; i < n; i++) {
        scanf("%d", &dest);
        p[i] = dest - 1;
        is_cycle[i] = -1;
        ans[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        find_ans_for(i);
        printf("%d ", ans[i]);
    }
    printf("\n");
    return 0;
}