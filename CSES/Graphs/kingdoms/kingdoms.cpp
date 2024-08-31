#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int UNVISITED = 0;
const int EXPLORING = 1;
const int FINSHED = 2;

int N, M;
vector<vector<int>> adj_list;
vector<int> state;

// Variables for the connecting components
int cnt;
vector<int> id;

int counter = 0;
vector<int> num;
vector<int> low;

stack<int> s;

void dfs(int node)
{
    low[node] = num[node] = counter++;
    s.push(node);
    state[node] = EXPLORING;

    for (auto neigh : adj_list[node]) {
        if (state[neigh] == UNVISITED) {
            dfs(neigh);
        }
        if (state[neigh] == EXPLORING) {
            low[node] = min(low[node], low[neigh]);
        }
    }

    if (low[node] == num[node]) {
        id[node] = cnt++;
        state[node] = FINSHED;
        while (s.top() != node) {
            state[s.top()] = FINSHED;
            id[s.top()] = id[node];
            s.pop();
        }
        s.pop();
    }
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    state.assign(N, UNVISITED);
    id.resize(N);
    cnt = 0;
    low.resize(N);
    num.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
    }

    for (int i = 0; i < N; i++) {
        if (state[i] == UNVISITED) {
            dfs(i);
        }
    }

    printf("%d\n", cnt);
    for (int i = 0; i < N; i++) {
        printf("%d ", id[i] + 1);
    }
    printf("\n");

    return 0;
}