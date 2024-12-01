#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef pair<int, int> pi;
typedef long long ll;

const int MOD = 1e9 + 7;

pi operator ^ (pi a, pi b)
{
    return mp(a.fi ^ b.fi, a.se ^ b.se);
}

int value = -1;

struct DSU {
    struct Node {
        int par;

        pi v;
    };

    int size;
    int components = 0;
    vector<Node> rep;
    vector<int> rank;

    void init(int N) {
        size = N;
        rep.resize(size);
        rank.assign(size, 0);
        components = N;

        for (int i = 0; i < size; i++) {
            rep[i] = {i, mp(0, 0)};
        }
    }

    Node find(int a) {
        if (rep[a].par == a) {
            return rep[a];
        }
        
        Node res = find(rep[a].par);
        return {res.par, res.v ^ rep[a].v};
    }


    // a xor b = v
    bool unite(int a, int b, pi v) {
        Node p1 = find(a);
        Node p2 = find(b);

        if (p1.par == p2.par) {
            pi tot = p1.v ^ p2.v;
            if (tot == v) {
                return true;
            }
            else {
                if (tot.fi == v.fi) {
                    return false;
                }
                else {
                    if (value == -1) {
                        value = tot.se ^ v.se;
                        return true;
                    }
                    else {
                        return value == tot.se ^ v.se;
                    }
                }
            }
        }

        if (rank[p1.par] < rank[p2.par]) {
            swap(p1, p2);
            swap(a, b);
        }
        if (rank[p1.par] == rank[p2.par]) {
            rank[p1.par]++;
        }

        pi u = p1.v ^ v ^ p2.v;
        rep[p2.par] = {p1.par, u};


        components--;
        return true;
    }
};

int N, M, K, Q;

// [0..M] : The columns
// [M..M + N] : The rows
DSU graph;

// row[i]: List of elements at row i
vector<vector<pi>> row;
// column[]: List of elements at column i
vector<vector<pi>> column;

ll calc_pow(ll a, int b)
{
    cout << b << endl;
    ll c = 1;

    while (b) {
        if (b % 2) {
            c = c * a % MOD;
        }

        a = a * a % MOD;
        b /= 2;
    }

    return c;
}   

void solve(void)
{
    scanf("%d %d %d %d", &N, &M, &K, &Q);

    graph.init(N + M);
    row.assign(N, vector<pi>());
    column.assign(M, vector<pi>());

    // Top left square
    graph.unite(0, M, mp(0, 0));

    for (int i = 0; i < K; i++) {
        int r, c, v;
        scanf("%d %d %d", &r, &c, &v);
        r--; c--;

        row[r].pb(mp(c, v));
        column[c].pb(mp(r, v));
    }

    int check = 1;
    value = -1;
    for (int i = 0; i < N; i++) {
        for (int j = 1; j < row[i].size(); j++) {
            pi c1 = row[i][j - 1];
            pi c2 = row[i][j];
            check &= graph.unite(c1.fi, c2.fi, mp(0, c1.se ^ c2.se));
        }

        if (!row[i].empty()) {
            check &= graph.unite(row[i][0].fi, M + i, mp(1, row[i][0].se));
        }
    }
    for (int j = 0; j < M; j++) {
        for (int i = 1; i < column[j].size(); i++) {
            pi c1 = column[j][i - 1];
            pi c2 = column[j][i];
            check &= graph.unite(M + c1.fi, M + c2.fi, mp(0, c1.se ^ c2.se));
        }

        if (!column[j].empty()) {
            check &= graph.unite(column[j][0].fi + M, j, mp(1, column[j][0].se));
        }
    }

    if (!check) {
        printf("0\n");
    }
    else {
        int ans = calc_pow(1 << 30, graph.components - (value != -1));
        printf("%d\n", ans);
    }
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