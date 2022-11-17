/*
ID: panos.p1
LANG: C++11
TASK: race3
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 50

using namespace std;

typedef unordered_map<int, bool> mi;

int n;
mi access_to[MAXN + 5];
vector<int> adj_list[MAXN + 5];
bool used[MAXN + 5];
vector<int> unavoidable;
vector<int> split;
int start, finish;

bool find_path_to_prev_node(int curnode, int midpoint)
{
    bool found_path = false;
    if (curnode == finish)
        return false;

    if (access_to[midpoint][curnode] == true)
        return true;

    used[curnode] = true;
    for (auto v : adj_list[curnode])
        if (!used[v])
            found_path = (found_path || find_path_to_prev_node(v, midpoint));

    return found_path;
}

void accessible_nodes_with_removal(int curnode, int removed)
{
    access_to[removed][curnode] = true;
    used[curnode] = true;

    if (curnode == finish)
        return;

    for (auto v : adj_list[curnode])
        if (!used[v] && v != removed)
            accessible_nodes_with_removal(v, removed);
}

int main(void)
{
    freopen("race3.in", "r", stdin);
    freopen("race3.out", "w", stdout);

    int i = 0;
    int n1;
    while (true) {
        while (true) {
            scanf("%d", &n1);
            if (n1 == -1 || n1 == -2)
                break;

            adj_list[i].pb(n1);
        }
        if (n1 == -1)
            break;
        i++;
    }
    n = i;
    start = 0;
    finish = n - 1;

    for (int i = 0; i < n; i++) {
        memset(used, false, sizeof(used));
        accessible_nodes_with_removal(start, i);

        if (i != start && i != finish && access_to[i][finish] == 0)
            unavoidable.pb(i);
    }

    for (auto u : unavoidable) {
        memset(used, false, sizeof(used));

        if (!find_path_to_prev_node(u, u))
            split.pb(u);
    }

    sort(unavoidable.begin(), unavoidable.end());
    sort(split.begin(), split.end());

    printf("%d", (int)unavoidable.size());
    for (auto u : unavoidable)
        printf(" %d", u);
    printf("\n");
    printf("%d", (int)split.size());
    for (auto s : split)
        printf(" %d", s);
    printf("\n");
    return 0;
}