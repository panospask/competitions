#include <bits/stdc++.h>
#define pb push_back

using namespace std;

int N, Q;
vector<int> par_size;
vector<int> sub_size;
vector<vector<int>> adj_list;
vector<int> par;
vector<int> tin;
vector<int> tout;
int counter = 0;

bool eulersort(const int& a, const int& b)
{
    return tin[a] < tin[b];
}

// Find the kid of u that contains v
int find_kid(int u, int v)
{
    int l = par[u] != -1;

    int res = upper_bound(adj_list[u].begin() + l, adj_list[u].end(), v, eulersort) - adj_list[u].begin() - 1;
    return adj_list[u][res];
}

// Returns true if A is ancestor of B
bool is_ancestor(int A, int B)
{
    return tin[A] <= tin[B] && tout[A] >= tout[B];
}

void init(int node)
{
    tin[node] = counter++;

    sub_size[node] = 1;
    for (auto neigh : adj_list[node]) {
        if (par[node] == neigh)
            continue;

        par[neigh] = node;
        init(neigh);
        sub_size[node] += sub_size[neigh];
    }

    tout[node] = counter;
}

void calculate_par(int node)
{
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        par_size[neigh] = par_size[node] + sub_size[node] - sub_size[neigh];
        calculate_par(neigh);
    }
}

int main(void)
{
    scanf("%d %d", &N, &Q);

    adj_list.resize(N);
    par.resize(N);
    sub_size.resize(N);
    par_size.resize(N);
    tin.resize(N);
    tout.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    par[0] = -1;
    init(0);
    par_size[0] = 0;
    calculate_par(0);

    for (int i = 0; i < N; i++)
        sort(adj_list[i].begin(),adj_list[i].end(), eulersort);

    while (Q--) {
        int A, B, C;
        scanf("%d %d %d", &A, &B, &C);
        A--; B--; C--;

        bool a1 = is_ancestor(C, A);
        bool a2 = is_ancestor(C, B);

        int res = 0;
        if (a1 && a2) {
            // If it is not the LCA, it is not on the path
            int k1 = find_kid(C, A);
            int k2 = find_kid(C, B);
            if (k1 == k2)
                res = 0;
            else
                res = par_size[C] + sub_size[C] - sub_size[k1] - sub_size[k2];
        }
        else if (a1) {
            res = sub_size[C] - sub_size[find_kid(C, A)];
        }
        else if (a2) {
            res = sub_size[C] - sub_size[find_kid(C, B)];
        }
        else {
            res = 0;
        }

        printf("%d\n", res);
    }

    return 0;
}