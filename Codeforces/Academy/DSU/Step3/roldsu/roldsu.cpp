#include <bits/stdc++.h>
#define mp make_pair

using namespace std;

typedef pair<int, int> ii;

struct dsu {

    int size;
    int components;
    vector<int> rep;
    vector<int> rank;
    stack<ii> changes_rep;
    stack<ii> changes_rank;

    void init(int n) {
        size = components = n;
        rep.resize(size);
        rank.assign(size, 0);
        for (int i = 0; i < size; i++)
            rep[i] = i;
    }

    void save(void) {
        changes_rank.push(mp(-1, -1)); // Savepoint
        changes_rep.push(mp(-1, -1)); // Savepoint
    }

    void rollback(void) {
        ii cur;
        while (!changes_rank.empty()) {
            cur = changes_rank.top(); changes_rank.pop();
            if (cur.first == -1) {
                // Savepoint reached
                break;
            }
            rank[cur.first] = cur.second;
        }
        while (!changes_rep.empty()) {
            cur = changes_rep.top(); changes_rep.pop();
            if (cur.first == -1) {
                // Savepoint reached
                break;
            }
            rep[cur.first] = cur.second;
            // Every rep change joins 2 sets => every rep removal creates 2 sets
            components++;
        }
    }

    int get(int a) {
        if (rep[a] != a)
            return get(rep[a]);
        
        return a;
    }

    void unite(int a, int b) {
        a = get(a);
        b = get(b);

        if (a == b)
            return;

        if (rank[a] == rank[b]) {
            changes_rank.push(mp(a, rank[a]));
            rank[a]++;
        }

        if (rank[b] > rank[a])
            swap(a, b);

        changes_rep.push(mp(b, b));
        rep[b] = a;
        components--;
        return;
    }
};

int n, m;
struct dsu graph;

int main(void)
{
    iostream::sync_with_stdio(false);
    cin >> n >> m;
    graph.init(n);

    string op;
    int a, b;
    for (int i = 0; i < m; i++) {
        cin >> op;
        if (op[0] == 'u') {
            cin >> a >> b;
            a--; b--;

            graph.unite(a, b);
            cout << graph.components << '\n';
        }
        else if (op[0] == 'p') {
            graph.save();
        }
        else {
            graph.rollback();
            cout << graph.components << '\n';
        }
    }

    return 0;
}