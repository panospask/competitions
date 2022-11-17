/*
ID: panos.p1
LANG: C++11
TASK: fence
*/

#include <bits/stdc++.h>
#define MAXN 505
#define pb push_back
#define mp make_pair

using namespace std;

template<class T> using rpq = priority_queue<T, vector<T>, greater<T>>;
typedef pair<int, int> ii;

set<int> adj_list[MAXN];
int e;
int degnode[MAXN];
int mnum = 5000;
vector<int> path;
map<ii, int> used;

set<int> odd_degnode;

void delete_edge(int v1, int v2)
{
    // adj_list[v1].erase(v2);
    // adj_list[v2].erase(v1);

    used[mp(v1, v2)]--;
    used[mp(v2, v1)]--;
}

void euler_proccess(int num)
{
    for (auto neigh : adj_list[num]) {
        if (used[mp(num, neigh)]) {
            delete_edge(num, neigh);
            euler_proccess(neigh);
        }
    }

    path.pb(num);
}

int main(void)
{
    freopen("fence.in", "r", stdin);
    freopen("fence.out", "w", stdout);

    scanf("%d", &e);
    int v1, v2;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &v1, &v2);
        adj_list[v1].insert(v2);
        adj_list[v2].insert(v1);
        degnode[v1]++;
        degnode[v2]++;
        if (degnode[v1] % 2 == 1)
            odd_degnode.insert(v1);
        else if (degnode[v1] >= 2)
            odd_degnode.erase(v1);
        
        if (degnode[v2] % 2 == 1)
            odd_degnode.insert(v2);
        else if (degnode[v2] >= 2)
            odd_degnode.erase(v2);

        mnum = min(mnum, min(v1, v2));
        used[mp(v1, v2)]++;
        used[mp(v2, v1)]++;
    }

    int start;
    if (odd_degnode.empty())
        start = mnum;
    else 
        start = *(odd_degnode.begin());

    euler_proccess(start);
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
        printf("%d\n", path[i]);

    return 0;
}