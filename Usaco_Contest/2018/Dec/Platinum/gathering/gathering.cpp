#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

int N, M;

vector<bool> disable_par;
// Except N --> All kids
vector<int> disable_kids_except;
vector<bool> ans;
vector<int> cons_cnt;
vector<int> indeg;
vector<vector<int>> constrain;
vector<bool> use;
vector<vector<int>> adj_list;
vector<int> par;
vector<int> tin;
vector<int> tout;
int counter;

bool ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

bool eulersort(const int& a, const int& b)
{
    return tin[a] < tin[b];
}

int find_kid(int a, int b)
{
    int l = par[a] != -1;

    int res = upper_bound(adj_list[a].begin() + l, adj_list[a].end(), b, eulersort) - adj_list[a].begin() - 1;
    return adj_list[a][res];
}

void init(int node)
{
    tin[node] = counter++;

    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        par[neigh] = node;
        init(neigh);
    }

    tout[node] = counter;
}

bool propagate_up(int node)
{
    bool d_p = disable_par[node];

    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        if (propagate_up(neigh)) {
            if (disable_kids_except[node] == -1)
                disable_kids_except[node] = neigh;
            else
                disable_kids_except[node] = N;
            d_p = true;
        }
    }

    return d_p;
}

void calc_ans(int node, bool dis_all)
{
    if (dis_all)
        disable_kids_except[node] = N;

    ans[node] = disable_kids_except[node] == -1;
    for (auto neigh : adj_list[node]) {
        if (neigh == par[node])
            continue;

        if (disable_kids_except[node] == -1 || disable_kids_except[node] == neigh)
            calc_ans(neigh, false);
        else
            calc_ans(neigh, true);
    }
}

bool check_valid(void)
{
    queue<int> q;
    use.assign(N, false);
    for (int i = 0; i < N; i++) {
        indeg[i] = adj_list[i].size();
        if (indeg[i] == 1 && cons_cnt[i] == 0)
            q.push(i);
    }

    int rm = 0;
    while (!q.empty()) {
        rm++;
        int v = q.front();
        q.pop();

        for (auto c : constrain[v]) {
            cons_cnt[c]--;
            if (!cons_cnt[c] && !use[c] && indeg[c] == 1) {
                q.push(c);
                use[c] = true;
            }
        }
        for (auto neigh : adj_list[v]) {
            indeg[neigh]--;
            if (!cons_cnt[neigh] && !use[neigh] && indeg[neigh] == 1) {
                q.push(neigh);
                use[neigh] = true;
            }

        }
    }

    return rm == N;
}

int main(void)
{
    freopen("gathering.in", "r", stdin);
    freopen("gathering.out", "w", stdout);

    scanf("%d %d", &N, &M);

    adj_list.resize(N);
    tin.resize(N);
    tout.resize(N);
    ans.resize(N);
    disable_kids_except.assign(N, - 1);
    disable_par.assign(N, false);
    par.resize(N);
    indeg.resize(N);
    constrain.resize(N);
    cons_cnt.resize(N);

    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--; v--;

        adj_list[u].pb(v);
        adj_list[v].pb(u);
    }

    par[0] = -1;
    init(0);

    for (int i = 0; i < N; i++)
        sort(adj_list[i].begin(), adj_list[i].end(), eulersort);

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--; b--;

        // a leaves before b
        if (ancestor(a, b)) {
            int K = find_kid(a, b);
            disable_par[K] = true;
        }
        else {
            disable_kids_except[a] = N;
        }

        constrain[a].pb(b);
        cons_cnt[b]++;
    }

    if (!check_valid()) {
        for (int i = 0; i < N; i++)
            printf("%d\n", 0);
        return 0;
    }

    propagate_up(0);
    calc_ans(0, false);

    for (int i = 0; i < N; i++)
        printf("%d\n", (int)ans[i]);

    return 0;
}