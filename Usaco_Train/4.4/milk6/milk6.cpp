/*
ID: panos.p1
LANG: C++11
TASK: milk6
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN 35
#define MAXM 100

using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, ii> pp;

int cap[MAXN][MAXN];
int flow[MAXN];
int res_cap[MAXN][MAXN];
set<int> adj_list[MAXN];
int n, m;
vector<pp> edges;
int start, finish;
bool used[MAXN];
int prevnode[MAXN];
set<int> removable;

bool customcomp (pp a, pp b)
{
    if (a.first.first != b.first.first)
        return !(a.first.first < b.first.first);
    
    return a.first.second < b.first.second;

}

int find_max_flow(void)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res_cap[i][j] = cap[i][j];

    int ttl_flow = 0;
    while(true) {
        priority_queue<ii> q;
        memset(used, false, sizeof(used));

        for (int i = 0; i < n; i++) {
            flow[i] = 0;
            prevnode[i] = -1;
        }
        flow[start] = INT_MAX;
        q.push(mp(flow[start], start));
        q.push(mp(0, INT_MAX));

        int curnode;
        ii cursit;
        int curflow;
        while(true) {
            cursit = q.top(); q.pop();
            curnode = cursit.second; curflow = cursit.first;

            if (curnode == INT_MAX)
                break;
            if (curnode == finish)
                break;

            if (used[curnode])
                continue;
            used[curnode] = true;

            for (auto v : adj_list[curnode]) 
                if (flow[v] < min(curflow, res_cap[curnode][v])) {
                    flow[v] = min(curflow, res_cap[curnode][v]);
                    prevnode[v] = curnode;
                    q.push(mp(flow[v], v));
                }
        }

        if (curnode == INT_MAX)
            break;

        assert(curnode == finish);

        int i = curnode;
        while (i != start) {
            res_cap[i][prevnode[i]] += curflow;
            res_cap[prevnode[i]][i] -= curflow;
            i = prevnode[i];
        }

        ttl_flow += curflow;
    }

    return ttl_flow;
}

int main(void)
{
    freopen("milk6.in", "r", stdin);
    freopen("milk6.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int n1, n2, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &n1, &n2, &c);
        n1--;
        n2--;

        adj_list[n1].insert(n2);
        adj_list[n2].insert(n1);
        cap[n1][n2] += c;
        edges.pb(mp(mp(c, i + 1), mp(n1, n2))); 
    }
    start = 0;
    finish = n - 1;

    int mflow = find_max_flow();
    if (mflow == 0) {
        printf("0 0\n");
        return 0;
    }
    sort(edges.begin(), edges.end(), customcomp);

    int curflow = mflow;
    int curcap, no1, no2, num, resflow;
    for (int e = 0; e < m && curflow != 0; e++) {
        curcap = edges[e].first.first;
        no1 = edges[e].second.first;
        no2 = edges[e].second.second;
        num = edges[e].first.second;

        cap[no1][no2] -= curcap;
        resflow = find_max_flow();
        if (curflow - resflow == curcap) {
            removable.insert(num);
            curflow = resflow;
        }
        else {
            cap[no1][no2] += curcap;
        }
    }

    printf("%d %d\n", mflow, (int)removable.size());
    int i = 0;
    for (auto r : removable) {
        printf("%d\n", r);
    }

    return 0;
}