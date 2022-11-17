/*
ID: panos.p1
LANG: C++11
TASK: telecow
*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define MAXN (2 * 100)
#define MAXM 600

using namespace std;

typedef pair<int, int> ii;

int n, m, source, sink;
int cap[MAXN][MAXN];
int res_cap[MAXN][MAXN];
int prevnode[MAXN];
int flow[MAXN];
bool used[MAXN];
bool deleted[MAXN];
set<int> adj_list[MAXN];

int find_max_flow(int removed)
{
    int maxloc, maxflow, ttl_flow = 0;

    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++)
            res_cap[i][j] = cap[i][j];
    }

    while (true) {
        priority_queue<ii> q;
        for (int i = 0; i < 2 * n; i++) {
            used[i] = false;
            flow[i] = 0;
            prevnode[i] = -1;
        }
        q.push(mp(INT_MAX, source));
        q.push(mp(0 , INT_MAX));


        while (true) {
            maxloc = q.top().second;
            maxflow = q.top().first;
            q.pop();

            if (maxloc == INT_MAX)
                break;
            if (maxloc == sink)
                break;

            used[maxloc] = true;
            for (auto neigh : adj_list[maxloc])
                if (!used[neigh] && !deleted[neigh] && neigh != 2 * removed && neigh != 2 * removed + 1 && flow[neigh] < min(maxflow, res_cap[maxloc][neigh])) {
                    flow[neigh] = min(maxflow, res_cap[maxloc][neigh]);
                    prevnode[neigh] = maxloc;
                    q.push(mp(flow[neigh], neigh));
                }
        }

        if (maxloc == INT_MAX)
            break;

        for (int j = sink; j != source; j = prevnode[j]) {
            res_cap[prevnode[j]][j] -= maxflow;
            res_cap[j][prevnode[j]] += maxflow;
        }

        ttl_flow += maxflow;
    }

    return ttl_flow;
}

int main(void)
{
    freopen("telecow.in", "r", stdin);
    freopen("telecow.out", "w", stdout);

    scanf("%d %d %d %d", &n, &m, &source, &sink);
    source--;
    sink--;
    int n1, n2;
    for (int i = 0; i < m; i++){ 
        scanf("%d %d", &n1, &n2);
        n1--;
        n2--;
        if (n1 != source && n2 != sink) {
            adj_list[2 * n1].insert(2 * n2 + 1);
            adj_list[2 * n2 + 1].insert(2 * n1);
            cap[2 * n2 + 1][2 * n1] = 1;
        }

        if (n2 != source && n1 != sink) {
            adj_list[2 * n2].insert(2 * n1 + 1);
            adj_list[2 * n1 + 1].insert(2 * n2);
            cap[2 * n1 + 1][2 * n2] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != sink && i != source) {
            adj_list[2 * i].insert(2 * i + 1);
            adj_list[2 * i + 1].insert(2 * i);
            cap[2 * i][2 * i + 1] = 1;
        }
        else {
            adj_list[2 * i].insert(2 * i + 1);
            adj_list[2 * i + 1].insert(2 * i);
            cap[2 * i][2 * i + 1] = INT_MAX;
        }
    }

    source = 2 * source;
    sink = 2 * sink + 1;

    set<int> answers;
    int ttl_flow = find_max_flow(-1);

    printf("%d\n", ttl_flow);
    int tmp_flow = ttl_flow;
    int curflow;
    int i = 0;
    while (answers.size() < ttl_flow) {
        if (2 * i != source && 2 * i + 1 != sink) {
            curflow = find_max_flow(i);
            if (tmp_flow - curflow == 1) {
                deleted[2 * i] = deleted[2 * i + 1] = true;
                tmp_flow -= 1;
                answers.insert(i);
            }
        }

        i++;
    }


    i = 0;
    for (auto v : answers) {
        printf("%d", v + 1);
        if (i != answers.size() - 1)
            printf(" ");
        else 
            printf("\n");
        i++;
    }
    return 0;
}