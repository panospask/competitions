#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pi;

const double INIT = 1e12;

struct NodeValue {
    int a;
    int b;

    NodeValue operator + (const NodeValue& n) {
        return {this->a + n.a, this->b + n.b};
    }
    void operator += (const NodeValue& n) {
        *this = *this + n;
    }
};

NodeValue operator - (const int i, const NodeValue& n)
{
    return {-n.a, -n.b + i};
}

const int w[2] = {1, 2};

int N, M;
vector<bool> visited;
vector<vector<pi>> adj_list;

// The value of every node is of the form a*x + b, where x is the value of the initial node in the bfs
vector<NodeValue> nodevals;
vector<int> component;
vector<double> final_values;
vector<int> all_values;
double x;


bool update_x(const NodeValue& p, const NodeValue& q)
{
    if (p.a == q.a) {
        return p.b == q.b;
    }

    double new_val = (double)(q.b - p.b) / (double)(p.a - q.a);
    if (abs(x - INIT) <= DBL_EPSILON) {
        x = new_val;
    }

    return abs(x - new_val) <= DBL_EPSILON;
}

bool bfs(int s)
{
    component.clear();
    all_values.clear();
    x = INIT;
    queue<int> q;
    q.push(s);
    nodevals[s] = {1, 0};

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        component.pb(u);
        NodeValue cur = nodevals[u];

        all_values.pb(-cur.b * cur.a);

        for (auto [v, c] : adj_list[u]) {
            NodeValue nxt = w[c] - nodevals[u];

            if (!visited[v]) {
                nodevals[v] = nxt;
                visited[v] = true;
                q.push(v);
            }
            else {
                bool good = update_x(nodevals[v], nxt);
                if (!good) {
                    return false;
                }
            }
        }
    }

    if (abs(x - INIT) <= DBL_EPSILON) {
        sort(all_values.begin(), all_values.end());
        int mid = all_values.size() / 2;

        x = all_values[mid];
    }

    for (auto u : component) {
        final_values[u] = nodevals[u].a * x + nodevals[u].b;
    }

    return true;
}

int main(void)
{
    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    visited.assign(N, false);
    nodevals.resize(N);
    final_values.resize(N);

    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u--; v--; c--;

        adj_list[u].pb(mp(v, c));
        adj_list[v].pb(mp(u, c));
    }

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            bool good = bfs(i);

            if (!good) {
                printf("NO\n");
                return 0;
            }
        }
    }

    printf("YES\n");
    for (int i = 0; i < N; i++) {
        printf("%lf ", final_values[i]);
    }
    printf("\n");

    return 0;
}