#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N;
vector<vector<int>> adj_list;
vector<int> c;
vector<int> k;

// total amount of colour x
vector<int> total;

vector<vector<int>> occur;

int counter = 0;
vector<int> tin;
vector<int> tout;

void dfs(int node, int par) {
    tin[node] = counter++;
    occur[c[node]].pb(tin[node]);

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node);
    }
    tout[node] = counter;

    
}

int main(void) {
    ;
}