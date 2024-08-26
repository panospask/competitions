#include <bits/stdc++.h>
#include "beechtree.h"

using namespace std;

typedef pair<int, int> pi;

int N, M;
vector<vector<pi>> kids;
vector<int> subtree;
vector<int> ans;
vector<map<int, int>> by_size;

bool colorsort(pi a, pi b)
{
    return a.second < b.second;
}

// Finds the size of the subtree of the kid of node that is of colour c 
// or 0 if node has no such kid
int sizecount(int node, int c)
{
    int p = lower_bound(kids[node].begin(), kids[node].end(), make_pair(0, c), colorsort) - kids[node].begin();

    if (p == kids[node].size() || kids[node][p].second != c) {
        return 0;
    }
    return subtree[kids[node][p].first];
}

bool cmp(int small, int big)
{
    for (auto [kid, c] : kids[small]) {
        if (sizecount(big, c) < subtree[kid]) {
            return false;
        }
    }

    return true;
}

bool merge(map<int, int>& a, map<int, int>& b)
{
    if (a.size() < b.size()) {
        swap(a, b);
    }

    bool res = true;
    for (auto [size, node] : b) {
        auto prv = a.upper_bound(size);
        if (prv != a.begin()) {
            prv--;

            res = res && cmp(prv->second, node);
        }

        auto nxt = a.lower_bound(size);
        if (nxt != a.end()) {
            res = res && cmp(node, nxt->second);
        }

        a[size] = node;
    }

    return res;
}

void dfs(int node)
{
    subtree[node] = 1;
    ans[node] = true;

    sort(kids[node].begin(), kids[node].end(), colorsort);
    int prv = -1;
    for (auto [kid, c] : kids[node]) {
        dfs(kid);

        ans[node] = ans[node] && ans[kid] && c != prv;
        subtree[node] += subtree[kid];
        prv = c;
    }

    if (!ans[node]) {
        return;
    }

    by_size[node][subtree[node]] = node;

    for (auto [kid, c] : kids[node]) {
        ans[node] = ans[node] && merge(by_size[node], by_size[kid]);
    }
}

vector<int> beechtree(int N, int M, vector<int> P, vector<int> C)
{
    kids.resize(N);
    ans.resize(N);
    subtree.resize(N);
    by_size.resize(N);

    for (int i = 1; i < N; i++) {
        kids[P[i]].push_back(make_pair(i, C[i]));
    }

    dfs(0);

    return ans;
}