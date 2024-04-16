#include <bits/stdc++.h>

using namespace std;

int N, M;
vector<vector<int>> no_adj_list;
vector<bool> visited;

vector<int> ans;
set<int> missing;
set<int> nxt;

bool find(vector<int>& v, int u)
{
    int pos = lower_bound(v.begin(), v.end(), u) - v.begin();

    if (pos != v.size() && v[pos] == u)
        return true;
    return false;
}

void explore_component(int s)
{
    visited[s] = true;

    missing.clear();
    for (int i  = 0; i < N; i++) {
        if (!visited[i] && s != i)
            missing.insert(i);
    }

    int sz = 0 ;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        sz++;
        int u = q.front();
        q.pop();

        for (auto m : missing) {
            if (find(no_adj_list[u], m)) {
                nxt.insert(m);
            }
            else {
                visited[m] = true;
                q.push(m);
            }
        }
        swap(missing, nxt);
        nxt.clear();
    }

    ans.push_back(sz);
}

int main(void)
{
    scanf("%d %d", &N, &M);

    no_adj_list.resize(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        no_adj_list[u].push_back(v);
        no_adj_list[v].push_back(u);
    }

    for (int i = 0; i < N; i++) {
        sort(no_adj_list[i].begin(), no_adj_list[i].end());
    }

    visited.assign(N, false);

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            explore_component(i);
        }
    }

    sort(ans.begin(), ans.end());
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}