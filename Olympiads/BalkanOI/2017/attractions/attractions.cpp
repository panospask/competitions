#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define f first
#define s second

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

const ll INF = 1e9 + 1;

int n;
ll k;
vector<vector<int>> adj_list;
vector<int> a;

// Dp variables
vector<pi> best_inside;
vector<pi> best_outside;
vector<pi> second_best;

// Functional Graph variables
vector<int> points_to;
vector<bool> on_stack;
stack<int> st;

void calculate_inside(int node, int par)
{
    best_inside[node] = mp(-INF, 1);

    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        calculate_inside(neigh, node);

        pi by_subtree = mp(best_inside[neigh].f - 1, best_inside[neigh].s);
        pi by_cur = mp(a[neigh] - 1, -neigh);

        pi give = max(by_cur, by_subtree);

        if (best_inside[node] < give) {
            second_best[node] = best_inside[node];
            best_inside[node] = give;
        }
        else {
            second_best[node] = max(second_best[node], give);
        }
    }
}

void calculate_outside(int node, int par)
{
    best_outside[node] = mp(-INF, -1);
    if (par != -1) {
        pi by_ancestor = mp(best_outside[par].f - 1, best_outside[par].s);
        by_ancestor = max(by_ancestor, mp(a[par] - 1, -par));

        pi by_sibling;

        if (best_inside[par].s == best_inside[node].s || best_inside[par].s == -node) {
            by_sibling = mp(second_best[par].f - 1, second_best[par].s);
        }
        else {
            by_sibling = mp(best_inside[par].f - 1, best_inside[par].s);
        }

        best_outside[node] = max(by_sibling, by_ancestor);
    }

    for (auto neigh : adj_list[node])
        if (neigh != par)
            calculate_outside(neigh, node);
}

int find_after(int node, ll days)
{
    if (days == 0)
        return node;
    if (on_stack[node]) {
        // Cycle found
        vector<int> cyc;

        while (st.top() != node) {
            cyc.push_back(st.top());
            st.pop();
        }
        cyc.push_back(node);

        reverse(cyc.begin(), cyc.end());

        int lands_at = days % cyc.size();
        return cyc[lands_at];
    }

    on_stack[node] = true;
    st.push(node);
    return find_after(points_to[node], days - 1);
}

int main(void)
{
    scanf("%d %lld", &n, &k);

    a.resize(n);
    adj_list.resize(n);
    best_inside.resize(n);
    best_outside.resize(n);
    second_best.resize(n);
    points_to.resize(n);
    on_stack.assign(n, false);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    calculate_inside(0, -1);
    calculate_outside(0, -1);

    // Build functional graph
    for (int i = 0; i < n; i++) {
        if (best_inside[i] > best_outside[i]) {
            points_to[i] = -best_inside[i].s;
        }
        else {
            points_to[i] = -best_outside[i].s;
        }
    }

    int ans = find_after(0, k);
    printf("%d\n", ans + 1);

    return 0;
}