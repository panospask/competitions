#include <bits/stdc++.h>

using namespace std;

struct edge {
    int come;
    int go;
    long double pe;
} edges[1000001];

long double dist[1001];

int t, n, m;

bool bellman_ford(void)
{
    memset(dist, 0, sizeof(dist));
    bool last_change = true;

    struct edge cur_edge;
    for (int i = 0; i < n; i++) {
        last_change = false;
        for (int j = 0; j < m; j++) {
            cur_edge = edges[j];
            if (dist[cur_edge.come] + cur_edge.pe < dist[cur_edge.go]) {
                dist[cur_edge.go] = dist[cur_edge.come] + cur_edge.pe;
                last_change = true;
            }
        }
    }

    return last_change;
}

int main(void)
{
    freopen("millionaire.in", "r", stdin);
    freopen("millionaire.out", "w", stdout);

    cin >> t;

    while (t--) {
        scanf("%d %d", &n, &m);
        for (int i = 0, a, b, pe; i < m; i++) {
            scanf("%d %d %d", &a, &b, &pe);
            edges[i].come = a;
            edges[i].go = b;
            edges[i].pe = -log(0.5 + 0.015 * pe);
        }

        if (bellman_ford())
            printf("Possible\n");
        else 
            printf("Not possible\n");
    }

    return 0;
}