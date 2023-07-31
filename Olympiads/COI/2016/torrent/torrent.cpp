#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, A, B;

// dp[i]: Maximum allowed time s.t i must be reached in order to complete the thing in time
vector<int> dp;
vector<int> p;
vector<bool> ok;
vector<vector<int>> adj_list;
vector<vector<int>> kid_times;

int TIME_TESTED;

vector<int> tin;
vector<int> tout;
int counter;

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

bool test_early(int t, vector<int>& a, int skiptime = -2)
{
    int cur_time = t;
    for (int i = 0; i < a.size(); i++) {
        if (cur_time == skiptime)
            cur_time++;
        if (a[i] < cur_time)
            return false;
        cur_time++;
    }

    return true;
}

void push_downwards(int node, int time_par)
{
    if (!ancestor(node, B)) {
        return;
    }
    else if (test_early(time_par, kid_times[node]) == false) {
        // Cannot advance
        return;
    }

    ok[node] = true;
    // Find the earliest time the file can be sent to the child that leads to B
    int l = time_par;
    int r = TIME_TESTED + 1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (test_early(time_par, kid_times[node], mid))
            r = mid;
        else
            l = mid;
    }

    for (auto neigh : adj_list[node])
        if (neigh != p[node])
            push_downwards(neigh, r);
}

// Function to be called at B and ancestors
// Seeing at what time they can get the file
void push_upwards(int node, int time_kid)
{
    if (node == -1) {
        return;
    }
    else if (test_early(time_kid, kid_times[node]) == false) {
        // Cannot go here, or further
        return;
    }

    ok[node] = true;
    // Find the earliest time the file can be sent to the parent
    // Find the earliest time the file can be sent to the child that leads to B
    int l = time_kid;
    int r = TIME_TESTED + 1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (test_early(time_kid, kid_times[node], mid))
            r = mid;
        else
            l = mid;
    }

    push_upwards(p[node], r);
}

void calculate_dp(int node)
{
    kid_times[node].push_back(TIME_TESTED + 1);
    for (auto neigh : adj_list[node]) {
        if (neigh == p[node])
            continue;

        calculate_dp(neigh);

        if (!ancestor(neigh, B))
            kid_times[node].push_back(dp[neigh]);
    }

    sort(kid_times[node].begin(), kid_times[node].end());
    // Binary search for the latest possible time slot
    int r = TIME_TESTED + 1;
    int l = -1;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (test_early(mid, kid_times[node]))
            l = mid;
        else
            r = mid;
    }

    // The earliest time is l - 1
    dp[node] = l - 1;

    return;
}

void euler_tour(int node)
{
    tin[node] = counter++;

    for (auto neigh : adj_list[node]) {
        if (neigh != p[node]) {
            p[neigh] = node;
            euler_tour(neigh);
        }
    }

    tout[node] = counter;
}

bool test_time(int t)
{
    TIME_TESTED = t;
    ok.assign(N, false);
    kid_times.assign(N, vector<int>());
    dp.assign(N, -1);

    calculate_dp(A);
    push_downwards(A, 0);
    push_upwards(B, 0);

    for (int i = 0; i < N; i++) {
        if (ancestor(i, B) && !ok[i])
            return false;
    }

    return true;
}

int main(void)
{
    scanf("%d %d %d", &N, &A, &B);
    A--; B--;

    tin.resize(N);
    tout.resize(N);
    dp.resize(N);
    p.resize(N);
    adj_list.resize(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    // Root the tree at A
    p[A] = -1;
    euler_tour(A);

    int l = -1;
    int r = N;
    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (test_time(mid))
            r = mid;
        else
            l = mid;
    }

    printf("%d\n", r);

    return 0;
}