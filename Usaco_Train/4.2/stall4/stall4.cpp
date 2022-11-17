/*
ID: panos.p1
LANG: C++11
TASK: stall4
*/

#include <bits/stdc++.h>
#define MAXN 200
#define MAXM 200
#define MAXPOS (MAXN + MAXM + 2)
#define pb push_back
#define mp make_pair
#define MAXNUM ((int)1)
#define CLEARNUM ((int)1000000)

using namespace std;

typedef pair<int, int> ii;

template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

int n, m;   
int flow[MAXPOS + 2];
int cap[MAXPOS + 2][MAXPOS + 2];
vector<int> adj_list[MAXPOS + 2];
bool used[MAXPOS + 2];
int source, sink;
int ttl_pos;
int ans;
int prevnode[MAXPOS + 2];

void find_max_flow(void)
{
    int maxi, maxflow;
    int ttl_flow = 0;

    while (true) {
        priority_queue<ii> q;
        for (int i = 0; i < ttl_pos; i++) {
            flow[i] = 0;
            used[i] = false;
            prevnode[i] = -1;
            q.push(mp(flow[i], i));
        }
        flow[source] = MAXNUM;
        q.push(mp(flow[source], source));
        q.push(mp(0, CLEARNUM));

        while (true) {
            maxflow = q.top().first;
            maxi = q.top().second;
            q.pop();
            if (maxi == CLEARNUM)
                break;
            if (maxi == sink)
                break;
            if (used[maxi])
                continue;
            
            if (maxflow != flow[maxi])
                assert(maxflow == flow[maxi]); // A check
            used[maxi] = true;
            for (auto v : adj_list[maxi]) {
                if (flow[v] < min(maxflow, cap[maxi][v])) {
                    flow[v] = min(maxflow, cap[maxi][v]);
                    prevnode[v] = maxi;
                    q.push(mp(flow[v], v));
                }
            }
        }

        if (maxi == CLEARNUM)
            break;
        assert(maxi == sink);
        assert(maxflow == flow[sink]);
        for (int u = maxi; u != source; u = prevnode[u]) {
            cap[prevnode[u]][u] -= maxflow;
            cap[u][prevnode[u]] += maxflow;
        }
        ttl_flow += maxflow;
    }

    ans = ttl_flow;
    return;
}

int main(void)
{
    freopen("stall4.in", "r", stdin);
    freopen("stall4.out", "w", stdout);

    scanf("%d %d", &n, &m);
    int stallnum;
    int id;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &stallnum);
        for (int j = 1; j <= stallnum; j++) {
            scanf("%d", &id);
            id += n;
            cap[i][id] = 1;
            cap[id][i] = 0;
            adj_list[i].pb(id);
            adj_list[id].pb(i);
        }
    }

    // Initialize supersource(connected to all cows) and supersink(connected to all stalls)
    source = 0;
    for (int i = 1; i <= n; i++) {
        adj_list[source].pb(i);
        adj_list[i].pb(source);
        cap[source][i] = MAXNUM;
        cap[i][source] = 0;
    }
    sink = n + m + 1;
    for (int i = n + 1; i <= n + m; i++) {
        adj_list[sink].pb(i);
        adj_list[i].pb(sink);
        cap[i][sink] = MAXNUM;
        cap[sink][i] = 0;
    }
    ttl_pos = n + m + 2;

    find_max_flow();
    printf("%d\n", ans);
    return 0;
}