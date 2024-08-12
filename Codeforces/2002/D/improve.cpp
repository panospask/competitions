#include <bits/stdc++.h>
#define pb push_back

using namespace std;

const int DEFAULT = -1;

int N, Q;
int rem;
vector<int> a;
vector<int> pos;
vector<vector<int>> kids;
vector<int> subtree;

// Variables while being a kid
vector<int> nxt;
vector<int> prv;
vector<int> par;

// Variables while being a parent
vector<int> chain;
vector<set<int>> kid_positions;
vector<bool> good;

// Test for any change in the subtree of node
bool test(int node)
{
    if (kids[node].size() == 0) {
        return true;
    }

    int p1 = *kid_positions[node].begin();

    if (p1 == 0) {
        return false;
    }

    return (a[p1 - 1] == node) && (chain[node] == kids[node].size() - 1);
}

void recalculate(int node)
{
    bool cur = test(node);

    rem -= cur - good[node];

    good[node] = cur;
}

void erase_bond(int n1, int n2)
{
    if (nxt[n1] == DEFAULT) {
        return;
    }

    nxt[n1] = DEFAULT;
    prv[n2] = DEFAULT;
    chain[par[n1]]--;
}

void make_bond(int n1, int n2)
{
    if (pos[n2] - pos[n1] != subtree[n1]) {
        return;
    }

    nxt[n1] = n2;
    prv[n2] = n1;
    chain[par[n1]]++;
}

// Erase this as kid
void erase_kid(int k)
{
    if (k == 0) {
        return;
    }

    int node = par[k];
    int bef = DEFAULT, aft = DEFAULT;

    auto it = kid_positions[node].lower_bound(pos[k]);

    it++;
    if (it != kid_positions[node].end()) {
        aft = a[*it];
    }
    it--;
    if (it != kid_positions[node].begin()) {
        it--;
        bef = a[*it];
    }

    if (bef != DEFAULT) {
        erase_bond(bef, k);
    }
    if (aft != DEFAULT) {
        erase_bond(k, aft);
    }
    if (bef != DEFAULT && aft != DEFAULT) {
        make_bond(bef, aft);
    }

    kid_positions[node].erase(pos[k]);
}

// Insert this as kid
void insert_kid(int k)
{
    if (k == 0) {
        return;
    }

    int node = par[k];
    int bef = DEFAULT, aft = DEFAULT;

    auto it = kid_positions[node].lower_bound(pos[k]);

    if (it != kid_positions[node].end()) {
        aft = a[*it];
    }
    if (it != kid_positions[node].begin()) {
        it--;
        bef = a[*it];
    }

    if (bef != DEFAULT && aft != DEFAULT) {
        erase_bond(bef, aft);
    }
    if (bef != DEFAULT) {
        make_bond(bef, k);
    }
    if (aft != DEFAULT) {
        make_bond(k, aft);
    }


    kid_positions[node].insert(pos[k]);

    recalculate(node);
}

void dfs(int node)
{
    subtree[node] = 1;
    for (auto neigh : kids[node]) {
        dfs(neigh);
        subtree[node] += subtree[neigh];
    }
}

void solve(void)
{
    scanf("%d %d", &N, &Q);

    a.resize(N);
    pos.resize(N);
    kids.assign(N, vector<int>());
    kid_positions.assign(N, set<int>());
    subtree.resize(N);
    good.assign(N, false);
    nxt.assign(N, DEFAULT);
    prv.assign(N, DEFAULT);
    par.resize(N);
    chain.assign(N, 0);
    rem = N;

    for (int i = 1; i < N; i++) {
        scanf("%d", &par[i]);
        par[i]--;

        kids[par[i]].pb(i);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        a[i]--;

        pos[a[i]] = i;
    }

    dfs(0);

    for (int i = 0; i < N; i++) {
        insert_kid(i);
    }
    for (int i = 0; i < N; i++) {
        recalculate(i);
    }

    while (Q--) {
        int i, j;
        scanf("%d %d", &i, &j);
        i--; j--;

        int n1 = a[i];
        int n2 = a[j];

        erase_kid(n1);
        erase_kid(n2);

        swap(pos[n1], pos[n2]);
        swap(a[i], a[j]);

        insert_kid(n1);
        insert_kid(n2);

        recalculate(n1);
        recalculate(n2);

        if (rem == 0) {
            printf("YES\n");
        }
        else {
            printf("NO\n");
        }
    }

    return;
}

int main(void)
{
    int t;
    scanf("%d", &t);

    while (t--) {
        solve();
    }

    return 0;
}