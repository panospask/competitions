#include <bits/stdc++.h>
#define MAXN 200000
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

bool visited[MAXN];
int t, n, m;
bool useedge[MAXN + 5];

vector<ii> adj_list[MAXN];

void bfs(int source)
{
    queue<int> q;
    q.push(source);

    int cur;
    while (!q.empty()) {
        cur = q.front(); q.pop();

        for (auto neigh : adj_list[cur]) {
            if (!visited[neigh.first] && !useedge[neigh.second]) {
                visited[neigh.first] = true;
                useedge[neigh.second] = true;
                q.push(neigh.first);
            }
        }
    }
}


int main(void)
{
    scanf("%d", &t);
    for (int x = 0; x < t; x++) {
        memset(visited, false, sizeof(visited));
        memset(useedge, false, sizeof(useedge));

        scanf("%d %d", &n, &m);
        int n1, n2;
        for (int i = 0; i < m; i++) {
            scanf("%d %d", &n1, &n2);
            adj_list[--n1].pb(mp(--n2, i));
            adj_list[n2].pb(mp(n1, i));
        }

        int total_connect = 1;
        bfs(0);

        string ranking;
        for (int i = 0; i < m; i++) {
            if (useedge[i])
                ranking.pb('0');
            else 
                ranking.pb('1');
        }

        memset(visited, false, sizeof(visited));
        for (int i = 0; i < n; i++)
            if (!visited[i]) {
                bfs(i);
                total_connect++;
            }

        cout << ranking << '\n';
    }

    return 0;
}