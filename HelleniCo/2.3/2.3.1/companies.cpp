#include <bits/stdc++.h>

using namespace std;

typedef set<int> si;
typedef pair<int, int> ii;
typedef map<int, multiset<ii>> adj_list;

int main(void)
{
    freopen("companies.in", "r", stdin);
    freopen("companies.out", "w", stdout);

    int n;
    cin >> n;

    adj_list adlist;
    si vertices;

    int i, j, p;
    for (int k = 0; k < n; k++) {
        cin >> i >> j >> p;
        adlist[i].insert(make_pair(j, p));
        vertices.insert(i);
        vertices.insert(j);
    }

    for (int u : vertices) {
        bool visited[105] = {false};
        int holding[105] = {0};

        queue<int> q;
        visited[u] = true;
        holding[u] = 100;
        q.push(u);

        while (!q.empty()) {
            int cur_node = q.front();
            q.pop();

            for (ii node : adlist[cur_node]) {

                int v, w;
                tie(v, w) = node;

                if (holding[cur_node] > 50)
                    holding[v] += w;
                
                if (holding[v] > 50) {
                    if (!visited[v]) {
                        q.push(v);
                        visited[v] = true;
                    }
                }
            }
        }

        for (int j : vertices) {
            if (j != u && holding[j] > 50)
                cout << u << ' ' << j << '\n';
        }
    }

}