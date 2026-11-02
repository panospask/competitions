#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

int N;
vector<int> A;
vector<vector<int>> adj_list;

// The set of elements such that, if current node is left is state
// with value v, we save 1 over the current best arbitrary
vector<set<int>> save;
// best[node]: How much do I save using arbitrary value
vector<int> best;

vector<int> subtree;

void merge(set<int>& s1, set<int>& s2, int& a1, int& a2, map<int, int>& special) {
    // We save what we can (combined)
    a1 = a1 + a2;

    // Check if there are any values that appear as valid options in both sets
    // which allow as to save +1 (the current merging kid)
    if (s1.size() < s2.size()) {
        swap(s1, s2);
    }

    for (auto v : s2) {
        if (s1.count(v)) {
            special[v]++;
        }
        else {
            s1.insert(v);
        }
    }
}

void dfs(int node, int par, int sum) {
    sum = sum ^ A[node];

    best[node] = 0;
    map<int, int> special;

    for (auto neigh : adj_list[node]) {
        if (neigh == par) {
            continue;
        }

        dfs(neigh, node, sum);
        merge(save[node], save[neigh], best[node], best[neigh], special);
    }

    if (adj_list[node].size() == 1 && par != -1) {
        // We are at a leaf
        save[node].insert(sum);
    }
    else {
        // We can arbitrarily choose a kid (or more) and not flip it, since we are flipping current node
        best[node]++;
        if (special.size() == 0) {
            // We can only save 1 kid
            return;
        }
        // We can save more than one, use the special values saved before
        int add = 0;
        for (auto [v, c] : special) {
            add = max(add, c);
        }
        best[node] += add;

        // The extra values don't help me anymore, only those that appear (c+1) times
        // If this TLEs, its because of the clear
        save[node].clear();
        for (auto [v, c] : special) {
            if (c == add) {
                save[node].insert(v);
            }
        }
    }
}

int main(void) {
    scanf("%d", &N);

    A.resize(N);
    adj_list.resize(N);
    save.resize(N);
    best.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    dfs(0, -1, 0);

    printf("%d\n", N - (best[0] + save[0].count(0)));
}