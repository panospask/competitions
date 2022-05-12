#include <bits/stdc++.h>

using namespace std;

typedef set<int> si;

si all_paths[50];

list<int> adj_list[100];
bool visit[50] = {false};



bool path_find(int cur, int dest)
{
    if (all_paths[dest].find(cur) != all_paths[dest].end())
        return false;

    visit[cur] = true;
    if (cur == dest)
        return true;
    
    bool holds = false;
    for (auto i : adj_list[cur]) {
        if (!visit[i])
            if (!path_find(i, dest))
                return false;
    }

    return true;
}

void find_all_paths(int a, int origin, int removed)
{
    all_paths[removed].insert(a);
    visit[a] = true;

    for (auto b : adj_list[a])
        if (!visit[b] && b != removed)
            find_all_paths(b, origin, removed);
}

int main(void)
{
    freopen("race.in", "r", stdin);
    freopen("race.out", "w", stdout);


    int n = 0;
    bool break_ln, break_all = false;
    while (!break_all) {
        break_ln = false;
        while (!break_ln) {
            int i;
            cin >> i;

            if (i == -1) {
                break_all = true;
                break_ln = true;
            }
            else if (i == -2) {
                break_ln = true;
            }
            else {
                adj_list[n].push_back(i);
            }
        }
        n++;
    }
    n--;

    list<int> possible;

    for (int i = 1; i < n - 1; i++) {
        memset(visit, false, sizeof(visit));
        find_all_paths(0, n - 1, i);
    }
    
    for (int i = 1; i < n - 1; i++) 
        if (all_paths[i].find(n - 1) == all_paths[i].end())
            possible.push_back(i);

    cout << possible.size();
    for (auto i : possible)
        cout << ' ' << i;

    cout << '\n';

    list<int> actual;
    for (auto i : possible) {
        bool holds = true;
        for (auto neigh : adj_list[i]) {
            memset(visit, false, sizeof(visit));
            if (!path_find(neigh, i))
                holds = false;
        }
        if (holds)
            actual.push_back(i);
    }

    cout << actual.size();
    for (auto i : actual)
        cout << ' ' << i;

    cout << '\n';
}