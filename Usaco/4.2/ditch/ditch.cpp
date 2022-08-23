/*
ID: panos.p1
LANG: C++11
TASK: ditch
*/

#include <bits/stdc++.h>
#define MAXN 205
#define pb push_back

using namespace std;

long long int cap[MAXN][MAXN];
long long int flow[MAXN];
long long int n, m;
long long int source, sink;
vector<long long int> adj_list[MAXN];
long long int ans;
bool visited[MAXN];
long long int prevnode[MAXN];
long long int ttl_flow;

void find_max_flow(void)
{
    long long int maxloc = 0, maxflow = 0;

    while (true) {
        for (int i = 0; i < m; i++) {
            flow[i] = 0;
            visited[i] = false;
            prevnode[i] = -1;
        }

        flow[source] = LONG_LONG_MAX;
        
        while (true) {
            maxloc = -1;
            maxflow = 0;

            for (int i = 0; i < m; i++) {
                if (maxflow < flow[i] && !visited[i]) {
                    maxloc = i;
                    maxflow = flow[i];
                }
            }

            if (maxloc == -1)
                break;
            if (maxloc == sink)
                break;

            visited[maxloc] = true;
            for (auto v : adj_list[maxloc]) {
                if (flow[v] < min(maxflow, cap[maxloc][v])) {
                    flow[v] = min(maxflow, cap[maxloc][v]);
                    prevnode[v] = maxloc;
                }
            }
        }

        if (maxloc == -1)
            break;

        for (int v = maxloc; v != source; v = prevnode[v]) {
            cap[prevnode[v]][v] -= maxflow;
            cap[v][prevnode[v]] += maxflow;
        }

        ttl_flow += maxflow;
    }

    ans = ttl_flow;
}

int main(void)
{
    freopen("ditch.in", "r", stdin);
    freopen("ditch.out", "w", stdout);

    scanf("%lld %lld", &n, &m);
    int n1, n2, c;
    int capadd = 0;
    long int capaddl = 0;
    long long int capaddll = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &n1, &n2, &c);
        n1--;
        n2--;
        cap[n1][n2] += c;
        adj_list[n1].pb(n2);
        adj_list[n2].pb(n1);
        capadd+= c;
        capaddl+= c;
        capaddll+= c;
    }
    // printf("%d %ld %lld\n", capadd, capaddl, capaddll);
    source = 0;
    sink = m - 1;

    find_max_flow();
    printf("%lld\n", ans);
    return 0;
}