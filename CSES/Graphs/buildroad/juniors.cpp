#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int N, M;

// adj_list[i]: Λίστα γειτνίασης του i (vector)
// O(N + M) (Good)
vector<vector<int>> adj_list;

// O(N^2) space complexity
// int adj_list[MAXN][MAXN];

vector<bool> visited;

void bfs(int i) {
    queue<int> q;

    q.push(i);

    while (q.empty() == false) {
        // Process a node
        int a = q.front();
        q.pop();

        for (int j = 0; j < adj_list[a].size(); j++) {
            int b = adj_list[a][j];

            if (visited[b]) {
                continue;
            }

            q.push(b);
            visited[b] = true;
        }
    }
}

int main(void) {
    scanf("%d %d", &N, &M);

    // Initialize all adjacency lists to empty
    adj_list.assign(N + 1, vector<int>());
    visited.assign(N + 1, false);

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    int counter = 0;
    vector<ii> edges;
    int first = -1;
    for (int i = 1; i <= N; i++) {
        if (visited[i]) {
            // We have visited i
            continue;
        }

        bfs(i);
        counter++;

        if (first == -1) {
            // Not reached any connected component
            // This is the first one
            first = i;
        }
        else {
            edges.push_back({first, i});
        }
    }

    printf("%d\n", counter - 1);
    for (auto e : edges) {
        printf("%d %d\n", e.first, e.second);
    }

    return 0;
}