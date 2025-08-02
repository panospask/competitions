#include "worldmap.h"
#define pb push_back

using namespace std;

vector<vector<int>> ans;
vector<vector<int>> adj_list;
vector<bool> visited;

int row;
int cnt = 0;

void fill(int color) {
    for (int i = 0; i < ans[row].size(); i++) {
        if (ans[row][i] == 0) {
            ans[row][i] = color;
        }
    }

    row++;
}

bool dfs(int node) {
    if (visited[node]) {
        return false;
    }

    visited[node] = true;
    cnt++;
    fill(node);
    for (int i = 0; i < adj_list[node].size(); i++) {
        ans[row][2 * i] = adj_list[node][i];
    }
    fill(node);
    fill(node);

    for (auto neigh : adj_list[node]) {
        if (dfs(neigh)) {
            fill(node);
        }
    }

    return true;
}

vector<vector<int>> create_map(int N, int M, vector<int> A, vector<int> B) {
    ans.assign(3 * N, vector<int>(3 * N, 0));
    adj_list.assign(N + 1, vector<int>());
    visited.assign(N + 1, false);

    cnt = 0;
    for (int i = 0; i < M; i++) {
        adj_list[A[i]].pb(B[i]);
        adj_list[B[i]].pb(A[i]);
    }

    row = 0;
    dfs(1);

    while (row < ans.size()) {
        fill(ans[row - 1][0]);
    }

    return ans;
}
