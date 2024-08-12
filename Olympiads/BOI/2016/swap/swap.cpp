/* For an explanation of the solution, read this:
 * https://codeforces.com/blog/entry/44769?#comment-293999
 */

#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> a;
vector<int> res;

int counter = 0;
vector<int> tin;
vector<int> tout;

/* dp[i][j]:
 * If the value at node i is j, at what position will it end up if we
 * perform the swaps optimally
 */
vector<unordered_map<int, int>> dp;

int process(int node, int v)
{
    if (dp[node].count(v)) {
        return dp[node][v];
    }

    int l = 2 * node + 1, r = 2 * node + 2;

    if (l >= N) {
        return node;
    }
    if (r >= N) {
        if (v < a[l]) {
            return node;
        }
        else {
            return process(l, v);
        }
    }

    if (v < min(a[l], a[r])) {
        // Do not make any swaps
        dp[node][v] = node;
    }
    else if (a[l] < min(v, a[r])) {
        // Only make the first swap to bring a[l] at the root
        dp[node][v] = process(l, v);
    }
    else {
        // a[r] is placed at the root

        int mn = min(a[l], v);

        int place_left = process(l, mn);
        int place_right = process(r, mn);

        if (place_left < place_right) {
            // Placing the minimum element left results in a better outcome
            if (mn == v) {
                dp[node][v] = process(l, v);
            }
            else {
                dp[node][v] = process(r, v);
            }
        }
        else {
            // Placing the minimum element right results in a better outcome
            if (mn == v) {
                dp[node][v] = process(r, v);
            }
            else {
                dp[node][v] = process(l, v);
            }
        }
    }

    return dp[node][v];
}

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

void dfs(int node)
{
    if (node >= N) {
        return;
    }

    tin[node] = counter++;

    dfs(2 * node + 1);
    dfs(2 * node + 2);

    tout[node] = counter;
}

void make_result(int node, int v)
{
    int l = 2 * node + 1;
    int r = 2 * node + 2;

    if (process(node, v) == node) {
        res[node] = v;

        if (l < N) {
            make_result(l, a[l]);
        }
        if (r < N) {
            make_result(r, a[r]);
        }
    }
    else if (ancestor(l, process(node, v))) {
        make_result(l, v);

        res[node] = a[l];
        if (r < N) {
            res[node] = min(a[l], a[r]);
            make_result(r, max(a[l], a[r]));
        }
    }
    else {
        make_result(r, v);
        res[node] = a[r];
        make_result(l, a[l]);
    }
}

int main(void)
{
    scanf("%d", &N);

    a.resize(N);
    tin.resize(N);
    tout.resize(N);
    res.resize(N);
    dp.resize(N);

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }
    
    process(0, a[0]);
    dfs(0);
    make_result(0, a[0]);

    for (int i = 0; i < N; i++) {
        printf("%d ", res[i]);
    }
    printf("\n");

    return 0;
}