#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;

struct LongPath {
    int length;
    ll labelsum;

    int node;
    // Values to compare
    int prevlabel;
    int prevnode;
};
const LongPath DEFAULT = {INT_MIN, 0, 0, 0, 0};

int N, M;

// Essentially reverse adjacency list
vector<vector<int>> revlist;
vector<vector<pi>> adj_list;
vector<int> outdegree;
vector<int> len;

// Ranking of longpaths, path at position N is like a supersink
vector<int> ranking;

// The optimal path for each node
vector<LongPath> path;

// All paths of the same size will be gathered here (I hope)
vector<LongPath> active;

bool operator < (const LongPath& a, const LongPath& b)
{
    if (a.length == b.length) {
        if (a.prevlabel == b.prevlabel)
            return ranking[a.prevnode] < ranking[b.prevnode];
        return a.prevlabel < b.prevlabel;
    }
    return a.length > b.length;
}

LongPath build_path(int u, int v, int l)
{
    LongPath p;
    p.node = u;
    p.length = path[v].length + 1;
    p.labelsum = path[v].labelsum + l;
    p.prevlabel = l;
    p.prevnode = v;

    return p;
}

void organize(void)
{
    sort(active.begin(), active.end());
    for (int i = 0; i < active.size(); i++) {
        ranking[active[i].node] = i;
    }
    active.clear();
}

int main(void)
{
    scanf("%d %d", &N, &M);
    revlist.resize(N);
    adj_list.resize(N);
    outdegree.assign(N, 0);
    path.resize(N + 1);
    ranking.resize(N + 1);
    len.assign(N, INT_MIN);

    for (int i = 0; i < M; i++) {
        int u, v, l;
        scanf("%d %d %d", &u, &v, &l);
        u--; v--;

        revlist[v].pb(u);
        adj_list[u].pb(mp(v, l));
        outdegree[u]++;
    }

    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (outdegree[i] == 0) {
            q.push(i);
            adj_list[i].push_back(mp(N, 0));
            len[i] = 0;
        }
    }

    int plen = 0;
    ranking[N] = 0;
    path[N] = {-1, 0, N, 0, N};

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (auto neigh : revlist[v]) {
            len[neigh] = max(len[neigh], len[v] + 1);
            outdegree[neigh]--;

            if (outdegree[neigh] == 0)
                q.push(neigh);
        }

        // Check if it's sorting time
        if (len[v] > plen) {
            organize();
            plen++;
        }

        // Calculate the best path :)
        path[v] = DEFAULT;
        for (auto neigh : adj_list[v]) {
            LongPath cur = build_path(v, neigh.first, neigh.second);
            if (cur < path[v]) {
                path[v] = cur;
            }
        }

        active.pb(path[v]);
    }

    for (int i = 0; i < N; i++) {
        printf("%d %lld\n", path[i].length, path[i].labelsum);
    }
}