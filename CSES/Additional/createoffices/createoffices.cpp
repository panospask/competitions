#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int INF = 1e6;

int N, D;
vector<vector<int>> adj_list;

//dp[node][dist]: Most nodes placed in the subtree of node
// if the closest node is at least dist away from node
vector<deque<int>> dp;

void makemax(int& a, const int& b)
{
    if (a < b) {
        a = b;
    }
}

// Merge the 2 dps and store the result in d1
void merge(deque<int>& v1, deque<int>& v2)
{
    if (v1.size() < v2.size()) {
        swap(v1, v2);
    }

    vector<int> created(v2.size(), 0);
    for (int dist = 0; dist < v2.size(); dist++) {
        int counterdist = D - dist;
        if (counterdist < dist) {
            // We want dist to be the minimum distance
            counterdist = dist;
        }

        if (counterdist < v1.size()) {
            makemax(created[dist], v1[counterdist] + v2[dist]);
        }
        if (counterdist < v2.size()) {
            makemax(created[dist], v1[dist] + v2[counterdist]);
        }
    }

    for (int dist = 0; dist < v2.size(); dist++) {
        makemax(v1[dist], v2[dist]);
        makemax(v1[dist], created[dist]);
    }

    // Propagate downwards
    for (int dist = v2.size() - 2; dist >= 0; dist--) {
        makemax(v1[dist], v1[dist + 1]);
    }
}

void dfs(int node, int par)
{
    dp[node].push_back(1);

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);

        // Move all of dp[neigh] one step higher
        dp[neigh].push_front(dp[neigh].front());

        merge(dp[node], dp[neigh]);
    }
}

int main(void)
{
    scanf("%d %d", &N, &D);

    adj_list.resize(N);
    dp.resize(N);

    for (int i = 1; i < N; i++) {
        int p;
        scanf("%d", &p);

        adj_list[p].pb(i);
    }

    dfs(0, 0);

    printf("%d\n", dp[0][0]);
}