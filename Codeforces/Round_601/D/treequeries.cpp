#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int MOD = 998244353;

typedef long long ll;

ll calc_pow(ll a, int b)
{
    ll c = 1;
    while (b) {
        if (b % 2)
            c = c * a % MOD;

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}
ll calc_inv(ll a)
{
    return calc_pow(a, MOD - 2);
}

const int QUERY = 0;
const int UPDATE = 1;
struct Event {
    int type;
    int node;

    // Only for updates
    int v;
};

int N, Q;
ll N_INV;
int BLOCK_SIZE;
vector<int> v;
vector<vector<int>> adj_list;
vector<int> subtree_size;
vector<int> active_updates;
vector<Event> events;
vector<int> ans;
vector<int> tin;
vector<int> tout;
vector<int> self;
vector<int> outval;
vector<int> p;
int counter = 0;
int curp;

void add(int& a, int b)
{
    a += b;
    if (a > MOD)
        a -= MOD;
}
void subtract(int& a, int b)
{
    a -= b;
    if (a < 0)
        a += MOD;
}

void process_updates(int node, int par = -1, ll incomingval = 0)
{
    // probability of the outside updates entering this subtree
    add(v[node], incomingval);

    // Process updates that happen in this node
    add(v[node], active_updates[node]);

    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        int newval = (N - subtree_size[neigh]) * N_INV % MOD;
        newval = (ll)newval * active_updates[node] % MOD;

        add(newval, outval[node]);
        subtract(newval, outval[neigh]);
        subtract(newval, self[node]);
        add(newval, incomingval);

        process_updates(neigh, node, newval);
    }
}
int generate_subtree_updates(int node, int par = -1)
{
    outval[node] = 0;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        generate_subtree_updates(neigh, node);
        add(outval[node], outval[neigh]);
    }

    add(v[node], outval[node]);
    self[node] = (subtree_size[node] * N_INV) % MOD * active_updates[node] % MOD;

    add(outval[node], self[node]);

    return outval[node];
}

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

// Finds the kid of a that contains b
int find_kid_contain(int a, int b)
{
    // if (adj_list[a].size() <= 5) {
    //     for (auto e : adj_list[a])
    //         if (ancestor(e, b))
    //             return e;
    // }

    int l = 0;
    int r = adj_list[a].size() - 1;
    if (p[a] == -1)
        r++;

    while (r > l + 1) {
        int mid = (l + r) / 2;
        if (tin[adj_list[a][mid]] <= tin[b])
            l = mid;
        else
            r = mid;
    }

    return adj_list[a][l];
}

void process_block(vector<Event>& events)
{
    for (int i = 0; i < events.size(); i++) {
        auto e = events[i];
        if (e.type == UPDATE) {
            add(active_updates[e.node], e.v);
        }
        else {
            int id = e.v;
            ans[id] = v[e.node];
            int d = e.node;
            for (int j = 0; j < i; j++) {
                if (events[j].type == QUERY)
                    continue;

                int v = events[j].v;
                int u = events[j].node;
                ll prob = 0;
                if (d == u) {
                    prob = 1;
                }
                else if (ancestor(d, u)) {
                    int available = subtree_size[u];
                    prob = available * N_INV % MOD;
                }
                else if (ancestor(u, d)) {
                    int available = N - subtree_size[find_kid_contain(u, d)];
                    prob = available * N_INV % MOD;
                }
                else {
                    int available = subtree_size[u];
                    prob = available * N_INV % MOD;
                }

                add(ans[id], (int)(prob * v % MOD));
            }
        }
    }

    generate_subtree_updates(0);
    process_updates(0);

    for (auto& e : events) {
        if (e.type == UPDATE)
            active_updates[e.node] = 0;
    }
}

void init(int node, int par = -1)
{
    p[node] = par;
    tin[node] = counter++;
    subtree_size[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par)
            continue;

        init(neigh, node);
        subtree_size[node] += subtree_size[neigh];
    }
    tout[node] = counter;
}

bool adjsort(const int& a, const int& b)
{
    if (a == curp)
        return false;
    else if (b == curp)
        return true;

    return tin[a] < tin[b];
}

int main(void)
{
    scanf("%d %d", &N, &Q);
    N_INV = calc_inv(N);
    BLOCK_SIZE = 3200;

    outval.resize(N);
    active_updates.resize(N);
    adj_list.resize(N);
    subtree_size.resize(N);
    v.resize(N);
    tin.resize(N);
    tout.resize(N);
    p.resize(N);
    self.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    init(0);
    for (int i = 0; i < N; i++) {
        curp = p[i];
        sort(adj_list[i].begin(), adj_list[i].end(), adjsort);
    }

    for (int q = 0; q < Q; q++) {
        int op;
        scanf("%d", &op);

        Event cur;
        cur.type = op % 2;
        if (op == 1) {
            int u, d;
            scanf("%d %d", &u, &d);
            u--;

            cur.node = u;
            cur.v = d;
            events.push_back(cur);
        }
        else {
            int u;
            scanf("%d", &u);
            u--;

            cur.node = u;
            cur.v = ans.size();
            ans.push_back(0);
            events.push_back(cur);
        }

        if (events.size() == BLOCK_SIZE) {
            process_block(events);
            events.clear();
        }
    }
    process_block(events);

    for (int i = 0; i < ans.size(); i++)
        printf("%d\n", ans[i]);

    return 0;
}