#include <bits/stdc++.h>
#define mp make_pair
#define f first
#define s second

using namespace std;

const int LEFT = 0, DOWN = 1, RIGHT = 2, UP = 3;
const int BL = 0, BR = 1, TR = 2, TL = 3;

typedef pair<int, int> pi;
typedef long long ll;

struct UnionFind {

    int size;
    vector<int> rep;
    vector<int> rank;

    void init(int n) {
        size = n;
        rank.assign(size, 0);

        rep.resize(size);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    int find(int a) {
        if (a != rep[a])
            rep[a] = find(rep[a]);

        return rep[a];
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (rank[a] == rank[b])
            rank[a]++;
        if (rank[b] > rank[a])
            swap(a, b);

        rep[b] = a;
    }
};

struct Tree {
    int x, y, radius;
};

struct MaxDiameter {
    int a, b;
    double w;
};

bool operator < (const MaxDiameter& a, const MaxDiameter& b)
{
    return a.w < b.w;
}

int n, m;
int W, H;
UnionFind dsu;
vector<Tree> trees;
vector<pair<pi, int>> visitors;
vector<set<int>> adj_list;
vector<vector<int>> ans;
vector<int> vis;
vector<MaxDiameter> edges;
int cur;

void CreateEdgeTrees(Tree& a, Tree& b, int a_id, int b_id)
{
    double dist = sqrt((ll)(a.x - b.x) * (a.x - b.x) + (ll)(a.y - b.y) * (a.y - b.y));

    MaxDiameter c;
    c.w = dist - a.radius - b.radius;
    c.a = a_id;
    c.b = b_id;

    edges.push_back(c);
}

void CreateEdgeBorder(Tree& a, int b, int a_id)
{
    MaxDiameter c;
    c.a = a_id;
    c.b = b;
    c.w = 0 - a.radius;

    if (b == LEFT) {
        c.w += a.x;
    }
    else if (b == DOWN) {
        c.w += a.y;
    }
    else if (b == RIGHT) {
        c.w += W - a.x;
    }
    else
        c.w += H - a.y;

    edges.push_back(c);
}

void remove_from_all(int i)
{
    for (int k = 0; k < 4; k++)
        adj_list[k].erase(i);
}

void dfs(int node)
{
    if (vis[node])
        return;

    ans[cur].push_back(node);
    vis[node] = true;

    for (auto& neigh : adj_list[node])
        dfs(neigh);
}

int main(void)
{
    scanf("%d %d", &n, &m);
    scanf("%d %d", &W, &H);

    trees.resize(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &trees[i].x, &trees[i].y, &trees[i].radius);

    visitors.resize(m);
    ans.resize(m);
    for (int j = 0; j < m; j++) {
        scanf("%d %d", &visitors[j].f.f, &visitors[j].f.s);
        visitors[j].s = j;
    }
    sort(visitors.begin(), visitors.end());

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            CreateEdgeTrees(trees[i], trees[j], i + 4, j + 4);
        }

        CreateEdgeBorder(trees[i], LEFT, i + 4);
        CreateEdgeBorder(trees[i], DOWN, i + 4);
        CreateEdgeBorder(trees[i], RIGHT, i + 4);
        CreateEdgeBorder(trees[i], UP, i + 4);
    }
    sort(edges.begin(), edges.end());

    // Initially, all entrances are connected
    adj_list.resize(4);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (i != j)
                adj_list[i].insert(j);

    int cur_add = 0;
    dsu.init(n + 4);
    bool bottomtop = true, leftright = true, lefttop = true, leftbottom = true, righttop = true, rightbottom = true;

    for (int v = 0; v < m; v++) {
        int r, e, id;
        id = visitors[v].s;
        r = visitors[v].f.f;
        e = visitors[v].f.s - 1;

        while (cur_add < edges.size() && (edges[cur_add].w < 2 * r || edges[cur_add].w == 0)) {
            dsu.unite(edges[cur_add].a, edges[cur_add].b);
            cur_add++;
        }

        // Check the cases!
        if (bottomtop && dsu.same(LEFT, RIGHT)) {
            bottomtop = false;
            adj_list[TL].erase(BL);
            adj_list[TL].erase(BR);
            adj_list[TR].erase(BL);
            adj_list[TR].erase(BR);

            adj_list[BL].erase(TL);
            adj_list[BL].erase(TR);
            adj_list[BR].erase(TL);
            adj_list[BR].erase(TR);
        }
        if (leftright && dsu.same(DOWN, UP)) {
            leftright = false;
            adj_list[TL].erase(TR);
            adj_list[TL].erase(BR);
            adj_list[BL].erase(TR);
            adj_list[BL].erase(BR);

            adj_list[TR].erase(TL);
            adj_list[TR].erase(BL);
            adj_list[BR].erase(TL);
            adj_list[BR].erase(BL);
        }

        if (lefttop && dsu.same(LEFT, UP)) {
            lefttop = false;
            adj_list[TL].clear();

            remove_from_all(TL);
        }
        if (righttop && dsu.same(RIGHT, UP)) {
            righttop = false;
            adj_list[TR].clear();

            remove_from_all(TR);
        }
        if (rightbottom && dsu.same(RIGHT, DOWN)) {
            rightbottom = false;
            adj_list[BR].clear();

            remove_from_all(BR);
        }
        if (leftbottom && dsu.same(LEFT, DOWN)) {
            leftbottom = false;
            adj_list[BL].clear();

            remove_from_all(BL);
        }

        vis.assign(4, false);
        cur = id;
        dfs(e);
        sort(ans[cur].begin(), ans[cur].end());
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < ans[i].size(); j++)
            printf("%d", ans[i][j] + 1);
        printf("\n");
    }
}