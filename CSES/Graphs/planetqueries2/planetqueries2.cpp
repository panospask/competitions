#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

int n, q;
vector<int> component;
vector<bool> on_cycle;
vector<bool> visited;
vector<bool> on_stack;
vector<ii> joins_at;
int components = 0;
vector<int> dest;
stack<int> s;
vector<int> cyclesize;
vector<int> dist_to_first_oc;
vector<vector<int>> ancestor;

int move_up(int x, int len)
{
    for (int i = 0; i < ceil(log2(n)); i++)
        if (len & (1<<i))
            x = ancestor[i][x];

    return x;
}


void find_component(int node)
{
    if (visited[node] && on_stack[node]) {
        // New cycle found
        component[node] = components++;
        on_cycle[node] = true;
        joins_at[node] = mp(node, 0);
        dist_to_first_oc[node] = 0;
        int sz = 1;
        while (!(s.top() == node)) {
            dist_to_first_oc[s.top()] = sz;
            component[s.top()] = component[node];
            on_cycle[s.top()] = true;
            joins_at[s.top()] = mp(s.top(), 0);
            s.pop();
            sz++;
        }

        cyclesize.push_back(sz);
    }
    else if (visited[node]) {
        // Already found cycle
        return;
    }
    else {
        visited[node] = true;
        on_stack[node] = true;
        s.push(node);
        find_component(dest[node]);
        on_stack[node] = false;
        if (on_cycle[node]) {
            joins_at[node] = mp(node, 0);
        }
        else {
            s.pop();
            component[node] = component[dest[node]];
            joins_at[node] = joins_at[dest[node]];
            joins_at[node].second++;
        }
    }
}

int main(void)
{
    scanf("%d %d", &n, &q);
    dest.resize(n);
    component.resize(n);
    joins_at.resize(n);
    visited.assign(n, 0);
    on_cycle.assign(n, 0);
    dist_to_first_oc.resize(n);
    on_stack.assign(n, 0);
    ancestor.resize(ceil(log2(n)), vector<int>(n));
    for (int i = 0; i < n; i++) {
        scanf("%d", &dest[i]);
        dest[i]--;
        ancestor[0][i] = dest[i];
    }
    for (int i = 1; i < ancestor.size(); i++)
        for (int j = 0; j < n; j++)
            ancestor[i][j] = ancestor[i-1][ancestor[i-1][j]];

    for (int i = 0; i < n; i++)
        find_component(i);

    while (q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;
        if (component[a] != component[b])
            printf("-1\n");
        else {
            int len = cyclesize[component[a]];
            if (on_cycle[a] && on_cycle[b]) {
                int dist = dist_to_first_oc[a] - dist_to_first_oc[b];
                printf("%d\n", (dist + len) % len);
            }
            else if (on_cycle[a] && !on_cycle[b]) {
                printf("-1\n");
            }
            else if (!on_cycle[a] && on_cycle[b]) {
                int dist = joins_at[a].second;
                a = joins_at[a].first;
                int circledist = (dist_to_first_oc[a] - dist_to_first_oc[b] + len) % len;
                printf("%d\n", dist + circledist);
            }
            else if (joins_at[a].first != joins_at[b].first || joins_at[b].second > joins_at[a].second) {
                printf("-1\n");
            }
            else {
                int check_anc = joins_at[a].second - joins_at[b].second;
                int ans = move_up(a, check_anc) == b ? check_anc : -1;
                printf("%d\n", ans);
            }
        }
    }
}