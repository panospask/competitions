#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 998244353;

int N;
vector<vector<int>> adj_list;

string s, t;
vector<int> depth;
// A hash of the difference I expect in such depth
vector<ll> hash;
vector<ll> pow2;

bool good = true;

void dfs(int node, int par) {
    // Calculate for current node
    if (pow2.size() < depth[node]) {
        pow2.push_back(pow2.back() * 2 % MOD);
    }
}

void solve(void) {
    ;
}

int main(void) {
    ;
}